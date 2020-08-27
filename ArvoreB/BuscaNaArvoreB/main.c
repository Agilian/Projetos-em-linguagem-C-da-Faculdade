#include <stdio.h>
#include <stdlib.h>
#define d 10

struct noB{
    int chave[2*d];
    struct noB *filho[2*d+1];
};

/*
noB* busca(noB *raizArvoreB, int valBuscado){
    int i = 0;

    if(raizArvoreB == NULL){
        return NULL;
    }

    while(i<d){
        if(raizArvoreB.chave[i] == valBuscado){
            return raizArvoreB;
        }
        else if(raizArvoreB.chave[i] < valBuscado){
            busca(raizArvoreB.filho[i]);
        }
        else if(raizArvoreB.chave[i] > valBuscado){
            i++;
        }
    }
}
*/

noB* buscaJairo(noB *r, int v){
    int i = 0;

    if(r == NULL){
        return NULL;
    }

    while(i<2*d && r.v[i] !=0 && r.chave[i] < v){
            i++;
        if(r.v[i] == v){
            return r;
        }
        else {
            return buscaJairo(r.filho[i], v);
        }
    }
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
