/*
    Programamador  :   Fabiano Traple
    Nome do arquivo:   bd.h
*/

// Difine's de pré-compilação

#define BD_MAX_DB_ABERTOS  256
#define BD_MAX_CAMPOS      128

#define BD_VERDADEIRO  0
#define BD_FALSO      -1

#define BD_SN          1       // Equivalente a char
#define BD_TEXTO       2       // Equivalente a uma cadeia char
#define BD_DATA        3       // Equivalente a unsigned long int
#define BD_HORA        4       // Equivalente a unsigned long int
#define BD_NU_INTEIRO  5       // Equivalente a long int
#define BD_NU_DECIMAL  6       // Equivalente a float

// Estrutura do cabeçalho do BD

struct EST_Cabecalho
{
   unsigned int TamCabecalho;
   char Versao[8];
   unsigned long int QtdReg;
   unsigned long int QtdRegExcluidos;
   unsigned int TamRegistro;
   unsigned int QtdCampos;
};

// Estrutura do campo do BD

struct EST_Campo
{
   char Descricao[30];
   char Tipo;
   unsigned int Tamanho;
   unsigned int PosIni;
};

// Estrutura que contém os dados de todos arquivos abertos

struct EST_DBAbertos
{
   char Apelido[30];
   FILE*PonteiroArquivoBD;
   unsigned long int PosPonReg;
   struct EST_Cabecalho Cabecalho;
   struct EST_Campo Campo[BD_MAX_CAMPOS];
};

// Protótipos das funções

char*BD_Erro();

char BD_Criar( char*PA_NomeBD,
               struct EST_Campo*PA_Registros,
               unsigned int PA_QtdCampos );

char BD_Abrir( char*PA_NomeBD,
               char*PA_ApelidoBD );

char BD_Fechar();

char BD_SelecionaBD( char*PA_ApelidoBD );
int BD_NumeroCampo( char*PA_NomeCampo );

char BD_NovoReg();

char BD_GravaSN( char*PA_NomeCampo, char PA_Valor );
char BD_GravaTexto( char*PA_NomeCampo, char*PA_Valor );
char BD_GravaData( char*PA_NomeCampo, char*PA_Valor );
char BD_GravaHora( char*PA_NomeCampo, char*PA_Valor );
char BD_GravaNuInteiro( char*PA_NomeCampo, long int*PA_Valor );
char BD_GravaNuDecimal( char*PA_NomeCampo, float*PA_Valor );

char BD_LerSN( char*PA_NomeCampo, char PA_Valor );
char BD_LerTexto( char*PA_NomeCampo, char*PA_Valor );
char BD_LerData( char*PA_NomeCampo, char*PA_Valor );
char BD_LerHora( char*PA_NomeCampo, char*PA_Valor );
char BD_LerNuInteiro( char*PA_NomeCampo, long int*PA_Valor );
char BD_LerNuDecimal( char*PA_NomeCampo, float*PA_Valor );

unsigned long int BD_RegAtual();
unsigned long int BD_TotalReg();

char BD_IrParaReg( unsigned long int PA_NumeroRegistro );
char BD_IrParaProximoReg();
char BD_IrParaRegAnterior();
char BD_IrParaInicio();
char BD_IrParaFim();

char BD_Inicio();
char BD_Fim();

char BD_MarcarRegParaExclusao();
char BD_ExcluirRegMarcados();

char BD_CriarIndice( char*PA_NomeIN,
                     char*PA_NomeBD,
                     char*PA_NomeCampo );

char BD_AbrirIndice( char*PA_NomeIN );

char BD_ReorganizaIndice( char*PA_NomeIN );
