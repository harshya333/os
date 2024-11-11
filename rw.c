#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

sem_t r,w;
int rcount=0;

void* reader(void* arg){
    sem_wait(&r);
    rcount++;
    if(rcount==1){
        sem_wait(&w);
    }
    
    sem_post(&r);
    printf("\nReading operation is performed");
    sem_wait(&r);
    rcount--;
    if(rcount==0){
        sem_post(&w);
    }
    sem_post(&r);
    return NULL;
    
}

void* writer(void* arg){
    sem_wait(&w);
    printf("\n Writing operation is performed");
    sem_post(&w);
    return NULL;
    
}

void main(){
    pthread_t Rtid[5];
    pthread_t Wtid[5];
    sem_init(&w,0,1);
    sem_init(&r,0,1);
    
    for(int i=0;i<5;i++){
        pthread_create(&Wtid[i],NULL,writer,NULL);
        pthread_create(&Rtid[i],NULL,reader,NULL);
        
    }
    
    for(int i=0;i<5;i++){
        pthread_join(Rtid[i],NULL);
         pthread_join(Wtid[i],NULL);
        
    }
}
