#include <stdio.h>
#include <stdlib.h>

long semente = 0; //semente da funcao rand

//gera um valor aleatorio entre mim e max
int valAleatorio(int min, int max){
    int v; //variavel auxiliar

    if(!semente){ //atualiza a semente
        time(&semente);
        srand((unsigned)semente);
    }

    v = min + rand() % (max - min + 1); // gera o valor aleatorio

    return v;
}

//aloca uma tabela para armazenar n(= numChave) chaves, do tipo string, de tamanho tamChave
int **geraTabela(int numChave, int tamChave){
    int **Tabela; //ponteiro para a tabela
    int i; //variavel auxiliar
    if (numChave < 1 || tamChave < 1){  //verifica se os parametros estão corretos
        printf("** ERRO: Parametro Invalido! **\n");
        return 0;
    }

    //aloca as linhas da Tabela, que correspondem ao numero de strings armazenadas na tabela
    Tabela = malloc(numChave * sizeof(int));
    if (Tabela == NULL){  //verifica se a Tabela foi alocada
        printf("** ERRO: Memoria Insuficiente! **");
        return 0;
    }

    //aloca as colunas da Tabela, que corresponde ao tamnho maximo das strings a serem armazenadas na Tabela
    for(i=0;i<numChave;i++){
        Tabela[i] = malloc(tamChave * sizeof(int));
        if (Tabela[i] == NULL){  //verifica se as colunas na linha i foram alocadas
            printf("** ERRO: Memoria Insuficiente! **");
            return 0;
        }
    }
    return Tabela;
}

//desaloca a Tabela
int liberaTabela(int numChave, int tamChave, int **Tb){
    int i; //variavel auxiliar

    if (Tb == NULL) //verifica se a Tabela está vazia
        return 0;

    if (numChave < 1 || tamChave < 1){ //verifica se os parametros estao corretos
        printf("** ERRO: Parametro Invalido! **");
        return Tb;
    }

    for(i=0;i<numChave;i++) //libera as colunas
        free(Tb[i]);

    free(Tb); //libera as linhas

    return 1;
}

//atualiza a tabela Tb com valores aleatorios
int geraTabAleatoria(int numChave, int tamChave, int **Tb){
    int i,j,t; //variaveis auxiliares

    if (Tb == NULL) //verifica se a Tabela está vazia
        return 0;

    if (numChave < 1 || tamChave < 1){ //verifica se os parametros estao corretos
        printf("** ERRO: Parametro Invalido! **");
        return Tb;
    }

    //gera e armazena os valores da tabela Tb
    for(i=0;i<numChave;i++){
        for(j=0;j<tamChave;j++){
            t = valAleatorio(1,3);//direciona para a faixa de valores da tabela ASCii(48 a 57, 65 a 90 ou 97,122)
                                  //e em seguida gera um caracter aleatorio nessa faixa
            if(t == 1)
                Tb[i][j] = valAleatorio(48,57);
            else if (t == 2)
                Tb[i][j] = valAleatorio(65,90);
            else
                Tb[i][j] = valAleatorio(97,122);
        }

        //enquanto a ultima string for igual a uma das demais, trocamos ela por uma outra gerada aleatoriamente
        while (comparaString(Tb,i+1,tamChave)==1){
            for(j=0;j<tamChave;j++){
                t = valAleatorio(1,3);

                if(t == 1)
                    Tb[i][j] = valAleatorio(48,57);
                else if (t == 2)
                    Tb[i][j] = valAleatorio(65,90);
                else
                    Tb[i][j] = valAleatorio(97,122);
            }
        }
    }

    return Tb;
}

// imprime todas as strings da tabela
int imprimeTabela(int numChave, int tamChave, int **Tb){
    int i,j; //variaveis auxiliares

    if (Tb == NULL) //verifica se a Tabela esta vazia
        return 0;

    if (numChave < 1 || tamChave < 1){ //verifica se os parametros estao corretos
        printf("** ERRO: Parametro Invalido! **");
        return Tb;
    }

    printf("Tabela de Strings:\n");

    //imprime as strings da tabela TB
    for(i=0;i<numChave;i++){
        for(j=0;j<tamChave;j++)
            printf("%c", Tb[i][j]);
        printf("\n");
    }

    return 0;
}

//compara a ultima string inserida com as demais para verificar se existe alguma igual a ela
int comparaString(int **Tb, int numChave, int tamChave){
    int i,j,cont = 0; //variaveis auxiliares

    if (Tb == NULL) //verifica se a Tabela esta vazia
        return 0;

    if(tamChave < 1 || numChave < 1){ //verifica se os parametros estao corretos
        printf("** Parametro Invalido! **");
        return 0;
    }

    if (numChave == 1) //se numChave tiver um elemento, nao existe strings iguais
        return 0;

    //verifica se existe strings iguais
    for(i=0;i<numChave;i++){
        for(j=0;j<tamChave;j++){
            if(Tb[i][j] == Tb[numChave-1][j])
                cont ++;
        }
    }

    //se cont for igual a tamChave significa q as strings sao iguais
    //qualquer outro valor indica que as strings sao diferentes
    if(cont == tamChave)
        return 1;
    else
        return 0;
}

int main()
{
    int numChave, tamChave;
    int **Tabela;

    numChave = 10;
    tamChave = 5;

    Tabela = geraTabela(numChave,tamChave);

    Tabela = geraTabAleatoria(numChave,tamChave,Tabela);

    //comparaString(Tabela,numChave,tamChave);

    imprimeTabela(numChave,tamChave,Tabela);

    liberaTabela(numChave,tamChave,Tabela);

    return 0;
}
