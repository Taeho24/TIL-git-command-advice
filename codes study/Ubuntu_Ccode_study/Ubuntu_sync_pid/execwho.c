// Requirement 2
/* fork() 함수로 생성한 자식 프로세스에서 execl()함수를 사용해 who 명령을 실행하도록 프로그램을 작성하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status = 0;

    pid_t  pid = fork();

    if (pid < 0) {
        perror("fork 실패");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스: execl을 사용해 who 명령 실행
        printf("[자식] who 명령 실행\n");

        execl("/usr/bin/who", "who", (char *)NULL);

        // execl이 실패하면 아래 코드 실행
        perror("execl 실패");
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 자식이 종료될 때까지 대기
        if (wait(&status) == -1) {
            perror("wait 실패");
            exit(EXIT_FAILURE);
        }

        printf("[부모] 자식 프로세스 종료\n");
    }

    return 0;
}
