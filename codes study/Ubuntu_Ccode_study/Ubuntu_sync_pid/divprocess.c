// Requirement 1
/* fork() 함수를 사용해 자식 프로세스에서는 현재 디렉터리의 절대 경로를 출력하고
 부모 프로세스에서는 현재 디렉터리의 내용을 출력하는 프로그램을 작성하시오. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main() {
    int status = 0;

    // fork() 호출
    pid_t pid = fork();

    if (pid < 0) {
        // fork 실패
        perror("fork 실패");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 자식 프로세스: 현재 디렉토리 절대 경로 출력
        char *cwd = NULL;

        cwd = getcwd(NULL, 0);  // 동적으로 버퍼 할당
        if (cwd == NULL) {
            perror("getcwd 실패");
            exit(EXIT_FAILURE);
        }

        printf("[자식] 현재 디렉토리의 절대 경로\n: %s\n", cwd);

        free(cwd);  // 동적 메모리 해제
        exit(EXIT_SUCCESS);
    } else {
        // 부모 프로세스: 디렉토리 내용 출력
        struct dirent *entry = NULL;
        DIR *dir = opendir(".");

        if (dir == NULL) {
            perror("opendir 실패");
            exit(EXIT_FAILURE);
        }

        printf("[부모] 현재 디렉토리의 파일 목록\n");

        int file_count = 0;
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printf("%-20s", entry->d_name);
                if (++file_count % 4 == 0) printf("\n");
            }
        }
        printf("\n");


        if (closedir(dir) != 0) {
            perror("closedir 실패");
            exit(EXIT_FAILURE);
        }

        // 자식 프로세스가 끝날 때까지 대기
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid 실패");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
