#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "bd.h"

// definindo variáveis globais


// Variável qie irá conter a descrição do último erro

char PR_DesUltErro[256];

//Cria uma lista usando a estrutura EST_DBAbertos para manter uma relação dos arquivos abertos

struct EST_DBAbertos ListaDBAbertos[BD_MAX_DB_ABERTOS];
unsigned int PR_QtdBDAberto = 0; // Quantidade de BD abertos
unsigned int PR_BDAtual = 0;     // BD Atualmente ativo







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função:   Criar um BD vazio, gravando apenas seu cabeçalho
         Parâmetro         :   char*PA_NomeBD > Nome do BD
         Parâmetro         :   struct EST_Campo*PA_Registros > Estrutura do registro que irá conter a lista de campos
         Parâmetro         :   unsigned int PA_QuantCampos > Quantidade de campos da Estrutura do registro
         Retorno           :   Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso ocorra erro
*/

char BD_Criar( char*PA_NomeBD,
               struct EST_Campo*PA_Campos,
               unsigned int PA_QtdCampos )
{
   //-----> Cria o arquivo de BD

   FILE*LO_PonteiroArquivoBD = fopen( PA_NomeBD, "wb");

   // Verifica se houve erro ao criar o arquivo

   if( LO_PonteiroArquivoBD == NULL )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "Erro ao criar o arquivo [" );
      strcat( PR_DesUltErro, PA_NomeBD );
      strcat( PR_DesUltErro, "]!\n");
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   //-----> Cria cabeçalho do BD

   struct EST_Cabecalho Temp;

   Temp.TamCabecalho = sizeof(struct EST_Cabecalho) + PA_QtdCampos*sizeof(struct EST_Campo);
   strcpy( Temp.Versao, "20060830"); //Data da última alteração feita no código fonte do DB
   Temp.QtdReg = 0;
   Temp.QtdRegExcluidos = 0;

   Temp.TamRegistro = 1; // Adiciona caracter de controle ao tamanho do registro
   int LO_Con;
   for( LO_Con = 0; LO_Con < PA_QtdCampos; LO_Con++)
   {
      PA_Campos[LO_Con].PosIni = Temp.TamRegistro;
      Temp.TamRegistro = Temp.TamRegistro + PA_Campos[LO_Con].Tamanho;
   }

   Temp.QtdCampos = PA_QtdCampos;

   // Grava cabeçalho

   fwrite( &Temp, sizeof(struct EST_Cabecalho), 1, LO_PonteiroArquivoBD);
   fwrite( &PA_Campos[0], (PA_QtdCampos*sizeof(struct EST_Campo)), 1, LO_PonteiroArquivoBD);

   // fecha o arquivo

   fclose( LO_PonteiroArquivoBD );

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função  :   Abrir um BD
         Parâmetro           :   char*PA_NomeBD > Nome do BD
         Parâmetro           :   char*PA_ApelidoBD > Apelidado do BD
         Retorno             :   Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso ocorra erro
*/

char BD_Abrir( char*PA_NomeBD,
               char*PA_ApelidoBD )
{
   //-----> Cria o arquivo de BD

   /*
   A função open() ao utilizar as flags "r+b"
   Caso o arquivo não exista retorna erro
   Caso exista abre
   */

   ListaDBAbertos[PR_QtdBDAberto].PonteiroArquivoBD = fopen( PA_NomeBD, "r+b");

   // Verifica se houve erro ao criar o arquivo

   if( ListaDBAbertos[PR_QtdBDAberto].PonteiroArquivoBD == NULL )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "Erro ao abrir o arquivo [" );
      strcat( PR_DesUltErro, PA_NomeBD );
      strcat( PR_DesUltErro, "]!\n");
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   // Carregando cabeçalho do BD

   fread( &ListaDBAbertos[PR_QtdBDAberto].Cabecalho,
          sizeof(struct EST_Cabecalho), 1,
          ListaDBAbertos[PR_QtdBDAberto].PonteiroArquivoBD);

   fread( &ListaDBAbertos[PR_QtdBDAberto].Campo,
          (ListaDBAbertos[PR_QtdBDAberto].Cabecalho.QtdCampos*sizeof(struct EST_Campo)), 1,
          ListaDBAbertos[PR_QtdBDAberto].PonteiroArquivoBD);

   // Adiciona apelido

   strcpy( ListaDBAbertos[PR_QtdBDAberto].Apelido, PA_ApelidoBD);


   PR_QtdBDAberto++;               // Adiciona +1 na quantidade de BD abertos
   PR_BDAtual = PR_QtdBDAberto-1;  // Altera o BD aberto atual

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função   :    Fechar um BD aberto anteriormente
         Parâmetro            :    char*PA_ApelidoBD > Apelidado do BD
         Retorno              :    Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso ocorra erro
*/
char BD_Fechar()
{
   // Verifica se existe arquivo aberto

   if( PR_QtdBDAberto == 0 )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_Fechar: Nenhum arquivo aberto para ser fechado!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   // Fechando arquivo

   int LO_Erro = fclose( ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD );

   // Verifica se houve erro ao fechar o arquivo

   if( LO_Erro != 0 )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_Fechar: Erro ao fechar o arquivo!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função    :   Selecionar o BD ativo atualmente
         Parâmetro             :   char*PA_ApelidoBD > Apelidado do BD
         Retorno               :   Retorna a posição do apelido na lista de arquivos abertos ou -1 caso não exita
*/
char BD_SelecionaBD( char*PA_ApelidoBD )
{

   // Verifica se o apelido dado como paramentro existe na lista de arquivos abertos

   int LO_PosLisBD;
   for( LO_PosLisBD = 0; LO_PosLisBD < PR_QtdBDAberto; LO_PosLisBD++)
   {
      if( strcmp( ListaDBAbertos[LO_PosLisBD].Apelido, PA_ApelidoBD ) == 0 )
      {
         PR_BDAtual = LO_PosLisBD;
         return( BD_VERDADEIRO );
      }
   }

   if( LO_PosLisBD == PR_QtdBDAberto )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_SelecionaBD: Apelido desconhecido!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função   :   Cria um novo registro em branco no fim do BD
         Parâmetro            :   char*PA_ApelidoBD > Apelidado do BD
         Retorno              :   Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso não
*/
char BD_NovoReg()
{
   // Verifica se existe arquivo aberto

   if( PR_QtdBDAberto == 0 )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_NovoReg: Nenhum arquivo aberto para ser fechado!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   // Criando registro em branco no final do arquivo

   char*LO_RegistroVazio = (char*) malloc( ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro );
   if( LO_RegistroVazio == NULL )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_NovoReg: Não foi possivel alocar a memória!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   fseek( ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD, 0, SEEK_END);

   fwrite( LO_RegistroVazio,
           ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro, 1,
           ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD);

   free( LO_RegistroVazio );

   ListaDBAbertos[PR_BDAtual].Cabecalho.QtdReg++;

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função   :   Grava dado no campo do registro atual
         Parâmetro            :   char*PA_NomeCampo > Nome do campo
         Parâmetro            :   char*PA_Valor > Valor que será gravado
         Retorno              :   Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso não
*/
char BD_GravaTexto( char*PA_NomeCampo, char*PA_Valor )
{
   // Verifica se existe arquivo aberto

   if( PR_QtdBDAberto == 0 )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_NovoReg: Nenhum arquivo aberto para ser fechado!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   int LO_NumCampo = BD_NumeroCampo( PA_NomeCampo );
   if( LO_NumCampo == BD_FALSO )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_Gravar: Nome do campo desconhecido!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }


   // Posiciona ponteiro do DB

   unsigned long int LO_PosPon = ListaDBAbertos[PR_BDAtual].Cabecalho.TamCabecalho+
                                 ((ListaDBAbertos[PR_BDAtual].Cabecalho.QtdReg-1)*
                                 ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro)+
                                 ListaDBAbertos[PR_BDAtual].Campo[LO_NumCampo].PosIni;

   int LO_TamCampo = 0;
   if( ListaDBAbertos[PR_BDAtual].Campo[LO_NumCampo].Tipo != BD_TEXTO )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_GravaTexto: O tipo deste campo não é texto!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }
   LO_TamCampo = strlen(PA_Valor);
   if( LO_TamCampo >  ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro )
   {
      LO_TamCampo = ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro;
   }

   fseek( ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD, LO_PosPon, SEEK_SET );
   fwrite( PA_Valor, LO_TamCampo, 1, ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD);

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função  : Grava dado no campo do registro atual
         Parâmetro           :   char*PA_NomeCampo > Nome do campo
         Parâmetro           :   long int*PA_Valor > Valor que será gravado
         Retorno             :   Retorna BD_VERDADEIRO caso bem sucedido ou BD_FALSO caso não
*/
char BD_GravaNuInteiro( char*PA_NomeCampo, long int*PA_Valor )
{
   // Verifica se existe arquivo aberto

   if( PR_QtdBDAberto == 0 )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_NovoReg: Nenhum arquivo aberto para ser fechado!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   int LO_NumCampo = BD_NumeroCampo( PA_NomeCampo );
   if( LO_NumCampo == BD_FALSO )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_Gravar: Nome do campo desconhecido!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }


   // Posiciona ponteiro do DB

   unsigned long int LO_PosPon = ListaDBAbertos[PR_BDAtual].Cabecalho.TamCabecalho+
         ((ListaDBAbertos[PR_BDAtual].Cabecalho.QtdReg-1)*
         ListaDBAbertos[PR_BDAtual].Cabecalho.TamRegistro)+
         ListaDBAbertos[PR_BDAtual].Campo[LO_NumCampo].PosIni;

   int LO_TamCampo = sizeof(long int);
   if( ListaDBAbertos[PR_BDAtual].Campo[LO_NumCampo].Tipo != BD_NU_INTEIRO )
   {
      memset( PR_DesUltErro, '\0', 256 );
      strcpy( PR_DesUltErro, "BD_GravaTexto: O tipo deste campo não é um inteiro numérico!" );
      printf("%s\n", PR_DesUltErro);
      return( BD_FALSO );
   }

   fseek( ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD, LO_PosPon, SEEK_SET );
   fwrite( &PA_Valor, LO_TamCampo, 1, ListaDBAbertos[PR_BDAtual].PonteiroArquivoBD);

   return( BD_VERDADEIRO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
         Objetivo da função  :   Verificar se o nome do campo existe e retorna a sua posição
         Parâmetro           :   char*PA_NomeCampo > Nome do campo
         Retorno             :   Retorna a posição do campo ou DB_FALSO caso dê erro
*/
int BD_NumeroCampo( char*PA_NomeCampo )
{
   int LO_NumCampo;
   for( LO_NumCampo = 0; LO_NumCampo < ListaDBAbertos[PR_BDAtual].Cabecalho.QtdCampos; LO_NumCampo++)
   {
      if( strncmp( ListaDBAbertos[PR_BDAtual].Campo[LO_NumCampo].Descricao, PA_NomeCampo, strlen(PA_NomeCampo) ) == 0 )
      {
         return( LO_NumCampo );
         break;
      }
   }
   return( BD_FALSO );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









