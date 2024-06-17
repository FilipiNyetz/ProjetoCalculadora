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
                operando1 = pilha[topo--] * 0.01744;
                valor = sin(operando1);
                pilha[++topo] = valor;
                i += 2; // Pula sobre 'sen'
            } else if (strncmp(&Str[i], "cos", 3) == 0) {
                operando1 = pilha[topo--] * 0.01744;
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

            // Desempilha os operandos
            strcpy(operando2, pilha[topo--]);
            strcpy(operando1, pilha[topo--]);

            // Verifica a precedência e necessidade de parênteses
            int prec_op = precedencia(Str[i]);
            int prec_topo = precedencia(pilha[topo][0]);
            int precisa_parenteses = (prec_op > prec_topo) || (prec_op == prec_topo && (Str[i] == '*' || Str[i] == '/'));

            // Constrói a expressão infixa
            resultado[0] = '\0';
            if (precisa_parenteses) {
                strcat(resultado, "(");
                strcat(resultado, operando1);
                strcat(resultado, " ");
                strncat(resultado, &Str[i], 1);
                strcat(resultado, " ");
                strcat(resultado, operando2);
                strcat(resultado, ")");
            } else {
                strcat(resultado, operando1);
                strcat(resultado, " ");
                strncat(resultado, &Str[i], 1);
                strcat(resultado, " ");
                strcat(resultado, operando2);
            }

            // Empilha o resultado, exceto se for a última operação matemática
            if (Str[i + 1] != '\0' && Str[i + 1] != ' ') {
                strcpy(pilha[++topo], resultado);
            } else {
                strcpy(pilha[++topo], operando1);
                strcat(pilha[topo], " ");
                strncat(pilha[topo], &Str[i], 1);
                strcat(pilha[topo], " ");
                strcat(pilha[topo], operando2);
            }

            // Pula para o próximo operador ou número
            while (Str[i + 1] == ' ')
                i++;
        } else if (ehFuncaoMatematica(&Str[i])) {
            // Funções como log, sen, cos
            char operando1[MAX], resultado[MAX];

            // Desempilha o operando
            strcpy(operando1, pilha[topo--]);

            // Constrói a expressão infixa
            if (Str[i] == 'l') {
                // Se for log, adiciona parênteses apenas se necessário
                int precisa_parenteses = (precedencia('l') > precedencia(pilha[topo][0]));

                resultado[0] = 'l';
                resultado[1] = 'o';
                resultado[2] = 'g';
                resultado[3] = '(';
                resultado[4] = '\0';
                if (precisa_parenteses) {
                    strcat(resultado, "(");
                    strcat(resultado, operando1);
                    strcat(resultado, "))");
                } else {
                    strcat(resultado, operando1);
                    strcat(resultado, ")");
                }
            } else if (Str[i] == 's') {
                // Seno
                resultado[0] = 's';
                resultado[1] = 'i';
                resultado[2] = 'n';
                resultado[3] = '(';
                resultado[4] = '\0';
                strcat(resultado, operando1);
                strcat(resultado, ")");
            } else if (Str[i] == 'c') {
                // Cosseno
                resultado[0] = 'c';
                resultado[1] = 'o';
                resultado[2] = 's';
                resultado[3] = '(';
                resultado[4] = '\0';
                strcat(resultado, operando1);
                strcat(resultado, ")");
            }

            // Empilha o resultado
            strcpy(pilha[++topo], resultado);

            // Pula para o próximo operador ou número
            while (Str[i + 1] == ' ')
                i++;
        }
    }

    // A expressão infixa final estará no topo da pilha
    strcpy(resposta, pilha[topo]);
    return resposta;
}
