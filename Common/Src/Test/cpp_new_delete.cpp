
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#if defined(__GNUC__) && (__ARM_ARCH == 8)

// GCC targeting ARM architecute 8 (z.B. Cortex-M55)
#if defined(OS_TYPE_THREADX)

#include "Common/Inc/Test/cpp_new_delete.h"

int demo_cpp_new_delete(void)
{
    // allocate single int
    int* p;

    printf("demo_cpp_new_delete: test\n");

    p = new int(42);

    printf("p=%p\n", p);

    // free single int
    delete p;

    // allocate array of 5 ints
    int* arr = new int[5]{1, 2, 3, 4, 5};

    printf("Array: \n");
    for (int i = 0; i < 5; i++)
    {
    	printf("p=%d\n", arr[i]);
    }

    // free array
    delete[] arr;

    arr = new int[0x500]; //0x1400 // Alloc much but leak for test

    printf("p=%p\n", arr);


	return 0;
}

#endif // defined(OS_TYPE_THREADX)

#endif // defined(__GNUC__) && (__ARM_ARCH == 8)
