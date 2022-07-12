#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

bool looping = true;
int count = 0;

void sig_handle(int signo)
{
    printf("Cought signo: %d count: %d\n", signo, ++count);
    if (count == 5)
        looping = false;
}

int main()
{
    timer_t timer;
    struct itimerspec newit;
    struct timespec sl = {
        .tv_sec = 0,
        .tv_nsec = 200000000
    };
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sig_handle;
    sigaction(SIGALRM, &sa, NULL);

    timer_create(CLOCK_REALTIME, NULL, &timer);

    newit.it_value.tv_sec = 1;
    newit.it_value.tv_nsec = 0;
    newit.it_interval.tv_sec = 1;
    newit.it_interval.tv_nsec = 0;

    timer_settime(timer, 0, &newit, NULL);

    while (looping) {
        printf("do something...\n");
        nanosleep(&sl, NULL);
    }

    return 0;
}
