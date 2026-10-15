// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <string.h>
#include <stdlib.h>

int SoDigitos(char []);
int eh_bissexto(int x);
int validar_dia_mes_ano(DataQuebrada d);
int contar_caracters(char *texto, char c, int x);
int inverter_num(int x);
int matriz_esquerda(char matriz[8][10], char palavra[5], int x, int y, int n);
int matriz_direita(char matriz[8][10], char palavra[5], int x, int y, int n);
int matriz_cima(char matriz[8][10], char palavra[5], int x, int y, int n);
int matriz_baixo(char matriz[8][10], char palavra[5], int x, int y, int n);
int diagonal_esquerda_cima(char matriz[8][10], char palavra[5], int x, int y, int n);
int diagonal_direita_cima(char matriz[8][10], char palavra[5], int x, int y, int n);
int diagonal_esquerda_baixo(char matriz[8][10], char palavra[5], int x, int y, int n);
int diagonal_direita_baixo(char matriz[8][10], char palavra[5], int x, int y, int n);
DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    DataQuebrada dq = quebraData(data);
    int datavalida = 1;

    if(dq.valido == 0)
        datavalida = 0;

    if (datavalida)
        return 1;
    else
        return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
        DataQuebrada ini = quebraData(datainicial);
        DataQuebrada fim = quebraData(datafinal);

        int numIni = ini.iAno * 10000 + ini.iMes * 100 + ini.iDia;
        int numFim = fim.iAno * 10000 + fim.iMes * 100 + fim.iDia;

        if( numIni > numFim) {
            dma.retorno = 4;
            return dma;
        }

        int day_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int dias = fim.iDia - ini.iDia;
        int mes = fim.iMes - ini.iMes;
        int ano = fim.iAno - ini.iAno;

        
        if (dias < 0) {
        int mesEmprestimo = fim.iMes - 1;
            
            if (mesEmprestimo == 0) {
                mesEmprestimo = 12;
            }
            int diasEmprestimo = day_mes[mesEmprestimo];
 
            if(mesEmprestimo == 2 && eh_bissexto(fim.iAno)){
                diasEmprestimo = 29;
            }

        dias = diasEmprestimo + dias;
        mes--;
        }

        if(mes < 0) {
            ano--;
            mes+= 12;
        }
        
        dma.qtdDias = dias;
        dma.qtdMeses = mes;
        dma.qtdAnos = ano;
        dma.retorno = 1;
        return dma;

        
        
        //verifique se a data final não é menor que a data inicial
      
        //calcule a distancia entre as datas

        //se tudo der certo
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{   
    int qtdOcorrencias = -1;

    qtdOcorrencias = contar_caracters(texto, c, isCaseSensitive);

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int sizeText = strlen(strTexto);
    int sizeSearch = strlen(strBusca);
    
    if(sizeText == 0 || sizeSearch == 0) return 0;

    int n = 0;
    char new_text[strlen(strTexto) + 1]; //Para colocar o '\0' dps
    char new_search[strlen(strBusca) + 1]; //Para Colocar o '\0' dps.

    for(int i = 0; i < sizeText; i++) {
        if(strTexto[i] != -61) {//Diferenciar acento, já que consomem 2 espaços
        new_text[n] = strTexto[i];
        n++;
        }
    }
    new_text[n] = '\0';

    n = 0;
    for(int i = 0; i < sizeSearch; i++) {
        if(strBusca[i] != -61) {//Diferenciar acento, já que consomem 2 espaços
        new_search[n] = strBusca[i];
        n++;
        }
    }
    new_search[n] = '\0';
    int verify_two = 0;
    n = strlen(new_search);

    for(int i = 0; new_text[i] != '\0'; i++) {

        if(new_text[i] == new_search[0]) {
            int j = i + 1;
            int contem = 1;
            for(int k = 1; new_search[k] != '\0'; k++) {

                if(new_text[j] != new_search[k]){
                contem = 0;
                break;
                }
                j++;
            }
            
            if(contem == 1) {
            posicoes[verify_two] = i + 1;
            verify_two++;
            posicoes[verify_two] = i + n;
            verify_two++;
            qtdOcorrencias++;
            }
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{   
    num = inverter_num(num);
    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdDigitos = 0, divisor = 1, aux = numerobusca, qtd = 0;

    if (aux == 0)
        qtdDigitos = 1;
    while (aux > 0)
    {
        qtdDigitos++;
        aux = aux / 10;
    }

    for (aux = 0; aux < qtdDigitos; aux++)
        divisor = divisor * 10;

    while (numerobase > 0)
    {
        if (numerobase % divisor == numerobusca)
        {
            qtd++;
            numerobase = numerobase / divisor;
        }
        else
            numerobase = numerobase / 10;
    }
    return qtd;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
    int achou = 0;
    int tam = strlen(palavra);

    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 10; c++) {

            if (matriz[l][c] == palavra[0]) {

                if (diagonal_esquerda_cima(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (matriz_cima(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (diagonal_direita_cima(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (matriz_esquerda(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (matriz_direita(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (diagonal_esquerda_baixo(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (matriz_baixo(matriz, palavra, l, c, tam)) {
                    achou = 1;
                } else if (diagonal_direita_baixo(matriz, palavra, l, c, tam)) {
                    achou = 1;
                }

            }

            if (achou == 1) {
                break;              
            }
        }

        if (achou == 1) {
            break;                  
        }
    }

    return achou;
 }



int SoDigitos(char data[]){

    for(int i = 0; data[i] != '\0'; i++) {
         
        if(data[i] < '0' || data [i] > '9')
         return 0;
    }
    return 1;    
}

DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 
    int contar = 0;

    for(i = 0; data[i] != '\0'; i++){
        if(data[i] == '/')
        contar++;
    }

    if(contar != 2) {
        dq.valido = 0;
        return dq;
    } 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
        if(!SoDigitos(sDia)) {
            dq.valido = 0;    
        return dq;
        }

	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
        if(!SoDigitos(sMes)) {
            dq.valido = 0;    
        return dq;
        }
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
        if(!SoDigitos(sAno)) {
            dq.valido = 0;    
        return dq;
        }
	}else {
		dq.valido = 0;
    return dq;
  }

    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno); 
    if(dq.iAno < 100)
    dq.iAno += 2000;

    if(!validar_dia_mes_ano(dq)) {
        dq.valido = 0;

    return dq;
  }
  
  dq.valido = 1;
    
  return dq;
}

int eh_bissexto(int x) {
    if ((x % 4 == 0 && x % 100 != 0) || x % 400 == 0)
        return 1;
    return 0;
}

int validar_dia_mes_ano(DataQuebrada d) {

    

    int day_mes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (eh_bissexto(d.iAno))                 // 2º: chama com o ano (com parênteses!)
        day_mes[2] = 29;

    if (d.iMes < 1 || d.iMes > 12)           // 3º: mês ANTES de usar day_mes[mês]
        return 0;

    if (d.iDia < 1 || d.iDia > day_mes[d.iMes])
        return 0;

    return 1;                              
}


int contar_caracters(char *texto, char c, int x) {

    int contar = 0;

    if(x == 1) {
        for(int i = 0; texto[i] != '\0'; i++) {
            if(texto[i] == c)
                contar++;
        }
    }
    else{
        if(c >= 'A' && c <= 'Z') {
            c += 32;
        }
        for(int i = 0; texto[i] != '\0'; i++) {
            char aux = texto[i];
            if(texto[i] >= 'A' && texto[i] <= 'Z') {
                aux += 32;
            }
            if(aux == c)
                contar++;

        }
    }

    return contar;
}

int inverter_num(int x) {

    int aux = x;
    int invertido = 0;
    while(x != 0) {
        aux %= 10;
        invertido = invertido * 10 + aux;
        x /= 10;
        aux = x;
    }
    return invertido;
}


int matriz_esquerda(char matriz[8][10], char palavra[5], int x, int y, int n) {
    for(int k = 1; k < n; k++) {
        y--;

        if(y < 0 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;

}
int matriz_direita(char matriz[8][10], char palavra[5], int x, int y, int n) {
    for(int k = 1; k < n; k++) {
        y++;

        if(y > 9 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;

}
int matriz_cima(char matriz[8][10], char palavra[5], int x, int y, int n) {
    for(int k = 1; k < n; k++) {
        x--;

        if(x < 0 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;

}
int matriz_baixo(char matriz[8][10], char palavra[5], int x, int y, int n) {
    for(int k = 1; k < n; k++) {
        x++;

        if(x > 7 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;

}



int diagonal_esquerda_cima(char matriz[8][10], char palavra[5], int x, int y, int n) {
    
    x -= 1;
    y -= 1;
    int k = 1;
    
    while( x >= 0 && y >= 0 && matriz[x][y] == palavra[k] && palavra[k] != '\0') {   
        x -= 1;
        y -= 1;
        k++;
        if(k == n) {
        return 1;
        }
    }
    return 0;
}

int diagonal_direita_cima(char matriz[8][10], char palavra[5], int x, int y, int n) {
    
    for(int k = 1; k < n; k++) {
        x--;
        y++;

        if(x < 0 || y >= 10 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;
}

int diagonal_esquerda_baixo(char matriz[8][10], char palavra[5], int x, int y, int n) {
    
    x += 1;
    y -= 1;
    int k = 1;
    
    while( x < 8 && y >= 0 && matriz[x][y] == palavra[k]) {   
        x += 1;
        y -= 1;
        k++;
        if(k == n) {
        return 1;
        }
    }
    return 0;
}

int diagonal_direita_baixo(char matriz[8][10], char palavra[5], int x, int y, int n) {
    
    for(int k = 1; k < n; k++) {
        x++;
        y++;

        if(x > 7 || y > 9 || matriz[x][y] != palavra[k]) {
        return 0;
        }
    }
    return 1;
}


// A Burrice leva ao aprendizado.
// Função abaixo não está sendo utilizada, mas bom ter criada.
int busca_direcao(char matriz[8][10], char palavra[5], int x, int y, int n, int dx, int dy) {
    /*for (int k = 1; k < n; k++) {      
        x += dx;                       
        y += dy;                       

        if (x < 0 || x > 7 || y < 0 || y > 9 || matriz[x][y] != palavra[k]) {
            return 0;                 
        }
    }
    return 1;*/                      
}
