#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
#include <time.h>


void  handle(union sigval v){
    time_t t;
    char p[32];
    time(&t);
    strftime(p, sizeof(p), "%T", localtime(&t));
    printf("%s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
    return;
}

void  handle2(union sigval v){
    time_t t;
    char p[32];
    time(&t);
    strftime(p, sizeof(p), "%T", localtime(&t));
    printf("=======handle 2======= %s thread %lu, val = %d, signal captured.\n", p, pthread_self(), v.sival_int);
    return;
}


int main(int argc, char *argv[]){

    struct sigevent evp;
    struct itimerspec ts;
    timer_t timer;
    int ret;
    memset   (&evp, 0, sizeof(evp));
    evp.sigev_value.sival_ptr = &timer;
    evp.sigev_notify = SIGEV_THREAD;
    evp.sigev_notify_function = handle;
    evp.sigev_value.sival_int = 3;   //作为handle()的参数
    ret = timer_create(CLOCK_REALTIME, &evp, &timer);
    if( ret){
        perror("timer_create");
    }

    ts.it_interval.tv_sec = 1;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 1;
    ts.it_value.tv_nsec = 0;
    ret = timer_settime(timer, TIMER_ABSTIME, &ts, NULL);
    if( ret )
    {
        perror("timer_settime");
    }


    struct sigevent evp2;
    struct itimerspec ts2;
    timer_t timer2;
    int ret2;
    memset   (&evp2, 0, sizeof(evp2));
    evp2.sigev_value.sival_ptr = &timer2;
    evp2.sigev_notify = SIGEV_THREAD;
    evp2.sigev_notify_function = handle2;
    evp2.sigev_value.sival_int = 8;   //作为handle()的参数
    ret2 = timer_create(CLOCK_REALTIME, &evp2, &timer2);
    if( ret){
        perror("timer_create");
    }

    ts2.it_interval.tv_sec = 0;
    ts2.it_interval.tv_nsec = 0;
    ts2.it_value.tv_sec = 10;
    ts2.it_value.tv_nsec = 0;
    ret2 = timer_settime(timer2, 0, &ts2, NULL);
    if( ret2 )
    {
        perror("timer_settime2");
    }

    while(1);

}
