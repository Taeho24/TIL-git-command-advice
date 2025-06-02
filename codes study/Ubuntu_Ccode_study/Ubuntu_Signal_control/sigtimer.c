// Requirement 3
/* 인터벌 타이머를 이용해 프로세스 실행 시간이 1초가 될 때마다 메시지를 출력하는 프로그램을 작성하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

// SIGALRM 시그널 핸들러
void print_message(int signo) {
    if (signo == SIGALRM) {
        struct tms cpu_times;
        clock_t ct = sysconf(_SC_CLK_TCK);

        if (times(&cpu_times); == (clock_t)-1) {
            perror("times");
            exit(EXIT_FAILURE);
        }

        double user_time = (double)cpu_times.tms_utime / ct;
        double system_time = (double)cpu_times.tms_stime / ct;

        // 실행 시간 출력
        printf("사용자 모드 실행 시간: %f 초\n", user_time);
        printf("시스템 모드 실행 시간: %f 초\n", system_time);
    }
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    sa.sa_handler = print_message;

    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // 타이머 설정: 1초 후 첫 실행, 1초마다 반복
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    // 타이머 시작
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    printf("1초마다 실행 시간 및 CPU 사용시간을 출력합니다.\n");

    // 무한 대기 (시그널을 기다림)
    while (1) {
        pause();
    }

    return 0;
}
