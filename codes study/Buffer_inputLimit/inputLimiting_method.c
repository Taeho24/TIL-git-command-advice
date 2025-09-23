// 닉네임 설정 등에 활용되는 글자 제한

/*
 char name[6];
    name[5] = '\0';
*/
#include <stdio.h>

// 1. 5글자만 입력 & 출력
int main() {
    char name[6];  // 크기 6 (최대 5글자 + 널 문자)
    
    printf("Enter your name (max 5 characters): ");
    scanf("%5s", name);  // 최대 5글자까지 입력받기

    printf("You entered: %s\n", name);  // 입력한 이름 출력
    
    return 0;
}

// 2. NULL문자를 포함하는 5글자 입력 & 출력 + '\n'가 입력될때의 처리
/*
int main() {
    char name[6];  // 크기 6 (최대 5글자 + 널 문자)
    
    printf("Enter your name (max 5 characters): ");
    fgets(name, sizeof(name), stdin);  // 최대 5글자까지 입력받기

    // 입력 후 '\n' 제거 (fgets는 줄바꿈 문자를 포함할 수 있으므로)
    if (name[strlen(name) - 1] == '\n') {
        name[strlen(name) - 1] = '\0';  // '\n'을 제거하고 널 문자로 대체
    }

    printf("You entered: %s\n", name);  // 입력한 이름 출력
    
    return 0;
}
*/

// 3. NULL문자를 포함하는 5글자 입력 & 출력 + '\n'가 입력될때의 처리 + 5글자가 넘었을때의 예외처리
/*
#include <string.h>

int main() {
    char name[6];  // 크기 6 (최대 5글자 + 널 문자)
    
    printf("Enter your name (max 5 characters): ");
    fgets(name, sizeof(name), stdin);  // 최대 5글자까지 입력받기

    // 입력된 이름의 길이를 확인
    if (strlen(name) > 5) {
        printf("Error: Name is too long! Please enter a name with at most 5 characters.\n");
    } else {
        // 줄 바꿈 문자 제거
        if (name[strlen(name) - 1] == '\n') {
            name[strlen(name) - 1] = '\0';
        }
        printf("You entered: %s\n", name);  // 입력한 이름 출력
    }

    return 0;
}
*/
