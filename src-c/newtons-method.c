/* Finds root using Newton's Method */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    /* f(x) = x^5 - 4 */

    srand(time(0)); /* seed */

    double f = rand() % 4; /* an initial random guess */

    for (size_t i = 0; i < 10000; ++i)
    {
        f -= (pow(f, 5) - 4) / (5 * pow(f, 4));
    }

    printf("root is %g", f);

    return EXIT_SUCCESS;
}
