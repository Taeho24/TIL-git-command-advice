// Requirement 1
/* 저수준 파일 입출력을 이용해 ‘newcat’프로그램을 작성하시오. 이때 행 번호를 붙여서 출력하고 파일명은 명령행 인자로 받는다.
ex.
$ newcat han.c */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    // 파일 디스크립터와 버퍼 초기화
    int fd = -1;
    char buffer[BUF_SIZE];
    ssize_t bytes_read = 0;
    int line_number = 1;  // 행 번호 시작 (1부터 시작)

    // 명령행 인자 확인
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명>\n", argv[0]);
        return 1;
    }

    // 파일 열기 (읽기 전용)
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }

    // 파일 내용 읽기
    while ((bytes_read = read(fd, buffer, BUF_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i-1] == '\n') {
                // 줄 번호 출력
                dprintf(STDOUT_FILENO, "%d ", line_number++);
            }
            // 한 문자자씩 출력
            write(STDOUT_FILENO, &buffer[i], 1);
        }
    }

    if (bytes_read == -1) {
        perror("파일 읽기 실패");
        close(fd);
        return 1;
    }

    // 파일 닫기
    close(fd);
    return 0;
}

