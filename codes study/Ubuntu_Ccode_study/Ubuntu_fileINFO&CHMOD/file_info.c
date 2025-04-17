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
#include <limits.h> // PATH_MAX
#include <errno.h>

void print_mode_info(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("파일종류: 일반파일\n");
    } else if (S_ISDIR(mode)) {
        printf("파일종류: 디렉토리\n");
    } else if (S_ISLNK(mode)) {
        printf("파일종류: 심볼릭 링크 파일\n");
    } else if (S_ISCHR(mode)) {
        printf("파일종류: 문자장치 특수파일\n");
    } else if (S_ISBLK(mode)) {
        printf("파일종류: 블록장치 특수파일\n");
    } else if (S_ISFIFO(mode)) {
        printf("파일종류: FIFO 파일\n");
    } else if (S_ISSOCK(mode)) {
        printf("파일종류: 소켓파일\n");
    } else {
        printf("파일종류: 기타\n");
    }
}

void print_file_info(const char *filename) {
    struct stat file_stat = {0};

    // lstat 시스템 호출을 통해 파일의 정보를 얻는다.
    if (lstat(filename, &file_stat) == -1) {
        perror("lstat");
        return;
    }

    // 파일명 출력
    printf("파일명: %s\n", filename);

    // inode 번호 출력
    printf("inode 번호: %lu\n", (unsigned long)file_stat.st_ino);

    // 파일 종류 출력
    print_mode_info(file_stat.st_mode);

    // 접근 권한 출력 (8진수 형식)
    printf("접근권한: %o\n", (unsigned int)file_stat.st_mode);

    // UID 출력
    printf("UID: %u\n", (unsigned int)file_stat.st_uid);

    // 심볼릭 링크일 경우, 링크 경로 및 원본 파일 정보 출력
    if (S_ISLNK(file_stat.st_mode)) {
        char target_path[PATH_MAX] = {0};

        if (realpath(filename, target_path) == NULL) {
            perror("realpath");
            return;
        }

        printf("------------\n");
        printf("원본 파일 경로 (realpath): %s\n", target_path);

        struct stat target_stat = {0};
        
        // 원본파일의 정보 읽기
        if (stat(filename, &target_stat) == -1) {
            perror("stat (원본 파일)");
            return;
        }

        printf("\n[원본 파일 정보]\n");
        printf("inode 번호: %lu\n", (unsigned long)target_stat.st_ino);
        print_mode_info(target_stat.st_mode);
        printf("접근권한: %o\n", (unsigned int)target_stat.st_mode);
        printf("UID: %u\n", (unsigned int)target_stat.st_uid);
    }
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
