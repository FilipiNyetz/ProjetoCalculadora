#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calculadora.c"

int main() {

    char posFixa[] = "0.5 45 sen 2 ^ +";
    
    // Convertendo para a forma infixa

    char *inFixa = getFormaInFixa(posFixa);
    
    printf("Funcao Infixa: %s\n", inFixa);
    
    // Calculando o valor da expressão

    float valor = getValor(posFixa);
    
    printf("Valor: %f\n", valor);
    
    return 0;
}
