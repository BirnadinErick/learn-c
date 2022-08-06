/*
    these 2 lines will ensure your platforms C Library
    is visible to our compiler, and the platform's
    I/O ops are also available to us
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*
        this ensures we have modern C in the platform
    */
    double A[3] = {
        [0] = 2003,
        [1] = 5,
        [2] = 19,
    };

    for (size_t i = 0; i < 3; ++i)
    {
        printf("Element of A @ %zu = %g\n", i, A[i]);
    }

    return EXIT_SUCCESS;
}
