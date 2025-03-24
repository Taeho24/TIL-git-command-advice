// div.c
#include "func.h"
#include <stdio.h>
int div(int a, int b){
    // ZeroDivisionError: division by zero
    if (b == 0){
        printf("Error: Division by Zero!\n");
        return 0;
    }
    return a / b;
}