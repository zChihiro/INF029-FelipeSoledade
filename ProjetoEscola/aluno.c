#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "use.h"
#include "aluno.h"
#include "utilitarios.h"


int menuAluno() {
    printf("======== Modulo Aluno ========\n\n");
    int sairAluno = 0;
    int opcaoAluno;

    printf("0 - Sair\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Alunos\n");
    printf("3 - Listar Alunos Sexo\n"); 
    printf("4 - Listar Alunos Name\n"); 
    printf("5 - Listar Alunos Data\n"); 
    printf("6 - Alterar Aluno\n");
    printf("7 - Excluir Aluno\n");
    printf("Digite a sua opcao: ");
    scanf("%d", &opcaoAluno);

    return opcaoAluno;
}

int cadastrarAluno(Aluno lista_aluno[], int qtdAluno) {

    if(qtdAluno == TAM_ALUNO) {
        printf("Lista de alunos cheia. Nao foi possivel cadastrar.\n\n");
        return 0;
    }
    Aluno novoAluno;
    
    printf("********** Cadastro Aluno **********\n\n");
    printf("Digite a matricula: ");
    scanf("%d", &novoAluno.matricula);

    if(Checklist_Aluno(lista_aluno, qtdAluno, novoAluno.matricula)){
        printf("Matricula ja cadastrada. Tente novamente.\n\n");
        return 0;
    }

    printf("Digite o nome completo do aluno: ");
    name_read(novoAluno.name);
    new_format(novoAluno.name);

    do {
        printf("Digite a data de nascimento xx/xx/xxxx--->: ");
        scanf("%d/%d/%d", &novoAluno.date_birth.dia, 
                          &novoAluno.date_birth.mes, 
                          &novoAluno.date_birth.ano);
        
        if(!Verify_Date(novoAluno.date_birth))
        printf("Data invalida, tente novamente.\n");

    } while(!Verify_Date(novoAluno.date_birth));


    do {
        printf("Digite seu CPF(***.***.***.**): ");
        name_read(novoAluno.cpf);

        if(!valid_cpf(novoAluno.cpf)){
            printf("CPF digitado de forma incorreta. Tente novamente!\n");
        }
    } while(!valid_cpf(novoAluno.cpf));

    novoAluno.sexo = valid_sex();
    novoAluno.ativo = 1;

    lista_aluno[qtdAluno] = novoAluno;

    printf("\n**Aluno cadastrado com sucesso.**\n\n");
    return 1;

}

void listarAlunos(Aluno lista_aluno[], int qtdAluno) {

    if(qtdAluno == 0){
        printf("Lista de alunos vazia. Cadastre Alunos para testes!\n\n");
    }else {
        for(int i = 0; i < qtdAluno; i++) {
            if (lista_aluno[i].ativo == 1) {
                printf(" ** Matricula: %d\n ** Nome: %s\n ** CPF: %s\n ** Sexo: %c\n ** Data: %02d/%02d/%d\n\n",
                        lista_aluno[i].matricula,
                        lista_aluno[i].name,
                        lista_aluno[i].cpf,
                        lista_aluno[i].sexo,
                        lista_aluno[i].date_birth.dia,
                        lista_aluno[i].date_birth.mes,
                        lista_aluno[i].date_birth.ano);
            }
        }
        int retorno;
        do{
        printf("Digite 1 para retornar: ");
        scanf("%d", &retorno);
        if(retorno != 1){
            printf("Numero inválido.\n\n");
            retorno = 0;
        }
        } while(!retorno);
            return;
    }
}

void listarAlunosSexo(Aluno lista_aluno[], int qtdAluno) {

    if(qtdAluno == 0) {
    printf("Nao ha alunos matriculados.\n\n");
    return;
    }
    char sexo;
    
    sexo = valid_sex();
    
        for(int i = 0; i < qtdAluno; i++) {
            if(lista_aluno[i].sexo == sexo)
            printf(" **Sexo: %c, **Nome: %s\n", lista_aluno[i].sexo, lista_aluno[i].name);
        }
        printf("\n");

        int retorno;
        do{
        printf("Digite 1 para retornar: ");
        scanf("%d", &retorno);
        if(retorno != 1){
            printf("Numero inválido.\n\n");
            retorno = 0;
        }
        } while(!retorno);
        return;  
}

void listarAlunosName(Aluno *lista_aluno, int qtdAluno) {

    if(qtdAluno == 0) {
        printf("Nao ha alunos matriculados.\n\n");
        return;
    }

    Aluno copia_vetor[TAM_ALUNO];

    for(int i = 0; i < qtdAluno; i++) {
        copia_vetor[i] = lista_aluno[i];
    }

    ordenarAlunosPorNome(copia_vetor, qtdAluno);

    for(int i = 0; i < qtdAluno; i++) {
        printf(" ** Name %s\n", copia_vetor[i].name);
        printf("------------------------------------------\n");
    }

    int retorno;
    do{
        printf("Digite 1 para retornar: ");
        scanf("%d", &retorno);
        if(retorno != 1){
            printf("Numero inválido.\n\n");
            retorno = 0;
        }
    } while(!retorno);
    return;

}

void listarAlunosData(Aluno *lista_aluno, int qtdAluno) {

     if(qtdAluno == 0) {
        printf("Nao ha alunos matriculados.\n\n");
        return;
    }

    Aluno copia_vetor[TAM_ALUNO];

    for(int i = 0; i < qtdAluno; i++) {
        copia_vetor[i] = lista_aluno[i];
    }

    ordenarAlunosPorData(copia_vetor, qtdAluno);

    for(int i = 0; i < qtdAluno; i++) {
        printf(" **Data: %02d/%02d/%d\n", 
            copia_vetor[i].date_birth.dia,
            copia_vetor[i].date_birth.mes,
            copia_vetor[i].date_birth.ano);
    }

    int retorno;
    do{
        printf("Digite 1 para retornar: ");
        scanf("%d", &retorno);
        if(retorno != 1){
            printf("Numero inválido.\n\n");
            retorno = 0;
        }
    } while(!retorno);
    return;
}    

void atualizarAluno(Aluno lista_aluno[], int qtdAluno){

    int matricula;
    
    if(qtdAluno == 0) {
       printf("Nao ha alunos matriculados\n\n");
       return;
    } else {
        printf("Digite a matricula: ");
        scanf("%d", &matricula);
        if(!invalid_id(matricula)) return;

        int id = search_id(lista_aluno, qtdAluno, matricula);

        if(id != -1) {
        printf("Digite o novo nome: ");
        name_read(lista_aluno[id].name);
        new_format(lista_aluno[id].name);
            
            do {
                printf("Digite a data de nascimento xx/xx/xxxx--->: ");
                scanf("%d/%d/%d", &lista_aluno[id].date_birth.dia, 
                                  &lista_aluno[id].date_birth.mes, 
                                  &lista_aluno[id].date_birth.ano);
                    
                if(!Verify_Date(lista_aluno[id].date_birth))
                printf("Data invalida, tente novamente.\n");

            } while(!Verify_Date(lista_aluno[id].date_birth));

            do {
                printf("Digite seu CPF(***.***.***.**): ");
                name_read(lista_aluno[id].cpf);

                if(!valid_cpf(lista_aluno[id].cpf))
                printf("CPF digitado de forma incorreta. Tente novamente!\n");
                
            } while(!valid_cpf(lista_aluno[id].cpf));

            lista_aluno[id].sexo = valid_sex();
            lista_aluno[id].ativo = 1;

            printf("Aluno atualizado com sucesso.\n");


        } else {
            printf("Matricula Inexistente\n");
        }

    }        
}

int excluirAluno(Aluno lista_aluno[], int qtdAluno){

    if(qtdAluno == 0) {
        printf("Sem alunos cadastrados no sistema.\n\n");
        return 0;
    }
    else {
        int matricula;
        printf("Digite a matricula para remocao do aluno: ");
        scanf("%d", &matricula);
        if(!invalid_id(matricula)) return 0;
       
    
            int id = search_id(lista_aluno, qtdAluno, matricula);

            if(id != -1) {
            
                for(int i = id; i < qtdAluno-1; i++) {
                lista_aluno[i] = lista_aluno[i+1];
                }
              printf("Aluno excluido com sucesso.\n\n");
              return 1;  
            } 
            else {
                printf("Matricula Invalida. Tente novamente\n\n");
                return 0;
            }
    }
}
