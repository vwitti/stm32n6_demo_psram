/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

// sim_thread.c
#define _GNU_SOURCE
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <stdatomic.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>

#include "forte/ASGEVO_PACKAGE/iosubsystem.h"
#include "forte/ASGEVO_PACKAGE/sensors.h"
#include "forte/ASGEVO_PACKAGE/valves.h"
#include "forte/ASGEVO_PACKAGE/events.h"

atomic_int ctx__running;       // 1=läuft, 0=stop

static inline void timespec_add_ns(struct timespec *t, long ns) {
  t->tv_nsec += ns;
  while (t->tv_nsec >= 1000000000L) {
    t->tv_nsec -= 1000000000L;
    t->tv_sec += 1;
  }
}

static void set_thread_realtime(int prio) {
  struct sched_param sp;
  memset(&sp, 0, sizeof(sp));
  sp.sched_priority = prio;

  // Hinweis: braucht i.d.R. CAP_SYS_NICE oder root
  if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp) != 0) {
    // Nicht fatal: wir laufen dann einfach ohne RT
    // (Optional loggen)
  }
}

static void* sim_thread_main(void *arg) {
  sim_thread_t *ctx = (sim_thread_t*)arg;

  if (ctx->use_realtime) {
    set_thread_realtime(ctx->rt_priority);
  }

  const long period_ns = SENORESIM_CYCLE_TIME * 1000L * 1000L; // 20 ms

  struct timespec next;
  if (clock_gettime(CLOCK_MONOTONIC, &next) != 0) {
    // Wenn das schiefgeht, abbrechen
    atomic_store(&ctx__running, 0);
    return NULL;
  }

  // optional: starte "ab der nächsten Periode"
  timespec_add_ns(&next, period_ns);

  while (atomic_load(&ctx__running)) {
    // Warten bis zum geplanten Zeitpunkt (driftfrei)
    int ret = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
    if (ret != 0 && ret != EINTR) {
      // Loggen und weiter versuchen
      fprintf(stderr, "clock_nanosleep: %s\n", strerror(ret));
    }

    if (!atomic_load(&ctx__running)) {
      break;
    }

    // Deadline erreicht -> ausführen
    vSensorCom_SimulateSensorExecute();

    // nächsten Slot planen
    struct timespec before = next;
    timespec_add_ns(&next, period_ns);

    // Overrun-Erkennung: sind wir schon über "next" drüber?
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    // Wenn now > next (oder weit hinterher), resynchronisieren:
    if ((now.tv_sec > next.tv_sec) ||
        (now.tv_sec == next.tv_sec && now.tv_nsec > next.tv_nsec)) {

      // Optional: einmal loggen
      // fprintf(stderr, "Overrun: missed period(s)\n");

      // Resync: ab jetzt wieder periodisch, nächste Periode ab "now"
      next = now;
      timespec_add_ns(&next, period_ns);
    }

    (void)before;
  }

  return NULL;
}

// Startet den Thread. Returns 0 bei Erfolg.
int SensorSim_pthread_start(sim_thread_t *ctx, int use_realtime, int rt_priority) {
  if (!ctx) return EINVAL;

  ctx->use_realtime = use_realtime ? 1 : 0;
  ctx->rt_priority = (rt_priority > 0) ? rt_priority : 20;

  if (atomic_exchange(&ctx__running, 1) == 1) {
    return EALREADY; // läuft schon
  }

  int err = pthread_create(&ctx->thread, NULL, sim_thread_main, ctx);
  if (err != 0) {
    atomic_store(&ctx__running, 0);
    return err;
  }

  return 0;
}

// Stoppt den Thread (blockiert bis Thread beendet ist). Returns 0 bei Erfolg.
int SensorSim_pthread_stop(sim_thread_t *ctx) {
  if (!ctx) return EINVAL;

  if (atomic_exchange(&ctx__running, 0) == 0) {
    return 0; // war nicht aktiv
  }

  return pthread_join(ctx->thread, NULL);
}
