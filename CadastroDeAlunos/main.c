#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 120

/* a) */
typedef struct aluno {
	char nome[40];
	int ano;
	char curso[40];
	float media;
} aluno;


/* b) */
aluno * copia_aluno( aluno * a)
{
	aluno *t;

	t=(aluno *)malloc(sizeof(aluno));
	if (t==NULL)
		return t;

	*t = *a;
	/* ou:
	strcpy(t->nome,a->nome);
	t->ano = a->ano;
	strcpy(t->curso,a->curso);
	t->media = a->media;
	*/

	return t;
}


/* c) */
void guarda_aluno( aluno * a, char * filename)
{
	FILE *f;

	if (a==NULL) return;

	f = fopen(filename,"a");

	if (f==NULL) return;

	fprintf(f, "%s\t%d\t%s\t%f\n",a->nome,a->ano,a->curso,a->media);

	fclose(f);
}

/* exemplo */

void mostra_aluno(aluno * a)
{
	if (a==NULL) return;
	printf("\nnome:%s\nano:%d\ncurso:%s\nmedia:%f\n",a->nome,a->ano,a->curso,a->media);
}

void mostra_ficheiro(char * filename)
{
	FILE *f;
	char buf[MAX_BUF];

	f = fopen(filename,"r");

	if (f==NULL)
	{
		printf("\nErro na abertura do ficheiro \"%s\"!\n", filename);
		return;
	}

	printf("\nFicheiro \"%s\"\n", filename);

	fgets(buf, MAX_BUF, f);
	while (!feof(f))
	{
		printf("%s",buf);
		fgets(buf, MAX_BUF, f);
	}

	fclose(f);
}


int main(int argc, char* argv[])
{
	aluno a1 = {"Paulo Silva", 1999, "EI", 14.2F};
	aluno a2 = {"Ricardo Malheiro", 1998, "EEC", 12.8F};
	aluno a3 = {"Paula Oliveira", 1999, "SE", 15.1F};

	aluno * at;

	printf("\n\n\n\nAlunos:\n");

	mostra_aluno(&a1);
	mostra_aluno(&a2);
	mostra_aluno(&a3);

	printf("\n\n\n\nFicheiro Inicial:\n");

	mostra_ficheiro("teste.doc");

	printf("\n\n\n\nCópia 1:\n");
	at = copia_aluno(&a1);
	mostra_aluno(at);
	guarda_aluno(at,"c:\\testes.doc");

	printf("\n\nCópia 2:\n");
	at = copia_aluno(&a2);
	mostra_aluno(at);
	guarda_aluno(at,"c:\\testes.doc");

	printf("\n\n\n\n\nFicheiro Final:\n");

	mostra_ficheiro("c:\\testes.doc");

	return 0;
}
