// Requirement 3
/* lseek() 함수를 이용해 다음 데이터 파일을 읽어 출력 형태와 같이 출력하는 프로그램을 작성하시오.
ex.
In data file: abcdefghijklmnopqrstuvwxyz
print: acegikmoqsuwy */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1  // 한 문자씩 읽기 위해 버퍼 크기를 1로 설정

int main(int argc, char *argv[]) {
    // 파일 디스크립터
    int fd = -1;
    char ch = '\0';  // 읽을 문자
    off_t offset = 0;  // 파일의 현재 오프셋

    if (argc != 2) {
        fprintf(stderr, "사용법: %s <파일명명>\n", argv[0]);
        return 1;
    }

    // 파일 열기 (읽기 전용)
    fd = open(argv[1], O_RDONLY);  // 파일 이름은 "data.txt"로 가정
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }

    // 파일에서 문자 읽기
    while (1) {
        // 현재 위치로 오프셋 이동 (offset 위치로 이동)
        if (lseek(fd, offset, SEEK_SET) == -1) {
            perror("lseek 실패");
            close(fd);
            return 1;
        }

        // 문자 읽기
        if (read(fd, &ch, BUF_SIZE) == 1) {
            // 홀수 인덱스 문자 출력 (0부터 시작이므로 짝수 인덱스)
            if (offset % 2 == 0) {
                write(STDOUT_FILENO, &ch, BUF_SIZE);
            }
        } else {
            break;  // 파일 끝에 도달하면 종료
        }

        // 다음 문자로 이동
        offset++;
    }

    // 파일 닫기
    close(fd);
    return 0;
}

