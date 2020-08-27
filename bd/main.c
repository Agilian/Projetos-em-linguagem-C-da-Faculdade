/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
      Abaixo est� o codigo que estou usando para testes...
*/
#include <string.h>
#include <stdio.h>

#include "bd.h"

// Descomente essas linhas abaixo conforme seu sistema operacional

//#define PU_SO linux
#define PU_SO  windows

int main()
{
   // Limpa a tela

   //#if( PU_SO == linux )
   //{
//      system( "clear" );  // Essa fun��o limpa a tela no linux
//   }
//   #else
//  {
      system( "cls" ); // Essa fun��o limpa a tela no windows
//   }
//   #endif

   // Inicia o teste

   printf( "Iniciando teste de cria��o do DB...\n" );


   // Criando estrutura de um cadastro de clientes para teste

   struct EST_Campo Clientes[3];

   // Campo 1

   memset( Clientes[0].Descricao, '\0', 30);
   strcpy( Clientes[0].Descricao, "Nome\n" );
   Clientes[0].Tipo = BD_TEXTO;
   Clientes[0].Tamanho = 60;

   // Campo 2

   memset( Clientes[1].Descricao, '\0', 30);
   strcpy( Clientes[1].Descricao, "Rua\n" );
   Clientes[1].Tipo = BD_TEXTO;
   Clientes[1].Tamanho = 40;

   // Campo 3

   memset( Clientes[2].Descricao, '\0', 4);
   strcpy( Clientes[2].Descricao, "Numero\n" );
   Clientes[2].Tipo = BD_NU_INTEIRO;
   Clientes[2].Tamanho = 4;

   printf( "Iniciando!\n" );


   // Criando banco de dados

   BD_Criar( "Clientes.bd", Clientes, 3 );

   // Abrindo banco de dados

   BD_Abrir( "Clientes.bd", "Clientes" );

   // Cria um novo registro

   long int LO_Con;
   for( LO_Con = 0; LO_Con < 10000; LO_Con++)
   {
      BD_NovoReg( "Clientes" );
      BD_GravaTexto( "Nome"  , "Jo�o da Silva Pereira Rocanbole" );
      BD_GravaTexto( "Rua"   , "Rua do p� de Laranja" );
      BD_GravaNuInteiro( "Numero", &LO_Con );
   }

   // Fechando banco de dados

   BD_Fechar( "Clientes" );

   printf( "Fim!\n" );

   return(0);
}


/*
    Agora Tenho uma d�vida...

    Nas fun��es de grava��o acima eu gravo campo a campo no registro do BD, o que deixa ele lento ao se gravar grandes blocos sequenciais de informa��o, estava pensando em cria uma fun��o especial para gravar e ler o registro inteiro !

    Ser� que havera muita diferen�a?
    Quais seriam as aplica��es dessa rotina?
    Ser� que tenho que fazer uma fun��o de verifica��o da estrutura do registro para que n�o cause erro, nessa nova rotina ?
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
