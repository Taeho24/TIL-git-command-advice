// Requirement 1
/* sigaction()함수를 이용해 SIQINT 시그널을 붙잡고 이를 처리하는 시그널 핸들러를 작성하시오.
sa_flags에 SA_SIGINFO를 설정하고 sa_sigaction을 사용하며 시그널 핸들러 함수에서 si_code 값을 출력해 시그널이 발생한 원인을 확인하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// SIGINT 시그널 핸들러
void sigint_handler(int signo, siginfo_t *info, void *context) {
    if (info == NULL) {
        fprintf(stderr, "siginfo_t 포인터가 NULL입니다.\n");
        exit(EXIT_FAILURE);
    }

    printf("\n[SIGINT 핸들러 작동]\n");
    psiginfo(info, "시그널 정보:");
    printf("시그널 번호: %d\n", signo);
    printf("si_code: %d\n", info->si_code);
    printf("프로그램을 종료합니다.\n");

    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction sa;

    // SIGINT 핸들러 설정
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = sigint_handler;
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction(SIGINT)");
        exit(EXIT_FAILURE);
    }

    // SIGINT를 제외한 모든 시그널 무시
    for (int i = 1; i < NSIG; ++i) {
        if (i == SIGKILL || i == SIGSTOP || i == SIGINT)
            continue;

        // 무시할 수 없는 시그널에 대한 오류 방지
        struct sigaction ignore_sa;
        memset(&ignore_sa, 0, sizeof(ignore_sa));
        ignore_sa.sa_handler = SIG_IGN;
        sigaction(i, &ignore_sa, NULL);
    }

    printf("SIGINT (Ctrl+C)를 기다리는 중입니다. 다른 시그널은 무시됩니다.\n");

    while (1) {
        pause();
    }

    printf("시그널 실패!\n");
    
    return EXIT_SUCCESS;
}
