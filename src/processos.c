#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define TOTAL 1000000000LL

void experimento_P1(int n)
{
    int id_memoria = shmget(IPC_PRIVATE, sizeof(long long), IPC_CREAT | 0666);

    if(id_memoria < 0)
    {
        perror("shmget");
        exit(1);
    }

    long long *contador_global = shmat(id_memoria,NULL,0);

    *contador_global = 0;

    long long incrementos = TOTAL/n;

    printf("\nExecutando P1...\n");

    for(int i=0;i<n;i++)
    {
        if(fork()==0)
        {
            for(long long j=0;j<incrementos;j++)
            {
                (*contador_global)++;
            }

            shmdt(contador_global);

            exit(0);
        }
    }


    for(int i=0;i<n;i++)
        wait(NULL);


    printf("P1 contador resultado: %lld\n", *contador_global);


    shmdt(contador_global);

    shmctl(id_memoria,IPC_RMID,NULL);
}

void experimento_P2(int n)
{
    int id_memoria = shmget(IPC_PRIVATE,sizeof(long long),IPC_CREAT | 0666);

    long long *contador_global = shmat(id_memoria,NULL,0);

    *contador_global=0;


    sem_unlink("/meusem");

    sem_t *semaforo = sem_open("/meusem",O_CREAT,0644,1);

    long long incrementos = TOTAL/n;

    printf("\nExecutando P2...\n");

    for(int i=0;i<n;i++)
    {
        if(fork()==0)
        {
            long long contador_local=0;

            for(long long j=0;j<incrementos;j++)
            {
                contador_local++;
            }

            sem_wait(semaforo);

            (*contador_global)+=
               contador_local;

            sem_post(semaforo);

            shmdt(contador_global);

            exit(0);
        }
    }

    for(int i=0;i<n;i++)
        wait(NULL);

    printf("P2 contador resultado: %lld\n",*contador_global);

    sem_close(semaforo);

    sem_unlink("/meusem");

    shmdt(contador_global);

    shmctl(id_memoria,IPC_RMID,NULL);
}

int main(int argc,char *argv[])
{
   int n=atoi(argv[1]);

   experimento_P1(n);

   experimento_P2(n);

   return 0;
}