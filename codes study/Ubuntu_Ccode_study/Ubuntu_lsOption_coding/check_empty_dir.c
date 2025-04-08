// Requirement 1
// 디렉터리가 비어 있는지 확인한 후 디렉터리가 비어 있다는 메시지를 출력하고 해당 디렉터리를 삭제하는 프로그램을 작성하시오.


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

int is_directory_empty(const char *dir_path) {
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    
    if (dir == NULL) {
        perror("디렉터리 열기 실패");
        return -1;  // 디렉터리 열기 실패
    }

    // 디렉터리 내의 첫 번째 항목은 '.' (자기 자신)과 '..' (부모 디렉터리)
    // 이 외에 다른 항목이 있으면 디렉터리가 비어 있지 않다고 판단
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return 0;  // 디렉터리가 비어 있지 않음
        }
    }
    
    closedir(dir);
    return 1;  // 디렉터리가 비어 있음
}

int main() {
    char dir_path[256] = ""; // char d_name[256];
    
    // 디렉터리 경로 입력
    printf("삭제할 디렉터리 경로를 입력하세요: ");
    if (fgets(dir_path, sizeof(dir_path), stdin) == NULL) {
        perror("입력 오류");
        exit(1);
    }
    dir_path[strcspn(dir_path, "\n")] = 0;  // fgets()로 입력 후, 개행 문자 제거
    // str[strlen(str) - 1] = '\0'; // 문자열에 개형문자가 있다고 가정하는 코드로 오류가능성 있음

    // 디렉터리가 비어 있는지 확인
    int is_empty = is_directory_empty(dir_path);
    
    if (is_empty == 1) {
        // 디렉터리가 비어 있으면 삭제
        if (rmdir(dir_path) == 0) {
            printf("디렉터리가 비어 있어 삭제되었습니다.\n");
        } else {
            perror("디렉터리 삭제 실패");
        }
    } else if (is_empty == 0) {
        // 디렉터리가 비어 있지 않으면
        printf("디렉터리가 비어 있지 않습니다.\n");
    } else if (is_empty == -1) {
        // 경로가 유효하지 않으면
        printf("디렉터리 경로가 유효하지 않거나 접근할 수 없습니다.\n");
        exit(1);
    }

    return 0;
}
