#ifndef HASHLIB_H_INCLUDED                    //considera o "hashlib.h" inclu�do
#define HASHLIB_H_INCLUDED                    //considera o "hashlib.h" inclu�do
#define HASHSIZE 1000                         // tamanho da tabela de hashing

typedef struct HashNode HashNode;             // n� da tabela de hashing
typedef HashNodePtr HashTable[HASHSIZE];      // tipo da tabela de hashing
typedef struct HashNode *HashNodePtr;         // apontador para um n� da tabela de hashing


void initHashTable(HashTable);                // inicia uma tabela de hashing
void hashInsert(char*, void*, HashTable);     // insere (chave,valor) numa tabela de hashing
void *hashSearch(char *, HashTable);          // busca pelo valor associado a uma chave


unsigned int hash(const char *key);           // fun��o de hash
HashNode *achar_hashnode(const char *key);

#endif                                        // HASHLIB_H_INCLUDED
