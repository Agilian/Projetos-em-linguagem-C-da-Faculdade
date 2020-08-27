/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
      Abaixo está o codigo que estou usando para testes...
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
//      system( "clear" );  // Essa função limpa a tela no linux
//   }
//   #else
//  {
      system( "cls" ); // Essa função limpa a tela no windows
//   }
//   #endif

   // Inicia o teste

   printf( "Iniciando teste de criação do DB...\n" );


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
      BD_GravaTexto( "Nome"  , "João da Silva Pereira Rocanbole" );
      BD_GravaTexto( "Rua"   , "Rua do pé de Laranja" );
      BD_GravaNuInteiro( "Numero", &LO_Con );
   }

   // Fechando banco de dados

   BD_Fechar( "Clientes" );

   printf( "Fim!\n" );

   return(0);
}


/*
    Agora Tenho uma dúvida...

    Nas funções de gravação acima eu gravo campo a campo no registro do BD, o que deixa ele lento ao se gravar grandes blocos sequenciais de informação, estava pensando em cria uma função especial para gravar e ler o registro inteiro !

    Será que havera muita diferença?
    Quais seriam as aplicações dessa rotina?
    Será que tenho que fazer uma função de verificação da estrutura do registro para que não cause erro, nessa nova rotina ?
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
