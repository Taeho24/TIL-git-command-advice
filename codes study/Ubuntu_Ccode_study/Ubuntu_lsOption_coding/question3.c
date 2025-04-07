// Requirement 3
// 파일명과 디렉터리 경로명을 명령행 인자로 입력받고 인자로 입력한 파일이 해당 디렉터리에 있는지 확인하는 프로그램을 작성하시오.


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int file_exists_in_directory(const char *dir_path, const char *filename) {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if (dir == NULL) {
        perror("디렉터리 열기 실패");
        return 0;
    }

    // 디렉터리 내 항목을 읽어서 파일명이 일치하는지 확인
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, filename) == 0) {
            closedir(dir);
            return 1;  // 파일이 존재함
        }
    }

    closedir(dir);
    return 0;  // 파일이 존재하지 않음
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "사용법: %s <디렉터리 경로> <파일명>\n", argv[0]);
        return 1;
    }

    const char *dir_path = argv[1];
    const char *filename = argv[2];

    // 파일 존재 여부 확인
    if (file_exists_in_directory(dir_path, filename)) {
        printf("파일 '%s'이(가) 디렉터리 '%s'에 존재합니다.\n", filename, dir_path);
    } else {
        printf("파일 '%s'이(가) 디렉터리 '%s'에 존재하지 않습니다.\n", filename, dir_path);
    }

    return 0;
}
