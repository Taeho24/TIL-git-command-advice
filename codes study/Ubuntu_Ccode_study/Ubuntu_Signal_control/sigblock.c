// Requirement 2
/* 반복문과 인터벌타임을 사용해 1초 간격으로 "Hanbit Books"를 출력하는 프로그램을 작성하시오.
작성된 프로그램이 `Ctrl + C`로 종료되지 않도록 sigprocmask()함수를 이용해 블로킹하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

void print_message(int signo) {
    if (signo == SIGALRM) {
        printf("Hanbit Books\n");
    }
}

int main() {
    sigset_t block_mask;
    struct itimerval timer;
    struct sigaction sa;

    // SIGINT를 포함하는 시그널 집합 생성
    if (sigemptyset(&block_mask) == -1) {
        perror("sigemptyset 실패");
        exit(EXIT_FAILURE);
    }

    if (sigaddset(&block_mask, SIGINT) == -1) {
        perror("sigaddset 실패");
        exit(EXIT_FAILURE);
    }

    // SIGINT 시그널 블로킹
    if (sigprocmask(SIG_BLOCK, &block_mask, NULL) == -1) {
        perror("sigprocmask 실패");
        exit(EXIT_FAILURE);
    }

    printf("SIGINT(Ctrl+C)를 블로킹합니다. 프로그램을 강제 종료하려면 kill 명령을 사용하세요.\n");

    // 무한 루프: 1초 간격으로 메시지 출력
    /* while (1) {
        printf("Hanbit Books\n");
        sleep(1);
    } */
    
    // 인터벌타임 이용
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = print_message;

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // 무한 대기
    while (1) {
        pause(); // 시그널 발생 시까지 대기
    }
    return 0;
}
