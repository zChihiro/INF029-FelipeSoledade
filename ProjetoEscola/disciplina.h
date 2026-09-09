#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#define TAM_DISCIPLINA 3
#define TAM_NOME 50

typedef struct {
    int codigo;
    char nome[TAM_NOME];
    int ativa;
} Disciplina;






#endif