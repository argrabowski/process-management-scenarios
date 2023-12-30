#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000

int main(int argc, char *argv[])
{
  /*
  initialize variables for reading the file, selecting
  random numbers, and reading command line arguments
  */
  FILE* seed_file;
  char seed_str[MAXCHAR];
  char* argument_list_0[] = {"last", "-d", "--fulltimes"};
  char* argument_list_1[] = {"id", "-u", NULL};
  int selection;
  if(argc == 2) // one argument
  {
    selection = atoi(argv[1]);
  }
  else if(argc > 2) // more than one argument
  {
    printf("too many arguments\n");
  }
  else // no arguments
  {
    printf("one argument expected\n");
  }
  /*
  switch case to chose the seed for each
  of the four slugs
  */
  switch(selection)
  {
    case 1:
      seed_file = fopen("seed_slug_1.txt", "r");
      break;
    case 2:
      seed_file = fopen("seed_slug_2.txt", "r");
      break;
    case 3:
      seed_file = fopen("seed_slug_3.txt", "r");
      break;
    case 4:
      seed_file = fopen("seed_slug_4.txt", "r");
      break;
    default:
      printf("argument must be between 1 and 4\n");
      break;
  }
  if(seed_file == NULL)
  {
    printf("can't open file for reading\n");
  }
  else
  {
    fscanf(seed_file, "%s", seed_str);
    fclose(seed_file);
  }
  /*
  scann the file, print the delay time and coin flip,
  use the sleep command
  */
  printf("[Slug PID: %d] Read Seed Value: %s\n", getpid(), seed_str);
  int seed = atoi(seed_str);
  printf("[Slug PID: %d] Read Seed Value (Integer): %d\n", getpid(), seed);
  srand(seed);
  int wait = rand()%4+1;
  int coin = rand()%2;
  printf("[Slug PID: %d] Delay time is %d seconds. Coin flip: %d\n", getpid(), wait, coin);
  printf("[Slug PID: %d] I'll get the job done. Eventually...\n", getpid());
  sleep(wait); // sleep for the time of wait
  if(coin == 0)
  {
    printf("[Slug PID: %d] Break time is over! I am running the 'last -d --fulltimes' command.\n", getpid());
    execvp("last", argument_list_0);
  }
  else
  {
    printf("[Slug PID: %d] Break time is over! I am running the 'id -u' command.\n", getpid());
    execvp("id", argument_list_1);
  }
  return 0;
}
