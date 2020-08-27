#include <stdio.h>
#include <stdlib.h>
#include "hashlib.h"
#define HASHSIZE 1000                          // Define o numero de posicoes no array. Note que esse nao eh o limite maximo

int main(int argc, char *argv[])
{

    HashNode *hashnode[HASHSIZE];              // Onde os registros serao salvos


    /* Exemplos */
    HashNode TAGa = { "TAGaaa", NULL, NULL };
    HashNode TAGb = { "TAGbbb", NULL, NULL };


    hashInsert(&TAGa);
    hashInsert(&TAGb);

    achar_hashnode("TAGaaa");
    achar_hashnode("TAGbbb");
    achar_hashnode("TAGccc");
    return 0;
}
