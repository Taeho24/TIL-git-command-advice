// Requirement 2
// ‘.’과 ‘..’항목을 제외하고 디렉터리에 있는 파일이나 하위 디렉터리명을 출력하는 myls 프로그램을 작성하시오.


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void myls(const char *dir_path) {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if (dir == NULL) {
        perror("디렉터리 열기 실패");
        return;
    }

    // 디렉터리 내 항목을 읽어서 '.'과 '..'을 제외한 항목 출력
    while ((entry = readdir(dir)) != NULL) {
        // '.'과 '..' 항목을 제외하고 출력
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char dir_path[256];

    // 디렉터리 경로 입력
    printf("디렉터리 경로를 입력하세요: ");
    scanf("%s", dir_path);

    // 디렉터리의 내용 출력
    myls(dir_path);

    return 0;
}
