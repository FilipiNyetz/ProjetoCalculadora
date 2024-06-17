#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calculadora.c"

//int main() {
//
//    char posFixa[] = "3 4 + 5 *";
//    
//    // Convertendo para a forma infixa
//
//    char *inFixa = getFormaInFixa(posFixa);
//    
//    printf("Funcao Infixa: %s\n", inFixa);
//    
//    // Calculando o valor da expressão
//
//    float valor = getValor(posFixa);
//    
//    printf("Valor: %.2lf\n", valor);
//    
//    return 0;
//}

int main() {
    // Testando a função getFormaInFixa com diferentes expressões posfixas
    char posFixa1[] = "3 4 + 5 *";
    char posFixa2[] = "7 2 * 4 +";
    char posFixa3[] = "8 5 2 4 + * +";
    char posFixa4[] = "6 2 / 3 + 4 *";
    char posFixa5[] = "9 5 2 8 * 4 + * +";
    char posFixa6[] = "2 3 + log 5 /";
    char posFixa7[] = "10 log 3 ^ 2 +";
    char posFixa8[] = "45 60 + 30 cos *";
    char posFixa9[] = "0.5 45 sen 2 ^ +";

    printf("Expressao posfixa: %s\n", posFixa1);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa1));

    printf("Expressao posfixa: %s\n", posFixa2);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa2));

    printf("Expressao posfixa: %s\n", posFixa3);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa3));

    printf("Expressao posfixa: %s\n", posFixa4);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa4));

    printf("Expressao posfixa: %s\n", posFixa5);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa5));

    printf("Expressao posfixa: %s\n", posFixa6);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa6));

    printf("Expressao posfixa: %s\n", posFixa7);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa7));

    printf("Expressao posfixa: %s\n", posFixa8);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa8));

    printf("Expressao posfixa: %s\n", posFixa9);
    printf("Expressao infixa: %s\n\n", getFormaInFixa(posFixa9));

    return 0;
}



