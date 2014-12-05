#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <semaphore.h>
#define BUFFER_N 8

struct buffer
{
	int write;
	clock_t cpu_time;
	int round;
	pid_t pid;
}msgbox[BUFFER_N];

//_syscall0(pid_t,gettid); //define gettid()

pthread_mutex_t mutex;
//pthread_cond_t empty,full;
sem_t empty,full;

void  p_thread1(void *arg);
void  p_thread2(void *arg);
void  p_thread3(void *arg);

void  c_thread1(void *arg);
void  c_thread2(void *arg);
void  c_thread3(void *arg);
void  c_thread4(void *arg);
void  c_thread5(void *arg);


int main(int argc, char *argv[]){
    pthread_t pth1,pth2,pth3;
    pthread_t cth1,cth2,cth3,cth4,cth5;

    int i;
    for (i=0;i<BUFFER_N;i++){
        msgbox[i].write = 0;
    }

    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,1,BUFFER_N);
    sem_init(&full,1,0);

    printf("!\n");
    //printf("%s\n", empty);

    pthread_create(&pth1,NULL,(void *)p_thread1, NULL);
    pthread_create(&pth2,NULL,(void *)p_thread2, NULL);
    pthread_create(&pth3,NULL,(void *)p_thread3, NULL);

    pthread_create(&cth1,NULL,(void *)c_thread1, NULL);
    pthread_create(&cth2,NULL,(void *)c_thread2, NULL);
    pthread_create(&cth3,NULL,(void *)c_thread3, NULL);
    pthread_create(&cth4,NULL,(void *)c_thread4, NULL);
    pthread_create(&cth5,NULL,(void *)c_thread5, NULL);

    pthread_join(pth1,NULL);
    pthread_join(pth2,NULL);
    pthread_join(pth3,NULL);

    pthread_join(cth1,NULL);
    pthread_join(cth2,NULL);
    pthread_join(cth3,NULL);
    pthread_join(cth4,NULL);
    pthread_join(cth5,NULL);

    printf("Executed successfully\n\n");
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    exit(0);
}

void p_thread1(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<6){
	  	tmp.write = 1;
  		tmp.cpu_time = clock();
	  	tmp.round = i;
  		tmp.pid = pthread_self();

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==0){
                msgbox[j].write = tmp.write;
                msgbox[j].cpu_time = tmp.cpu_time;
                msgbox[j].round = tmp.round;
                msgbox[j].pid = tmp.pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void p_thread2(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<6){
	  	tmp.write = 1;
  		tmp.cpu_time = clock();
	  	tmp.round = i;
  		tmp.pid = pthread_self();

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==0){
                msgbox[j].write = tmp.write;
                msgbox[j].cpu_time = tmp.cpu_time;
                msgbox[j].round = tmp.round;
                msgbox[j].pid = tmp.pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void p_thread3(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<6){
	  	tmp.write = 1;
  		tmp.cpu_time = clock();
	  	tmp.round = i;
  		tmp.pid = pthread_self();

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==0){
                msgbox[j].write = tmp.write;
                msgbox[j].cpu_time = tmp.cpu_time;
                msgbox[j].round = tmp.round;
                msgbox[j].pid = tmp.pid;
                break;
            }
        }
        if (j!=8){
           i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void c_thread1(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<4){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==1){
                tmp.write = msgbox[j].write;//redundant
                msgbox[j].write = 0;
                tmp.cpu_time = msgbox[j].cpu_time;
                tmp.round = msgbox[j].round;
                tmp.pid = msgbox[j].pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer Process 1:\n%ld ms\tRound %d\tPID[%d]\n",(long)tmp.cpu_time,tmp.round,tmp.pid);
    }
}

void c_thread2(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<4){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==1){
                tmp.write = msgbox[j].write;//redundant
                msgbox[j].write = 0;
                tmp.cpu_time = msgbox[j].cpu_time;
                tmp.round = msgbox[j].round;
                tmp.pid = msgbox[j].pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer Process 2:\n%ld ms\tRound %d\tPID[%d]\n",(long)tmp.cpu_time,tmp.round,tmp.pid);
    }
}

void c_thread3(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<4){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==1){
                tmp.write = msgbox[j].write;//redundant
                msgbox[j].write = 0;
                tmp.cpu_time = msgbox[j].cpu_time;
                tmp.round = msgbox[j].round;
                tmp.pid = msgbox[j].pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer Process 3:\n%ld ms\tRound %d\tPID[%d]\n",(long)tmp.cpu_time,tmp.round,tmp.pid);
    }
}

void c_thread4(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<4){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==1){
                tmp.write = msgbox[j].write;//redundant
                msgbox[j].write = 0;
                tmp.cpu_time = msgbox[j].cpu_time;
                tmp.round = msgbox[j].round;
                tmp.pid = msgbox[j].pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer Process 4:\n%ld ms\tRound %d\tPID[%d]\n",(long)tmp.cpu_time,tmp.round,tmp.pid);
    }
}

void c_thread5(void *arg){
    int i,j;
    struct buffer tmp;

    i = 1;
	while (i<4){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        for (j = 0; j < BUFFER_N; ++j){
            if (msgbox[j].write==1){
                tmp.write = msgbox[j].write;//redundant
                msgbox[j].write = 0;
                tmp.cpu_time = msgbox[j].cpu_time;
                tmp.round = msgbox[j].round;
                tmp.pid = msgbox[j].pid;
                break;
            }
        }
        if (j!=8){
            i++;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Consumer Process 5:\n%ld ms\tRound %d\tPID[%d]\n",(long)tmp.cpu_time,tmp.round,tmp.pid);
    }
}
