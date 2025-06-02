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

    psiginfo(info, "Received Signal:");
    printf("시그널 번호: %d\n", signo);
    printf("si_code: %d\n", info->si_code);

    printf("프로그램을 종료합니다.\n");
    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction sa;
    sigset_t st_mask;

    act.sa_sigaction = sigint_handler;
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction(SIGINT)");
        exit(EXIT_FAILURE);
    }

    // 모든 시그널 무시 (SIGINT 제외)
    for (int i = 1; i < NSIG; ++i) {
        if (i != SIGINT) {
            signal(i, SIG_IGN);
        }
    }

    // SIGINT만 허용하는 마스크 생성
    sigemptyset(&st_mask);
    sigaddset(&st_mask, SIGINT);

    // sigaction으로 SIGINT 처리 함수 등록
    if (sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0>) {
        perror("sigaction 실패");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT(Ctrl+C)를 기다리는 중입니다. 종료하려면 Ctrl+C를 누르세요.\n");

    sigfillset(&st_mask);           // 모든 시그널을 차단
    sigdelset(&st_mask, SIGINT);    // SIGINT만 허용
    
    if (sigprocmask(SIG_SETMASK, &st_mask, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    sigsuspend(&st_mask);

    printf("시그널 실패!\n");

    return EXIT_SUCCESS;
}
