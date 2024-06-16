#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "calculadora.c"

int main() {

    char posFixa[] = "7 2 * 4 +";
    
    // Convertendo para a forma infixa

    char *inFixa = getFormaInFixa(posFixa);
    
    printf("Funcao Infixa: %s\n", inFixa);
    
    // Calculando o valor da expressão

    float valor = getValor(posFixa);
    
    printf("Valor: %f\n", valor);
    
    return 0;
}



