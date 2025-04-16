// Requirement 1
/* 명령행 인자로 받은 파일의 정보를 추출해 다음 예와 같이 출력하는 프로그램을 작성하시오.
ex.
파일명: a.c
inode 번호: 1020400
파일종류: 일반파일
접근권한: 100644
UID: 1000 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void print_file_info(const char *filename) {
    struct stat file_stat;

    // stat 시스템 호출을 통해 파일의 정보를 얻는다.
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    }

    // 파일명 출력
    printf("파일명: %s\n", filename);

    // inode 번호 출력
    printf("inode 번호: %ld\n", (int)file_stat.st_ino);

    // 파일 종류 출력
    if (S_ISREG(file_stat.st_mode)) {
        printf("파일종류: 일반파일\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("파일종류: 디렉토리\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("파일종류: 심볼릭 링크 파일\n");
    } else if (S_ISCHR(file_stat.st_mode)) {
        printf("파일종류: 문자장치 특수파일\n");
    } else if (S_ISBLK(file_stat.st_mode)) {
        printf("파일종류: 블록장치 특수파일\n");
    } else if (S_ISFIFO(file_stat.st_mode)) {
        printf("파일종류: FIFO 파일\n");
    } else if (S_ISSOCK(file_stat.st_mode)) {
        printf("파일종류: 소켓파일\n");
    } else {
        printf("파일종류: 기타\n");
    }

    // 접근 권한 출력 (8진수 형식)
    printf("접근권한: %o\n", (unsigned int)file_stat.st_mode);

    // UID 출력
    printf("UID: %d\n", (int)file_stat.st_uid);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    const char *file_name = argv[1];

    // 파일 정보 출력
    print_file_info(file_name);

    return 0;
}
