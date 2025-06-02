// Requirement 3
/* 인터벌 타이머를 이용해 프로세스 실행 시간이 1초가 될 때마다 메시지를 출력하는 프로그램을 작성하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/times.h>

// SIGALRM 시그널 핸들러
void print_message(int signo) {
    if (signo == SIGALRM) {
        time_t now = time(NULL);
        if (now == ((time_t)-1)) {
            perror("time");
            return 1;
        }
        struct tm *time_info = localtime(&now);
        if (time_info == NULL) {
            perror("localtime");
            return 1;
        }

        printf("현재 시각: %04d-%02d-%02d %02d:%02d:%02d\n",
            time_info->tm_year + 1900,
            time_info->tm_mon + 1,
            time_info->tm_mday,
            time_info->tm_hour,
            time_info->tm_min,
            time_info->tm_sec);
    }
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    memset(&sa, 0, sizeof(sa));
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

    printf("1초마다 현재시간을 출력합니다.\n");

    // 무한 대기 (시그널을 기다림)
    while (1) {
        pause();
    }

    return 0;
}
