#include <stdio.h>
#include <process.h>

int main() {
        pid_t pid;
        if ((pid = fork()) == -1) {
                return 1;
        }
        if (pid == 0) {
                printf("Child process, Belova Ksenia Egorovna\n");
        }
        else {
                printf("Parent process, Group: I914B\n");
        }
        sleep(10);
        return 0;
}
