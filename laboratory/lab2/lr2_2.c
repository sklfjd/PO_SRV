#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/sched.h>
#include <string.h>

int main(void) {
    char smsg[20];
    char rmsg[200];
    int coid;
    long serv_pid;
    struct sched_param param;

    // Устанавливаем приоритет и алгоритм планирования
    param.sched_priority = 12;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);
	
    printf("Client program, priority: %d, policy: RR\n", param.sched_priority);
    printf("Enter server PID: ");
    scanf("%ld", &serv_pid);
    printf("Entered %ld \n", serv_pid);
    printf("Belova Ksenia Egorovna\nGroup: I914B\n");

    coid = ConnectAttach(0, serv_pid, 1, 0, 0);
    printf("Connect result %d \n, Enter message: ", coid);
    scanf("%s", smsg);
    printf("Entered %s \n", smsg);

    if (MsgSend(coid, smsg, strlen(smsg) + 1, rmsg, sizeof(rmsg)) == -1) {
        printf("Error MsgSend \n");
    } else {
        printf("Received reply: %s \n", rmsg);
    }

    return 0;
}
