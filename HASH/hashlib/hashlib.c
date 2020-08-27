#include <stdio.h>
#include <stdlib.h>
#include "hashlib.h"

struct HashNode {                              // nó da tabela de hashing
                    char *key;                       /* chave de busca      */
                    void *valueptr;                  /* valor associado     */
                    HashNodePtr next;                /* apontado p/ próximo */
                } HashNode;


unsigned int hashInsert(HashNode *h)           // Registra um HashNode no array
{
    unsigned int posicao;
    if(h == NULL)
        exit(1);

    posicao = hash(h->key);

    if(hashnode[posicao] == NULL)                    /* Posicao vazia, basta incluir a HashNode aqui */
    {
        hashnode[posicao] = h;
    }

    else                                             /* Houve uma colisao entre as posicoes, devemos usar o campo "next" */
    {
        HashNode *tmp = hashnode[posicao];
        while(tmp->next != NULL) tmp = tmp->next;
        tmp->next= h;
    }

    printf("registrado em %u.\n", posicao);
    return(posicao);
}






HashNode *achar_hashnode(const char *key)
{
    unsigned int posicao = hash(key);
    HashNode *h = hashnode[posicao];

    for(; h!=NULL ; h = h->next)
    {
        /* Nome foi encontrado */
        if(strcmp(h->key, key) == 0)
        {
            printf("HashNode encontrado em %u.\n", posicao);
            return(h);
        }
    }
    printf("HashNode nao encontrado.\n");                       // Se a funcao chegar aqui, o loop terminou sem encontrar o HashNode, entao ele nao existe
    return(NULL);
}




////////////////////////////////////////////////////////////////////////////////////////////////////// FUNÇÕES DE HASH:
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int hash(const char *key)            // Dado um KEY, retorna um numero no intervalo [0,HASHSIZE[
{
    char *h = key;
    unsigned int soma = 0;

    while(*h != 0) /* caractere nulo indica fim da string */
    {
        soma += *h;
        h++;
    }

    return(soma % HASHSIZE);
}
