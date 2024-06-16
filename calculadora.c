#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

#define MAX 512


float getValor(char *Str) {
    double pilha[MAX];
    int topo = -1;
    char buffer[100]; // Buffer para armazenar números temporariamente
    int j = 0; // Índice para o buffer

    for (int i = 0; Str[i] != '\0'; ++i) {
        if (isdigit(Str[i]) || Str[i] == '.') {
            // Se for um dígito ou ponto decimal, armazena no buffer
            buffer[j++] = Str[i];
        } else if (Str[i] == ' ' || Str[i] == '\t') {
            // Se for um espaço, converte o buffer para double e empilha
            if (j > 0) {
                buffer[j] = '\0'; // Termina a string
                pilha[++topo] = strtod(buffer, NULL);
                j = 0; // Reseta o índice do buffer
            }
        } else {
            // Se for um operador, reseta o buffer e empilha o número
            if (j > 0) {
                buffer[j] = '\0';
                pilha[++topo] = strtod(buffer, NULL);
                j = 0;
            }

            // Se for um operador, desempilha os operandos necessários e realiza a operação
            double operando1, operando2;
            double valor = 0;

            if (strncmp(&Str[i], "log", 3) == 0) {
                operando1 = pilha[topo--];
                valor = log10(operando1);
                pilha[++topo] = valor;
                i += 2; // Pula sobre 'log'
            } else if (strncmp(&Str[i], "sen", 3) == 0) {
                operando1 = pilha[topo--] * 0.0174444444444444;
                valor = sin(operando1);
                pilha[++topo] = valor;
                i += 2; // Pula sobre 'sen'
            } else if (strncmp(&Str[i], "cos", 3) == 0) {
                operando1 = pilha[topo--] * 0.0174444444444444;
                valor = cos(operando1);
                pilha[++topo] = valor;
                i += 2; // Pula sobre 'cos'
            } else {
                operando2 = pilha[topo--];
                operando1 = pilha[topo--];

                switch (Str[i]) {
                    case '+':
                        pilha[++topo] = operando1 + operando2;
                        break;
                    case '-':
                        pilha[++topo] = operando1 - operando2;
                        break;
                    case '*':
                        pilha[++topo] = operando1 * operando2;
                        break;
                    case '/':
                        if (operando2 != 0.0) {
                            pilha[++topo] = operando1 / operando2;
                        } else {
                            printf("Erro: Divisão por zero\n");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    case '^':
                        pilha[++topo] = pow(operando1, operando2);
                        break;
                    default:
                        printf("Erro: Operador inválido\n");
                        exit(EXIT_FAILURE);
                }
            }
        }
    }
    // O resultado final estará no topo da pilha
    return pilha[topo];
}

int ehOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Função para retornar a precedência de um operador
int precedencia(char operador) {
    if (operador == '^')
        return 3;
    else if (operador == '*' || operador == '/')
        return 2;
    else if (operador == '+' || operador == '-')
        return 1;
    else
        return 0; // Operador inválido
}


int ehFuncaoMatematica(char *str) {
    return (strncmp(str, "log", 3) == 0 || strncmp(str, "sen", 3) == 0 || strncmp(str, "cos", 3) == 0);
}


char *getFormaInFixa(char *Str) {
    static char resposta[MAX];
    char pilha[MAX][MAX];
    int topo = -1;
    char buffer[MAX]; // Buffer para armazenar temporariamente números ou operadores
    int j = 0; // Índice para o buffer

    for (int i = 0; Str[i] != '\0'; ++i) {
        if (isdigit(Str[i]) || Str[i] == '.') {
            // Se for um dígito ou ponto decimal, armazena no buffer
            buffer[j++] = Str[i];
        } else if (Str[i] == ' ' || Str[i] == '\t') {
            // Se for um espaço, converte o buffer para string e empilha
            if (j > 0) {
                buffer[j] = '\0'; // Termina a string
                strcpy(pilha[++topo], buffer);
                j = 0; // Reseta o índice do buffer
            }
        } else if (ehOperador(Str[i])) {
            // Se for um operador, desempilha os operandos necessários e realiza a operação
            char operando2[MAX], operando1[MAX], resultado[MAX];
            char abertura = '\0', fechamento = '\0'; // Variáveis para armazenar os parênteses

            // Desempilha os operandos
            strcpy(operando2, pilha[topo--]);
            strcpy(operando1, pilha[topo--]);

            // Verifica a precedência e necessidade de parênteses
            if (precedencia(Str[i]) > precedencia(pilha[topo][0])) {
                abertura = '(';
                fechamento = ')';
            }

            // Constrói a expressão infixa
            sprintf(resultado, "%c%s %c %s%c", abertura, operando1, Str[i], operando2, fechamento);

            // Empilha o resultado
            strcpy(pilha[++topo], resultado);

            // Pula para o próximo operador ou número
            while (Str[i + 1] == ' ')
                i++;
        } else {
            // Funções como log, sen, cos
            char operando1[MAX], resultado[MAX];

            // Desempilha o operando
            strcpy(operando1, pilha[topo--]);

            // Constrói a expressão infixa
            if (ehFuncaoMatematica(&Str[i])) {
                if (strncmp(&Str[i], "log", 3) == 0) {
                    sprintf(resultado, "log(%s)", operando1);
                    strcpy(pilha[++topo], resultado);
                    i += 2; // Pula sobre 'log'
                } else if (strncmp(&Str[i], "sen", 3) == 0) {
                    sprintf(resultado, "sen(%s)", operando1);
                    strcpy(pilha[++topo], resultado);
                    i += 2; // Pula sobre 'sen'
                } else if (strncmp(&Str[i], "cos", 3) == 0) {
                    sprintf(resultado, "cos(%s)", operando1);
                    strcpy(pilha[++topo], resultado);
                    i += 2; // Pula sobre 'cos'
                }
            }
        }
    }

    // A expressão infixa final estará no topo da pilha
    strcpy(resposta, pilha[topo]);
    return resposta;
}
