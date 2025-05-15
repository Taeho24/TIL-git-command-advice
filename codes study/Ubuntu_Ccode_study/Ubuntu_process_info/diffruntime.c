// Requirement 2
/* 반복문을 사용해 저수준 파일 입출력 함수인 open()과 close()를 반복적으로 100000번 실행하는 프로그램을 작성하고, 사용자 모드 실행 시간과 시스템 모드 실행 시간을 출력해 비교하시오. */


// #include <sys/types.h>
// #include <sys/times.h>
// #include <time.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>

// int main() {
//     int i;
//     time_t t;
//     struct tms buf;
//     clock_t ct, t1, t2;

//     ct = sysconf(_SC_CLK_TCK);
//     printf("Clock tick : %ld\n", ct);

//     if ((t1 = times(&buf)) == -1) {
//         perror("times 1");
//         exit(1);
//     }

//     for (i = 0; i < 99999999; i++)
//         time(&t);
//         sleep(1);

//     if ((t2 = times(&buf)) == -1) {
//         perror("times 2");
//         exit(1);
//     }

//     printf("t1: %ld\n", t1);
//     printf("t2: %ld\n", t2);
//     printf("utime : %ld\n", buf.tms_utime);
//     printf("stime : %ld\n", buf.tms_stime);
//     printf("Real time : %.1f sec\n", (double)(t2 - t1) / ct);
//     printf("User time : %.1f sec\n", (double)buf.tms_utime / ct);
//     printf("System time : %.1f sec\n", (double)buf.tms_stime / ct);
// }
