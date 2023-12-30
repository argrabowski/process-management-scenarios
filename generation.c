#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000

int main()
{
  /*
  Initialize variables for reading the seed and
  getting the decendant count
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
  int lifespan_count = rand()%4+7;
  printf("Random Descendant Count: %d\n", lifespan_count);
  printf("Time to meet the kids/grandkids/great grandkids/...\n");
  int childPid = fork();
  while(lifespan_count >= 0)
  {
    if(childPid == 0) // child process
    {
      lifespan_count--;
      printf("  [Child, PID: %d]: I was called with descendant count=%d. I'll have %d descendant(s).\n", getpid(), lifespan_count+1, lifespan_count);
      if(lifespan_count <= 0)
      {
        exit(0);
      }
      childPid = fork();
    }
    else if(childPid > 0) // parent process
    {
      printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n", getpid(), childPid);
      waitpid(childPid, NULL, 0);
      printf("[Parent, PID: %d]: Child %d has finished with status code %d. It's now my turn to exit.\n", getpid(), childPid, lifespan_count-1);
      break;
    }
    else
    {
      perror("fork error\n");
    }
  }
  return 0;
}
