#include <stdio.h>
#include <stdlib.h>

void PrintfVetor(char vetor[], char tamanho);
void CopiaVetor(char vetor_in[], char vetor_out[], int tamanho);

int main(int argc, char* argv[])
{
        char *L_ant, *L_atu;
        int n, k, bit;
        int N, linhas, regra;
////////////////////////////////////////////////////////////////  /* Obtem dados de entrada */
        printf("Digite o comprimento da linha: ");            //
        scanf("%d", &N);                                      //
        printf("Digite o numero de linhas: ");                //
        scanf("%d", &linhas);                                 //
        printf("Digite a regra a ser utilizada (0 a 255): "); //
        scanf("%d", &regra);                                  //
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////   /* Aloca espaco para o vetor atual e o anterior */
        L_ant = (char*) malloc(N*sizeof(char));               //
        L_atu = (char*) malloc(N*sizeof(char));               //
////////////////////////////////////////////////////////////////

        for(n=0; n<N; n++)                                         /* Criacao da linha inicial */
                L_ant[n] = 0;                                      /* Preenche a linha inicial com zeros */

        L_ant[N/2] = 1;                                            /* Insere o valor 1 na posicao do meio da linha inicial */
        L_atu[0] = L_atu[N-1] = 0;                                 /* Define que na linha atual, a primeira posicao e a ultima serao sempre iguais a 0 */
        PrintfVetor(L_ant, N);                                     /* Escreve a linha inicial na tela */

        for(k=2; k<=linhas; k++){                                  /* Percorre cada posicao da linha atual, exceto a primeira e a ultima posicoes */
                for(n=1; n<N-1; n++){                              /* Obtem a regra para a posicao atual, e atualiza essa posicao na linha atual */
                        bit = L_ant[n-1]*4+L_ant[n]*2+L_ant[n+1];
                        L_atu[n] = (regra&(1<<bit))!=0;
                }
                PrintfVetor(L_ant, N);                             /* Escreve a linha atual na tela */
                CopiaVetor(L_atu, L_ant, N);                       /* Atualiza a linha anterior */
        }
        free(L_ant);                                               /* Libera a memoria dinamica das linhas */
        free(L_atu);                                               /* Libera a memoria dinamica das linhas */
        return 0;
}

void PrintfVetor(char vetor[], char tamanho){
        int n;
        for(n=0; n<tamanho; n++)
                printf("%d ", vetor[n]);
        puts("");
}

void CopiaVetor(char vetor_in[], char vetor_out[], int tamanho){
        int n;
        for(n=0; n<tamanho; n++)
                vetor_out[n] = vetor_in[n];
}
