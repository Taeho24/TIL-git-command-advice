// Requirement 3
/* 명령행 인자로 환경 변수명과 변숫값을 입력받아 환경 변수를 설정하는 프로그램을 작성하시오. 
프로세스 종료 후 출력 가능하게 전역적으로 설정, 자식에서 환경변수를 설정하는 형태로만 구현해서 `env | grep TERM` 같은 명령어 시 확인 가능하게 */

/*
> $ ./setenv_example TERM xterm
> $ source ./setenv_example TERM xterm  # 셸 내에서 실행
> $ env | grep TERM
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        if (argc == 2) {
            // 환경 변수명만 입력되었을 때 그 값을 출력 (search 목적)
            char *env_var_name = argv[1];
            char *value = getenv(env_var_name);
            if (value != NULL) {
                printf("%s = %s\n", env_var_name, value);
            } else {
                printf("환경 변수 %s는 설정되지 않았습니다.\n", env_var_name);
            }
        }
        fprintf(stderr, "Usage: %s <환경 변수명> <변수값>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *env_var_name = argv[1]; // 환경 변수명
    char *env_var_value = argv[2]; // 변숫값

    pid_t pid = fork();  // 자식 프로세스 생성

    if (pid < 0) {
        perror("fork 실패");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // 자식 프로세스
        // 환경 변수 설정
        if (setenv(env_var_name, env_var_value, 0) == -1) {
            perror("환경 변수 설정 실패");
            exit(EXIT_FAILURE);
        }

        // 환경 변수 설정 후, sleep으로 잠시 대기 (부모가 먼저 종료되지 않도록)
        sleep(2);

        // env 명령어 실행하여 환경 변수 출력
        execlp("env", "env", NULL);
        perror("exec 실패");  // exec 실패 시
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {  // 부모 프로세스
        // 자식 프로세스가 종료될 때까지 기다림
        wait(NULL);
        printf("자식 프로세스가 실행 완료되어 환경 변수의 변경을을 확인할 수 없습니다.\n");
    }

    return 0;
}
