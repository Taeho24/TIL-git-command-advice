// Requirement 2
/* 저수준 파일 입출력을 이용해 파일을 복사하는 프로그램을 작성하시오. 이때 파일명은 명령행인자로 받는다.
ex. 
han.c를 bit.c로 복사
$ newcp han.c bit.c */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024 // 버퍼 크기 정의

int main(int argc, char *argv[]) {
    // 변수 초기화
    int src_fd = -1, dest_fd = -1; // 파일 디스크립터 초기화
    char buffer[BUF_SIZE];          // 데이터 버퍼
    ssize_t bytes_read = 0;         // 읽은 바이트 수

    if (argc != 3) {
        fprintf(stderr, "사용법: %s <원본 파일> <대상 파일>\n", argv[0]);
        return 1;
    }

    // 대상 파일이 이미 존재하는지 확인
    if (access(argv[2], F_OK) != -1) {
        fprintf(stderr, "에러: 대상 파일 '%s'가 이미 존재합니다.\n", argv[2]);
        return 1;  // 파일이 존재하면 에러 코드 반환
    }

    // 원본 파일 열기 (읽기 전용)
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    // 대상 파일 열기 (쓰기 모드드, 없으면 생성, 권한은 0644)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("대상 파일 열기 실패");
        close(src_fd);
        return 1;
    }

    // 파일을 버퍼로 읽고 쓰기
    while ((bytes_read = read(src_fd, buffer, BUF_SIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("파일 쓰기 실패");
            close(src_fd);
            close(dest_fd);
            printf("파일 복사 중 오류가 발생했습니다.\n");
            exit(1);
        }
    }

    if (bytes_read == -1) {
        perror("파일 읽기 실패");
    }

    // 파일 닫기
    close(dest_fd);
    close(src_fd);

    printf("파일 복사가 완료되었습니다.\n");

    return 0;
}
