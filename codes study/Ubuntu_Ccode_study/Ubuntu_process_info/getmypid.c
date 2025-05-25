// Requirement 1
/* 명령행 인자로 PID를 입력받아 해당 프로세스가 속한 프로세스 그룹ID(PGID), 세션 ID를 출력하는 프로그램을 작성하시오.
 명령행 인자로 지정한 PID가 0이면 현재 프로세스를 대상으로 PPID와 PGID, 세션ID를 구한다. 
 sleep(100)등 프로세스를 생성하고 동작하는것을 확인*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pgid = -1;
    pid_t sid = -1;
    pid_t target_pid;
    char *endptr;

    // 명령행 인자 처리
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <PID>\n", argv[0]);
        return 1;
    }

    // strtol을 사용하여 문자열을 정수로 변환
    target_pid = strtol(argv[1], &endptr, 10);

    // 변환이 실패했을 경우 처리
    if (*endptr != '\0') {
        fprintf(stderr, "유효하지 않은 PID: %s\n", argv[1]);
        return 1;
    }

    // 음수 PID 처리: PID는 0 또는 양수여야 함
    if (target_pid < 0) {
        fprintf(stderr, "PID는 음수일 수 없습니다. 유효한 PID를 입력하세요.\n");
        return 1;
    }

    // PID가 0이면 현재 프로세스를 대상으로 처리
    if (target_pid == 0) {
        target_pid = getpid();
    }

    // 해당 프로세스의 PGID와 Session ID 구하기
    pgid = getpgid(target_pid); // 프로세스 그룹 ID
    sid = getsid(target_pid);   // 세션 ID

    // 오류 처리: getpgid() 또는 getsid()에서 -1을 반환할 경우
    if (pgid == -1) {
        perror("getpgid() 호출 실패");
        return 1;
    }
    if (sid == -1) {
        perror("getsid() 호출 실패");
        return 1;
    }

    printf("PID: %d\n", target_pid);
    printf("PGID: %d\n", pgid);
    printf("Session ID: %d\n", sid);

    sleep(100);

    return 0;
}
