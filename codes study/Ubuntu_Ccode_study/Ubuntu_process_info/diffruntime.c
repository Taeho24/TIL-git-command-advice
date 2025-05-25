// Requirement 2
/* 반복문을 사용해 저수준 파일 입출력 함수인 open()과 close()를 반복적으로 100000번 실행하는 프로그램을 작성하고, 사용자 모드 실행 시간과 시스템 모드 실행 시간을 출력해 비교하시오. */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>

#define NUM_ITERATIONS 100000
#define FILENAME "tempfile.txt"

int main() {
    struct tms start_tms = {0}, end_tms = {0};  // tms 구조체 초기화
    clock_t ct = 0;  // 시스템 클럭 주기 초기화
    double user_time = 0.0, system_time = 0.0;  // 사용자 및 시스템 모드 시간 초기화

    // 시스템 클럭 주기 확인
    ct = sysconf(_SC_CLK_TCK);  // 1초에 해당하는 시스템 클럭 주기
    if (ct == -1) {
        perror("sysconf(_SC_CLK_TCK) 실패");
        exit(EXIT_FAILURE);
    }
    printf("Clock tick : %ld\n", ct);

    // 시작 시간 기록
    if (times(&start_tms) == -1) {
        perror("start_tms 실패");
        exit(EXIT_FAILURE);
    }

    // 파일 열기 및 닫기를 100,000번 반복
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int fd = open(FILENAME, O_RDWR | O_CREAT, 0664);  // 파일 열기
        if (fd == -1) {
            perror("파일 열기 실패");
            exit(EXIT_FAILURE);  // 파일 열기 실패 시 종료
        }
        
        if (close(fd) == -1) {
            perror("파일 닫기 실패");
            exit(EXIT_FAILURE);  // 파일 닫기 실패 시 종료
        }
    }

    // 종료 시간 기록
    if (times(&end_tms) == -1) {
        perror("end_tms 실패");
        exit(EXIT_FAILURE);
    }

    // 사용자 모드 시간과 시스템 모드 시간 계산
    user_time = (double)(end_tms.tms_utime - start_tms.tms_utime) / ct;
    system_time = (double)(end_tms.tms_stime - start_tms.tms_stime) / ct;

    // 실행 시간 출력
    printf("사용자 모드 실행 시간: %f 초\n", user_time);
    printf("시스템 모드 실행 시간: %f 초\n", system_time);

    return 0;
}
