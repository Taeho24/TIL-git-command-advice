// Requirement 3
/* Requirement 2 에서 생성한 자식 프로세스가 종료하기를 기다리도록 waitpid() 함수를 사용해 작성하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;

    pid_t pid = fork();

    if (pid < 0) {
        // fork 실패
        perror("fork 실패");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스: who 명령 실행
        printf("[자식] who 명령 실행 중\n");

        execl("/usr/bin/who", "who", (char *)NULL);

        // execl 실패 시 아래 코드가 실행됨
        perror("execl 실패");
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 자식 종료 기다림
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid 실패");
            exit(EXIT_FAILURE);
        }

        // 자식의 종료 상태 확인
        if (WIFEXITED(status)) {
            printf("[부모] 자식이 종료됨, 반환값: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[부모] 자식이 시그널에 의해 종료됨, 시그널 번호: %d\n", WTERMSIG(status));
        } else {
            printf("[부모] 자식이 정상 종료하지 않았습니다.\n");
        }
    }

    return 0;
}
