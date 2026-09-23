#ifndef RELATORIO_H
#define RELATORIO_H
#include <time.h>
#include "use.h"
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include "utilitarios.h"


int menuRelatorios(void);
void buscarAlunoPorNome(Aluno lista_aluno[], int qtdAluno);
void buscarProfessorPorNome(Professor lista_professor[], int qtdProfessor);
void listarAlunosMenosDe3Disciplinas(Aluno lista_aluno[], int qtdAluno, Disciplina lista_disciplina[], int qtdDisciplina);
void aniversariantesAluno(Aluno lista_aluno[], int qtdAluno);
void aniversariantesProfessor(Professor lista_professor[], int qtdProfessor);



#endif