#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

void caesar_cipher(char *str, const char *substitution) {
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        // 영어 대소문자 처리
        if (ch >= 'A' && ch <= 'Z') {
            str[i] = substitution[ch - 'A'];  // 대문자에 대해 치환
        } else if (ch >= 'a' && ch <= 'z') {
            str[i] = substitution[ch - 'a' + 26];  // 소문자에 대해 치환
        }
    }
}

int main() {
    char substitution[52];
    char input_string[MAX_LEN];

    // 치환 문자 입력 받기
    printf("치환 문자 (대소문자 구분하여 26자씩 입력):\n");
    printf("대문자에 대한 치환 문자 (26자): ");
    fgets(substitution, 27, stdin);
    substitution[26] = '\0';  // 대문자 치환 끝

    printf("소문자에 대한 치환 문자 (26자): ");
    fgets(substitution + 26, 27, stdin);
    substitution[52] = '\0';  // 소문자 치환 끝

    // 입력 문자열 받기
    printf("입력 문자열: ");
    fgets(input_string, MAX_LEN, stdin);
    input_string[strcspn(input_string, "\n")] = '\0';  // 문자열의 개행 문자 제거

    // 암호화 수행
    caesar_cipher(input_string, substitution);

    // 결과 출력
    printf("치환된 문자열: %s\n", input_string);

    return 0;
}

/*치환 문자 (대소문자 구분하여 26자씩 입력):
대문자에 대한 치환 문자 (26자): QWERTYUIOPASDFGHJKLZXCVBNM
소문자에 대한 치환 문자 (26자): qwertyuiopasdfghjklzxcvbnm
입력 문자열: Hello, World!
치환된 문자열: Itssg, Vgksr!*/
