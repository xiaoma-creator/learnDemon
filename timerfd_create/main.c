#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>        /* Definition of uint64_t */
#include <string.h>
#include <sys/select.h>

#define handle_error(msg) \
	   do { printf(msg); exit(EXIT_FAILURE); } while (0)

static void print_elapsed_time(void)
{
   static struct timespec start;
   struct timespec curr;
   static int first_call = 1;
   int secs, nsecs;

   if (first_call)
   {
      first_call = 0;
      if (clock_gettime(CLOCK_MONOTONIC, &start) == -1)
	   handle_error("clock_gettime");
   }

   if (clock_gettime(CLOCK_MONOTONIC, &curr) == -1)
      handle_error("clock_gettime");

   secs = curr.tv_sec - start.tv_sec;
   nsecs = curr.tv_nsec - start.tv_nsec;
   if (nsecs < 0)
   {
	   secs--;
	   nsecs += 1000000000;
   }
   printf("%d.%03d: ", secs, (nsecs + 500000) / 1000000);
}


int main(int argc, char *argv[])
{
   struct itimerspec new_value;
   int max_exp, fd;
   struct timespec now;
   uint64_t exp, tot_exp = 0;
   ssize_t s;

   if ((argc != 2) && (argc != 4))
   {
	   ssize_t s;
	   printf("%s %d\n",__FUNCTION__, __LINE__);
	   if ((argc != 2) && (argc != 4))
	   {
		   fprintf(stderr, "%s init-secs [interval-secs max-exp]\n", argv[0]);
		   handle_error("argc argv is error");
	   }
   }

   if (clock_gettime(CLOCK_REALTIME, &now) == -1)
   {
      handle_error("clock_gettime");
   }

   /* Create a CLOCK_REALTIME absolute timer with initial
	  expiration and interval as specified in command line */

   new_value.it_value.tv_sec = now.tv_sec + atoi(argv[1]);
   new_value.it_value.tv_sec = atoi(argv[1]);
   new_value.it_value.tv_nsec = 0;
   if (argc == 2) {
	   new_value.it_interval.tv_sec = 0;
	   max_exp = 1;
   } else {
	   new_value.it_interval.tv_sec = atoi(argv[2]);
	   max_exp = atoi(argv[3]);
   }
   new_value.it_interval.tv_nsec = 0;

   fd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);
   if (fd == -1)
	   handle_error("timerfd_create");

   if (timerfd_settime(fd, 0, &new_value, NULL) == -1)
	   handle_error("timerfd_settime");

   print_elapsed_time();
   printf("timer started\n");

/*
   for (tot_exp = 0; tot_exp < max_exp;) {
	   s = read(fd, &exp, sizeof(uint64_t));
	   if (s != sizeof(uint64_t))
		   handle_error("read");

	   tot_exp += exp;
	   print_elapsed_time();
	   printf("read: %llu; total=%llu\n",
			   (unsigned long long) exp,
			   (unsigned long long) tot_exp);
   }
*/

    int maxfd = fd;
    int res = 0;
    uint64_t buff = 0;
    fd_set readfds;
    struct timeval timeout;

    memset(&timeout, 0, sizeof(struct timeval));

    do{
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        timeout.tv_sec = 1;
        res = select(fd+1, &readfds, NULL, NULL, &timeout);
        if (-1 == res)
        {
            handle_error("select error");
        }
        else if (0 == res)
        {
            printf("\r\n \033[1;35m[func: %s, line: %d]\033[0m: select time out\n", __FUNCTION__, __LINE__);
        }
        else
        {
            if (FD_ISSET(fd, &readfds))
            {
                res = read(fd, &buff, sizeof(uint64_t));
                if (res != sizeof(uint64_t))
                {
                    handle_error("read error");
                }

                tot_exp += buff;
                print_elapsed_time();
                printf("read: %llu; total=%llu\n",
                        (unsigned long long) buff,
                        (unsigned long long) tot_exp);
            }
         }

    }while(1);


   exit(EXIT_SUCCESS);

}

