#ifndef HASHLIB_H_INCLUDED                    //considera o "hashlib.h" incluído
#define HASHLIB_H_INCLUDED                    //considera o "hashlib.h" incluído
#define HASHSIZE 1000                         // tamanho da tabela de hashing

typedef struct HashNode HashNode;             // nó da tabela de hashing
typedef HashNodePtr HashTable[HASHSIZE];      // tipo da tabela de hashing
typedef struct HashNode *HashNodePtr;         // apontador para um nó da tabela de hashing


void initHashTable(HashTable);                // inicia uma tabela de hashing
void hashInsert(char*, void*, HashTable);     // insere (chave,valor) numa tabela de hashing
void *hashSearch(char *, HashTable);          // busca pelo valor associado a uma chave


unsigned int hash(const char *key);           // função de hash
HashNode *achar_hashnode(const char *key);

#endif                                        // HASHLIB_H_INCLUDED
