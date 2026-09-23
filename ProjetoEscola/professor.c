#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "use.h"
#include "professor.h"
#include "utilitarios.h"


int menuProfessor() {
    printf("======== Modulo Professor ========\n\n");
    int opcaoProfessor;

    printf("0 - Sair\n");
    printf("1 - Cadastrar Professor\n");
    printf("2 - Listar Professores\n");
    printf("3 - Listar Professores Sexo\n");
    printf("4 - Listar Professores Nome\n");
    printf("5 - Listar Professores Data\n");
    printf("6 - Alterar Professor\n");
    printf("7 - Excluir Professor\n");
    printf("Digite a sua opcao: ");
    scanf("%d", &opcaoProfessor);

    return opcaoProfessor;
}

int cadastrarProfessor(Professor lista_professor[], int qtdProfessor) {

    if(qtdProfessor == TAM_PROFESSOR) {
        printf("Lista de professores cheia. Nao foi possivel cadastrar.\n\n");
        return 0;
    }
    Professor novoProfessor;

    printf("********** Cadastro Professor **********\n\n");
    printf("Digite a matricula: ");
    scanf("%d", &novoProfessor.matricula);

    if(Checklist_Professor(lista_professor, qtdProfessor, novoProfessor.matricula)){
        printf("Matricula ja cadastrada. Tente novamente.\n\n");
        return 0;
    }

    printf("Digite o nome completo do professor: ");
    name_read(novoProfessor.name);
    new_format(novoProfessor.name);

    do {
        printf("Digite a data de nascimento xx/xx/xxxx--->: ");
        scanf("%d/%d/%d", &novoProfessor.date_birth.dia,
                          &novoProfessor.date_birth.mes,
                          &novoProfessor.date_birth.ano);

        if(!Verify_Date(novoProfessor.date_birth))
        printf("Data invalida, tente novamente.\n");

    } while(!Verify_Date(novoProfessor.date_birth));


    do {
        printf("Digite seu CPF(***.***.***.**): ");
        name_read(novoProfessor.cpf);

        if(!valid_cpf(novoProfessor.cpf)){
            printf("CPF digitado de forma incorreta. Tente novamente!\n");
        }
    } while(!valid_cpf(novoProfessor.cpf));

    novoProfessor.sexo = valid_sex();
    novoProfessor.ativo = 1;

    lista_professor[qtdProfessor] = novoProfessor;

    printf("\n**Professor cadastrado com sucesso.**\n\n");
    return 1;

}

void listarProfessores(Professor lista_professor[], int qtdProfessor) {

    if(qtdProfessor == 0){
        printf("Lista de professores vazia. Cadastre Professores para testes!\n\n");
    }else {
        for(int i = 0; i < qtdProfessor; i++) {
            if (lista_professor[i].ativo == 1) {
                printf(" ** Matricula: %d\n ** Nome: %s\n ** CPF: %s\n ** Sexo: %c\n ** Data: %02d/%02d/%d\n\n",
                        lista_professor[i].matricula,
                        lista_professor[i].name,
                        lista_professor[i].cpf,
                        lista_professor[i].sexo,
                        lista_professor[i].date_birth.dia,
                        lista_professor[i].date_birth.mes,
                        lista_professor[i].date_birth.ano);
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

void listarProfessoresSexo(Professor lista_professor[], int qtdProfessor) {

    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados\n\n");
        return;
    }

    char sexo;
    sexo = valid_sex();

    for(int i = 0; i < qtdProfessor; i++) {
        if(lista_professor[i].sexo == sexo)
            printf(" **Sexo: %c, **Nome: %s\n", lista_professor[i].sexo, lista_professor[i].name);
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

void listarProfessoresName(Professor *lista_professor, int qtdProfessor) {

    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados\n\n");
        return;
    }

    Professor copia_vetor[TAM_PROFESSOR];

    for(int i = 0; i < qtdProfessor; i++) {
        copia_vetor[i] = lista_professor[i];
    }

    ordenarProfessoresPorNome(copia_vetor, qtdProfessor);

    for(int i = 0; i < qtdProfessor; i++) {
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

void listarProfessoresData(Professor *lista_professor, int qtdProfessor) {

    if(qtdProfessor == 0) {
        printf("Nao ha professores cadastrados\n\n");
        return;
    }

    Professor copia_vetor[TAM_PROFESSOR];

    for(int i = 0; i < qtdProfessor; i++) {
        copia_vetor[i] = lista_professor[i];
    }

    ordenarProfessoresPorData(copia_vetor, qtdProfessor);

    for(int i = 0; i < qtdProfessor; i++) {
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

void atualizarProfessor(Professor lista_professor[], int qtdProfessor){

    int matricula;

    if(qtdProfessor == 0) {
       printf("Nao ha professores cadastrados\n\n");
    } else {
        printf("Digite a matricula: ");
        scanf("%d", &matricula);
        if(!invalid_id(matricula)) return;

        int id = search_id_professor(lista_professor, qtdProfessor, matricula);

        if(id != -1) {
        printf("Digite o novo nome: ");
        name_read(lista_professor[id].name);
        new_format(lista_professor[id].name);

            do {
                printf("Digite a data de nascimento xx/xx/xxxx--->: ");
                scanf("%d/%d/%d", &lista_professor[id].date_birth.dia,
                                  &lista_professor[id].date_birth.mes,
                                  &lista_professor[id].date_birth.ano);

                if(!Verify_Date(lista_professor[id].date_birth))
                printf("Data invalida, tente novamente.\n");

            } while(!Verify_Date(lista_professor[id].date_birth));

            do {
                printf("Digite seu CPF(***.***.***.**): ");
                name_read(lista_professor[id].cpf);

                if(!valid_cpf(lista_professor[id].cpf))
                printf("CPF digitado de forma incorreta. Tente novamente!\n");

            } while(!valid_cpf(lista_professor[id].cpf));

            lista_professor[id].sexo = valid_sex();
            lista_professor[id].ativo = 1;

            printf("Professor atualizado com sucesso.\n");

        } else {
            printf("Matricula Inexistente\n");
        }

    }
}

int excluirProfessor(Professor lista_professor[], int qtdProfessor){

    if(qtdProfessor == 0) {
        printf("Sem professores cadastrados no sistema\n\n");
        return 0;
    }
    else {
        int matricula;
        printf("Digite a matricula para remocao do professor: ");
        scanf("%d", &matricula);
        if(!invalid_id(matricula))
        return 0;

            int id = search_id_professor(lista_professor, qtdProfessor, matricula);

            if(id != -1) {

                for(int i = id; i < qtdProfessor-1; i++) {
                lista_professor[i] = lista_professor[i+1];
                }
              printf("Professor excluido com sucesso.\n\n");
              return 1;
            }
            else {
                printf("Matricula Invalida. Tente novamente\n\n");
                return 0;
            }
    }
}
