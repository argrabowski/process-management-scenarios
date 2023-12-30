#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000
#define exit(i) ((rands[i]%50)+1)

int main()
{
  /*
  Initialize variables for reading the seed and
  getting the child count
  */
  FILE* seed_file;
  char seed_str[MAXCHAR];
  seed_file = fopen("seed.txt", "r");
  if(seed_file == NULL)
  {
    printf("can't open file for reading\n");
  }
  else
  {
    fscanf(seed_file, "%s", seed_str); // scan the seed file
    fclose(seed_file);
  }
  printf("Read Seed Value: %s\n", seed_str);
  int seed = atoi(seed_str);
  printf("Read Seed Value (Integer): %d\n", seed);
  int child_count = rand()%6+10;
  printf("Random Child Count: %d\n", child_count);
  printf("I'm feeling prolific!\n");
  int rands[child_count];
  srand(seed);
  for(int i = 0; i < child_count; i++) // get random numbers
  {
    rands[i] = rand();
  }
  for(int i = 0; i < child_count; i++)
  {
    int childPid = fork();
    if(childPid == 0) // child process
    {
      int wait = (rands[i]%3)+1;
      printf("  [Child, PID: %d]: I am the child and I will wait %d second(s) and exit with code %d.\n", getpid(), wait, exit(i));
      sleep(wait);
      printf("  [Child, PID: %d]: Now exiting...\n", getpid());
      break;
    }
    else if(childPid > 0) // parent process
    {
      printf("[Parent]: I am waiting for PID %d to finish.\n", childPid);
      waitpid(childPid, NULL, 0);
      printf("[Parent]: Child %d has finished with status code %d. Onward!\n", childPid, exit(i));
    }
    else
    {
      perror("fork error\n");
    }
  }
  return 0;
}
