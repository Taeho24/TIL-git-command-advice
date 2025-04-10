// Requirement 2
// ‘.’과 ‘..’항목을 제외하고 디렉터리에 있는 파일이나 하위 디렉터리명을 출력하는 myls 프로그램을 작성하시오.


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

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

void normalize_path(char *path) {
    char *dirs[256] = {0};  // 경로 컴포넌트를 저장할 배열
    int dir_count = 0;
    
    // 경로를 '/' 기준으로 분리하여 컴포넌트별로 저장
    char *token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, ".") == 0) {
            // '.'은 무시
            token = strtok(NULL, "/");
            continue;
        }
        if (strcmp(token, "..") == 0) {
            // '..'은 부모 디렉터리로 이동, dir_count가 0보다 클 때만 이동
            if (dir_count > 0) {
                dir_count--;
            } else {
                // 이미 최상위 디렉터리라면 경고 메시지 출력
                // printf("경고: 부모 디렉터리로 이동할 수 없습니다. 이미 최상위 디렉터리입니다.\n");
                fprintf(stderr, "경고: 부모 디렉터리로 이동할 수 없습니다. 이미 최상위 디렉터리입니다.\n");
            }
        } else {
            // 일반적인 디렉터리나 파일은 dirs 배열에 추가
            dirs[dir_count] = token;
            dir_count++;
        }
        token = strtok(NULL, "/");
    }
    
    // '/'로 구분하여 최종 경로를 생성
    path[0] = '\0';  // 초기화
    for (int i = 0; i < dir_count; i++) {
        strcat(path, "/");
        strcat(path, dirs[i]);
    }

    // 경로가 빈 문자열일 경우, 루트 디렉터리('/')로 처리
    if (path[0] == '\0') {
        strcpy(path, "/");
    }
}

int main() {
    char dir_path[256] = "";
    char absolute_path[512]=""; // 절대경로를 저장

    // 디렉터리 경로 입력
    printf("디렉터리 경로를 입력하세요: ");
    if (fgets(dir_path, sizeof(dir_path), stdin) == NULL) {
        perror("입력 오류");
        exit(1);
    }
    
    // 개행 문자 제거
    dir_path[strcspn(dir_path, "\n")] = 0;

    // 입력된 경로가 상대 경로일 경우 절대 경로로 변환
    if (dir_path[0] != '/') {
        // 현재 작업 디렉터리 가져오기
        if (getcwd(absolute_path, sizeof(absolute_path)) == NULL) {
            perror("현재 작업 디렉터리 가져오기 실패");
            exit(1);
        }
        
        // 작업 디렉터리 경로 뒤에 '/' 추가
        if (absolute_path[strlen(absolute_path) - 1] != '/') {
            strcat(absolute_path, "/");
        }
        
        // 상대 경로와 결합하여 절대 경로 생성
        strcat(absolute_path, dir_path);

        // 절대 경로로 변경
        strcpy(dir_path, absolute_path);
    }

    // 경로 정리:   /home/user/./mydir -> /home/user/mydir
    //              /home/user/../mydir -> /home/mydir
    normalize_path(absolute_path);
    // 결과 오류:    /home/user/../mydir -> //mydir

    printf("디렉터리 '%s'의 내용\n", absolute_path);

    // 디렉터리의 내용 출력
    myls(dir_path);

    return 0;
}
