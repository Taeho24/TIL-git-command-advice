// Requirement 1
// 사용자ID를 입력받아 홈 디렉터리와 로그인 셸을 출력하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int is_number(const char *str) {
    if (*str == '\0') return 0;  // 빈 문자열일 때
    while (*str) {
        if (!isdigit((unsigned char)*str)) return 0;  // 숫자가 아니면 0 반환
        str++;
    }
    return 1; 
}

int main() {
    struct passwd *pw = NULL;
    char *input_ID = NULL;
    size_t buf_size = 0;
    ssize_t line_len;
    uid_t uid = 0;

    printf("사용자 ID(uid)를 입력하세요: ");

    line_len = getline(&input_ID, &buf_size, stdin);
    if (line_len == -1) {
        perror("입력 오류");
        free(input_ID);
        return 1;
    }

    // 개행 문자 제거
    input_ID[strcspn(input_ID, "\n")] = '\0';

    // 숫자인지 확인
    if (!is_number(input_ID)) {
        fprintf(stderr, "오류: 정수가 아닌 값이 입력되었습니다.\n");
        free(input_ID);
        return 1;
    }

    // 문자열을 정수로 변환
    uid = (uid_t)strtoul(input_ID, NULL, 10);

    pw = getpwuid(uid);
    if (pw == NULL) {
        fprintf(stderr, "해당 UID에 대한 사용자 정보를 찾을 수 없습니다.\n");
        free(input_ID);
        return 1;
    }

    printf("사용자 이름: %s\n", pw->pw_name);
    printf("홈 디렉터리: %s\n", pw->pw_dir);
    printf("로그인 셸: %s\n", pw->pw_shell);

    free(input_ID);
    return 0;
}
