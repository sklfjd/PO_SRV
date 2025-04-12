#include <stdio.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include "thLib.h"

int main() {
	pthread_attr_t attr1, attr2;
	
        printf("Prog threads PID %d \n", getpid());

	pthread_attr_init(&attr1);
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr1, SCHED_RR);
	attr1.param.sched_priority = 13;

	pthread_attr_init(&attr2);
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
	attr1.param.sched_priority = 10;

        pthread_create(&thread_id1, NULL, long_thread1, NULL);
        pthread_create(&thread_id2, NULL, long_thread2, NULL);

	pthread_join(thread_id1, NULL);
	
	pthread_attr_destroy(attr1);
	pthread_attr_destroy(attr2);

        return 0;
}
