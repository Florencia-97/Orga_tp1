#include "vecinos.h"

int mod(int x, int m)
{
    int r = x % m;
    return r < 0 ? r + m : r;
}

unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j,
                     unsigned int M, unsigned int N)
{
    int contador = 0;
    int c1 = 0;
    for (c1 = -1; c1 <= 1; ++c1)
    {
        int f = mod(i + c1, N);
        int c2 = 0;
        for (c2 = -1; c2 <= 1; ++c2)
        {
            if (c1 == 0 && c2 == 0)
                continue;
            int c = mod(j + c2, M);
            if (a[f * M + c] == 1)
                contador++;
        }
    }
    return contador;
}
