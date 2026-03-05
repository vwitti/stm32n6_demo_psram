/*
 * AsgAssert.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef COMMON_ASGASSERT_ASGASSERT_H_
#define COMMON_ASGASSERT_ASGASSERT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Handler-Prototyp (wird von dir implementiert)
void my_assert_fail(const char *expr,
                    const char *file,
                    int line,
                    const char *func);

// Makro ersetzt assert()
#define ASG_ASSERT(expr)                                      \
    do {                                                     \
        if (!(expr)) {                                       \
            my_assert_fail(#expr, __FILE__, __LINE__, __func__); \
        }                                                    \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* COMMON_ASGASSERT_ASGASSERT_H_ */
