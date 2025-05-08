#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/sched.h>

void server(void) {
    int rcvid;
    int chid;
    char message[512];
    struct sched_param param;

    // Устанавливаем приоритет и алгоритм планирования
    param.sched_priority = 6;
    pthread_setschedparam(pthread_self(), SCHED_RR, &param);

    printf("Belova Ksenia Egorovna\nGroup: I914B\n");
    printf("Server start working \n");
    printf("Server priority: %d, policy: RR\n", param.sched_priority);

    chid = ChannelCreate(0);
    printf("Channel id: %d \n", chid);
    printf("PID: %d \n", getpid());

    while (1) {
        rcvid = MsgReceive(chid, message, sizeof(message), NULL);
        printf("Received message, rcvid %X \n", rcvid);
        printf("Message:: \"%s\". \n", message);
        strcpy(message, "This is answer");
        MsgReply(rcvid, EOK, message, sizeof(message));
        printf("Replied with: \"%s\" \n", message);
    }
}

int main(void) {
    printf("Prog server \n");
    server();
    return 0;
}
