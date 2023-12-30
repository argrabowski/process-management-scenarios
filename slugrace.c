#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAXCHAR 1000
#define CHILDREN 4

int main()
{
  /*
  initialize variables for slug commandline arguments,
  clock, pids, finished processes, and status
  */
  int result;
  struct timespec tp;
  clockid_t clk_id;
  clk_id = CLOCK_REALTIME;
  char* slug_1_args[] = {"slug", "1", NULL};
  char* slug_2_args[] = {"slug", "2", NULL};
  char* slug_3_args[] = {"slug", "3", NULL};
  char* slug_4_args[] = {"slug", "4", NULL};
  char* racing_args[] = {"pgrep", "-P", NULL};
  int finished = 0;
  int finishPid;
  int status;
  int pids[CHILDREN];
  /*
  spawn the children using a loop with a counter, providing a
  different parameter to each spawned child
  */
  for(int i = 0; i < CHILDREN; i++)
  {
    int childPid = fork(); // fork() system call
    if(childPid == 0) // if process is child
    {
      printf("  [Child, PID: %d]: Executing './slug %d' command...\n", getpid(), i+1);
      /*
      switch case for each slug which have different
      seeds for different random variables
      */
      switch(i+1)
      {
        case 1:
          execvp("./slug", slug_1_args);
          break;
        case 2:
          execvp("./slug", slug_2_args);
          break;
        case 3:
          execvp("./slug", slug_3_args);
          break;
        case 4:
          execvp("./slug", slug_4_args);
          break;
        default:
          printf("argument must be between 1 and 4\n");
          break;
      }
      break;
    }
    else if(childPid > 0) // if process is parent
    {
      printf("[Parent]: I forked off child %d.\n", childPid);
      pids[i] = childPid;
      if(i == CHILDREN-1)
      {
        /*
        parent loops through, checking to see if any child has finished,
        and if not, waiting 0.25 seconds before printing out the current
        racing slugs
        */
        while(finished < CHILDREN)
        {
          printf("[Parent]: The race is ongoing. The following children are still racing:");
          for(int i = 0; i < CHILDREN; i++)
          {
            if(!WIFEXITED(status)) // if child process has exited
            {
              printf(" %d\n", pids[i]);
            }
          }
          printf("\n");
          if(waitpid(-1, &status, WNOHANG) == 0) // if child process has finished
          {
            usleep(250000); // sleep for 0.25 seconds
          }
          else
          {
            result = clock_gettime(clk_id, &tp); // get the time for this process
            printf("[Parent]: Child %d has crossed the finish line! It took %ld seconds.\n", childPid, tp.tv_sec);
            finished++;
          }
        }
      }
      result = clock_gettime(clk_id, &tp); // get the total time of the race
      printf("[Parent]: The race is over! It took %ld seconds.\n", tp.tv_sec);
    }
    else
    {
      perror("fork error\n");
    }
  }
  return 0;
}
