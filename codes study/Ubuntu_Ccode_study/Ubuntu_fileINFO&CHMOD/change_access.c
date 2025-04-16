// Requirement 2
/* 명령행 인자로 받은 파일의 기존 접근 권한을 출력하고 접근 권한을 변경하는 프로그램을 작성하시오(숫자 모드 기능 구현).
ex.
$ mychmod 777 a.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void print_permissions(mode_t mode) {
    printf("권한: ");
    printf((S_IRUSR & mode) ? "r" : "-");
    printf((S_IWUSR & mode) ? "w" : "-");
    printf((S_IXUSR & mode) ? "x" : "-");
    printf((S_IRGRP & mode) ? "r" : "-");
    printf((S_IWGRP & mode) ? "w" : "-");
    printf((S_IXGRP & mode) ? "x" : "-");
    printf((S_IROTH & mode) ? "r" : "-");
    printf((S_IWOTH & mode) ? "w" : "-");
    printf((S_IXOTH & mode) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <상수값 권한> <파일명>\n", argv[0]);
        return 1;
    }

    // 권한이 올바른 8진수 형식인지 확인
    char *endptr;
    mode_t new_mode = strtol(argv[1], &endptr, 8);  
    
    // 잘못된 숫자나 범위 초과 시 에러 처리
    if (*endptr != '\0' || new_mode < 0 || new_mode > 0777) {
        fprintf(stderr, "에러: 권한 값은 8진수여야 하며 000 ~ 777 범위여야 합니다.\n");
        return 1;
    }

    // 입력 받은 파일 경로
    char *file = argv[2];

    // 파일 정보 가져오기
    struct stat file_stat;

    // 파일의 상태 가져오기
    if (stat(file, &file_stat) == -1) {
        if (errno == ENOENT) {
            perror("에러: 파일을 찾을 수 없습니다");
        } else {
            perror("stat");
        }
        return 1;
    }

    // 기존 파일 접근 권한 출력
    printf("변경 전 ");
    print_permissions(file_stat.st_mode);

    // 파일의 접근 권한 변경
    if (chmod(file, new_mode) == -1) {
        perror("chmod");
        return 1;
    }

    // 변경된 권한 출력
    if (stat(file, &file_stat) == -1) {
        perror("stat");
        return 1;
    } else {
        printf("Permissions successfully changed to %o\n", new_mode);
    }
    printf("변경 후 ");
    print_permissions(file_stat.st_mode);

    return 0;
}
