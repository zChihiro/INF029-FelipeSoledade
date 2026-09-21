#ifndef UTILITARIOS_H
#define UTILITARIOS_H
#include "use.h"
#include "aluno.h"
#include "professor.h"


int Checklist_Aluno(Aluno lista_aluno[], int qtdAluno, int x);
int search_id(Aluno lista_aluno[], int qtdAluno, int x);

int Checklist_Professor(Professor lista_professor[], int qtdProfessor, int x);
int search_id_professor(Professor lista_professor[], int qtdProfessor, int x);

int Verify_Date(Data d); 
int valid_cpf(char *cpf);
int invalid_id(int x);
char valid_sex();
void name_read(char *texto);
void caracter_read(char *texto);
void new_format(char name[]);
void limpar_buffer();
int ler_int(int *n);

#endif