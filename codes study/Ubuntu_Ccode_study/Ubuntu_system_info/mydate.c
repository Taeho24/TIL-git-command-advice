// Requirement 2
/* 날짜와 시간을 출력하는 명령 mydate를 작성하시오. 이때 mydate의 옵션은 다음과 같다.
ex.
$ mydate
[option]
-a : 연, 월, 일, 요일, 시, 분, 초 출력 
-y : 연도만 출력
-m : 월만 출력
-d : 일만 출력
-w : 요일만 출력
-h : 시, 분, 초 출력*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

// 사용법 출력 함수
void print_usage() {
    printf("사용법: mydate [옵션들]\n");
    printf("[option]\n");
    printf("  -a, --all         : 연, 월, 일, 요일, 시, 분, 초 출력 (단독으로 사용)\n");
    printf("  -y, --year        : 연도만 출력\n");
    printf("  -m, --month       : 월만 출력\n");
    printf("  -d, --day         : 일만 출력\n");
    printf("  -w, --weekday     : 요일만 출력\n");
    printf("  -h, --hour        : 시, 분, 초 출력\n");
    printf("  -f, --format \"FMT\": 포맷 문자열에 따라 출력 (strftime 형식)\n");
    printf("      --help        : 도움말 출력\n\n");

    printf("예시 FMT(strftime): \"%%Y-%%m-%%d %%H:%%M:%%S\"\n");
    printf("  %%Y : 연도 (예: 2025)\n");
    printf("  %%y : 연도 (끝 2자리, 예: 25)\n");
    printf("  %%m : 월 (01~12)\n");
    printf("  %%d : 일 (01~31)\n");
    printf("  %%H : 시 (00~23)\n");
    printf("  %%M : 분 (00~59)\n");
    printf("  %%S : 초 (00~60)\n");
    printf("  %%A : 요일 전체 (예: Sunday)\n");
    printf("  %%a : 요일 축약 (예: Sun)\n");
    printf("  %%p : AM/PM\n");
}

// 조건에 맞는 경우 사용법을 출력하고 종료하는 함수
int check_no_option(int argc, int show_all, int total_flags, int use_format) {
    // 옵션이 없을 때
    if (argc == 1) {
        show_all = 1; // 기본적으로 -a(모든 항목) 옵션 적용
        // print_usage();
        return 0;
    }
    // 유효한 옵션이 없을 때 처리
    if (!show_all && !total_flags && !use_format) {
        print_usage();
        return 1;  
    }

    return 0;  // 정상적으로 진행
}

// 결과 출력 함수
void print_selected(struct tm *t, char **weekdays, int y, int m, int d, int w, int h) {
    if (y) printf("연도: %04d\n", t->tm_year + 1900);
    if (m) printf("월: %02d\n", t->tm_mon + 1);
    if (d) printf("일: %02d\n", t->tm_mday);
    if (w) printf("요일: %s\n", weekdays[t->tm_wday]);
    if (h) printf("시간: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);
}

int main(int argc, char *argv[]) {
    int opt, long_index;
    int show_all = 0, show_year = 0, show_month = 0, show_day = 0;
    int show_weekday = 0, show_hour = 0;
    int use_format = 0;
    char format_buf[128] = "";  // 사용자 지정 포맷

    time_t now = time(NULL);
    if (now == ((time_t)-1)) {
        perror("time");
        return 1;
    }
    struct tm *t = localtime(&now);
    if (t == NULL) {
        perror("localtime");
        return 1;
    }

    char *weekdays[] = {"일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"};

    const struct option long_options[] = {
        {"all",     no_argument,       0, 'a'},
        {"year",    no_argument,       0, 'y'},
        {"month",   no_argument,       0, 'm'},
        {"day",     no_argument,       0, 'd'},
        {"weekday", no_argument,       0, 'w'},
        {"hour",    no_argument,       0, 'h'},
        {"format",  required_argument, 0, 'f'},
        {"help",    no_argument,       0,  0 },
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "aymdwhf:", long_options, &long_index)) != -1) {
        // short option 없음: --help
        if (opt == 0 && strcmp(long_options[long_index].name, "help") == 0) {
        print_usage();
        return 0;
        }
        switch (opt) {
            case 'a': show_all = 1; break;
            case 'y': show_year = 1; break;
            case 'm': show_month = 1; break;
            case 'd': show_day = 1; break;
            case 'w': show_weekday = 1; break;
            case 'h': show_hour = 1; break;
            case 'f':
                strncpy(format_buf, optarg, sizeof(format_buf) - 1);
                format_buf[sizeof(format_buf) - 1] = '\0';  // 안전 종료
                use_format = 1;
                break;
            case '?':
                fprintf(stderr, "잘못된 옵션이 포함되어 있습니다: -%c\n", optopt);
                print_usage();
                return 1;
            default:    // 혹시 모를 예외처리
                print_usage();
                return 1;
        }
    }
    
    int total_flags = show_year + show_month + show_day + show_weekday + show_hour;

    // 옵션 유효성 체크
    if (check_no_option(argc, show_all, total_flags, use_format)) {
        return 0;  
    }

    // -a 또는 --all 단독 사용만 허용
    if (show_all && (total_flags > 0 || use_format)) {
        fprintf(stderr, "오류: -a/--all 옵션은 다른 옵션과 함께 사용할 수 없습니다.\n");
        print_usage();
        return 1;
    }

    // -f 또는 --format
    if (use_format) {
        char output[128];
        if (strftime(output, sizeof(output), format_buf, t)) {
            printf("%s\n", output);
        } else {
            fprintf(stderr, "포맷 오류 또는 출력 버퍼 초과\n");
            return 1;
        }
        return 0;
    }

    // 출력
    if (show_all) {
        printf("현재 시간: %04d년 %02d월 %02d일 %s %02d시 %02d분 %02d초\n",
               t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
               weekdays[t->tm_wday], t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        print_selected(t, weekdays, show_year, show_month, show_day, show_weekday, show_hour);
    }

    return 0;
}
