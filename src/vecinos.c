#include "vecinos.h"

unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j,
                     unsigned int M, unsigned int N)
{
    int contador = 0;
    int c1 = 0;
    int c2 = 0;
    int f = 0;
    int c = 0;

    for (c1 = -1; c1 <= 1; ++c1)
    {
        f = mod(i + c1, N);
        
        for (c2 = -1; c2 <= 1; ++c2)
        {
            if (c1 == 0 && c2 == 0)
                continue;
            c = mod(j + c2, M);
            if (a[f * M + c] == 1)
                contador++;
        }
    }
    return contador;
}
