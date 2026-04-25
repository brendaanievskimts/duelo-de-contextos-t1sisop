#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL 1000000000LL

long long contador_global = 0;

pthread_mutex_t mutex;

void *incrementa_sem_mutex(void *arg)
{
    long long inc = *((long long*)arg);

    for(long long i=0; i<inc; i++)
    {
        contador_global++;
    }

    return NULL;
}

void *incrementa_com_mutex(void *arg)
{
    long long inc = *((long long*)arg);

    long long local = 0;

    for(long long i=0; i<inc; i++)
    {
        local++;
    }

    pthread_mutex_lock(&mutex);

    contador_global += local;

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void experimento_T1(int n)
{
    pthread_t threads[n];

    long long por_thread = TOTAL/n;

    contador_global = 0;

    printf("\nExecutando T1...\n");

    for(int i=0;i<n;i++)
    {
        if(pthread_create(&threads[i], NULL, incrementa_sem_mutex, &por_thread) != 0)
        {
            printf("Erro criando thread\n");
            exit(1);
        }
    }

    for(int i=0;i<n;i++)
        pthread_join(threads[i], NULL);

    printf("T1 contador final: %lld\n",contador_global);
}

void experimento_T2(int n)
{
    pthread_t threads[n];

    long long por_thread = TOTAL/n;

    contador_global=0;

    printf("\nExecutando T2...\n");

    pthread_mutex_init(&mutex, NULL);

    for(int i=0;i<n;i++)
    {
        if(pthread_create(&threads[i], NULL, incrementa_com_mutex, &por_thread) !=0)
        {
            printf("Erro criando thread\n");
            exit(1);
        }
    }

    for(int i=0;i<n;i++)
        pthread_join(threads[i], NULL);

    printf("T2 contador final: %lld\n", contador_global);

    pthread_mutex_destroy(&mutex);
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Uso: ./threads N\n");
        return 1;
    }

    int n=atoi(argv[1]);

    experimento_T1(n);

    experimento_T2(n);

    return 0;
}