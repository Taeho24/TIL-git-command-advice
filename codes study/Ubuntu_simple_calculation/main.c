// main.c
#include <stdio.h>
#include <string.h>
#include "func.h"

int main() {
    int first_num = 0, second_num = 0;
    int result = 0;
    char op = '\0';
    char input[100] = {0}; // 입력받은 input
    char cleaned_input[100] = {0}; // 공백을 제거한 input

    printf("수식을 입력하세요!! ");

    // scanf("%d %c %d", &first_num, &op, &second_num);
    if (fgets(input, sizeof(input), stdin) == NULL) {  // 입력 오류 처리
        printf("입력 오류가 발생했습니다.\n");
        return 1;
    }

    // 띄어쓰기를 모두 제거하는 코드
    int j = 0;
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ') {
            cleaned_input[j++] = input[i];
        }
    }
    cleaned_input[j] = '\0';  // 문자열 끝에 null 추가

     // 수식 파싱 (정수와 연산자만 추출)
     if (sscanf(cleaned_input, "%d%c%d", &first_num, &op, &second_num) != 3) {
        printf("잘못된 입력입니다. 수식 형식을 확인하세요.\n");
        return 1;
     }

     // 연산자 예외 처리 // '+', '-', '*', '/' 
     // 곱하기의 다른 연산자(ex. x, X,..)는 제외
     // 나누기 Division by Zero 처리는 div.c에서 예외처리
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        printf("잘못된 연산자입니다. +, -, *, /만 가능합니다.\n");
        return 1;
    }

    // 계산 결과
    switch (op) {
        case '+':
            result = add(first_num, second_num);
            break;
        case '-':
            result = sub(first_num, second_num);
            break;
        case '*':
            result = mul(first_num, second_num);
            break;
        case '/':
            result = div(first_num, second_num);
            break;
        default:
            printf("Error: Unsupported operator\n");
            return 1;
    }
    printf("계산결과는 %d입니다.\n", result);
    return 0;
}
