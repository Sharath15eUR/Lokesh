#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<math.h>
#include<signal.h>

pthread_mutex_t lock;
int time_range=10; // set 100 for o/p  purpose val sset to 10
volatile sig_atomic_t stop=0;

int is_prime(const int num){
    for(int i=2;i<=sqrt(num);++i){
        if (num%i == 0){
            return 0;
        }
    }
    return 1;
}

void handle_signint(int sig){
    stop=1;
    printf("\nsig int : %d :request raised, terminating gracefully with interupt  after curr task complete",sig);
}


void* thread_A_func(void* n ){
    int N = *(int*)n;
    int* sum= (int*)calloc(1,sizeof(int));
    for(int i=2;N>0;++i){
        if(is_prime((const int)i)){
            *sum+=i;
            N--;
        }
    }
    return sum;
}

void* thread_B_func(void* arg) {
    time_t start = time(NULL);
    while (!stop) {
        time_t now = time(NULL);
        if (now - start > time_range || stop) break;

        sleep(2);

        now = time(NULL);
        if (now - start > time_range || stop) break;

        pthread_mutex_lock(&lock);
        printf("\nThread 1 running (%d s)",time(NULL)-start);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* thread_C_func(void* arg){

    time_t start = time(NULL);
    while(!stop){
        time_t now = time(NULL);
        if(now-start > time_range || stop)break;

        sleep(3);
        now=time(NULL);
        if(now-start >time_range || stop )break;
        pthread_mutex_lock(&lock);
        printf("\nThread 2 running (%d s)",time(NULL)-start);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    
    signal(SIGINT,handle_signint);

    pthread_t ta,tb,tc;
    pthread_mutex_init(&lock,NULL);
    int n;
    void* prime_sum;

    printf("ent n for prime sum: ");
    scanf("%d",&n);

    pthread_create(&ta,NULL,&thread_A_func,(void*)&n);
    pthread_create(&tb,NULL,thread_B_func,NULL);
    pthread_create(&tc,NULL,thread_C_func,NULL);

    pthread_join(ta,&prime_sum);
    pthread_join(tb,NULL);
    pthread_join(tc,NULL);
    pthread_mutex_destroy(&lock);

    printf("\nsum of first %d prime no is %d",n,*(int*)prime_sum);

    return 0;

}