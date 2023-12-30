#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHAR 1000
#define LOCATIONS 5

int main()
{
  /*
  Initialize variables for reading the file, reading
  the seed value, and selecting random numbers
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
    fscanf(seed_file, "%s", seed_str);
    fclose(seed_file);
  }
  printf("Read Seed Value: %s\n", seed_str);
  int seed = atoi(seed_str);
  printf("Read Seed Value (Integer): %d\n", seed);
  printf("It's time to see the world/file system!\n");
  int rands[LOCATIONS];
  srand(seed);
  /*
  For loop for changing the current working directory
  */
  for(int i = 0; i < LOCATIONS; i++)
  {
    rands[i] = rand();
  }
  int selected_rand;
  char* argument_list[] = {"ls", "-alh", NULL};
  int code;
  int status;
  for(int i = 0; i < LOCATIONS; i++)
  {
    selected_rand = rands[i]%6;
    char cwd[MAXCHAR];
    switch(selected_rand)
    {
      case 0:
        printf("Selection #%d: /home [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/home") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      case 1:
        printf("Selection #%d: /proc [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/proc") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      case 2:
        printf("Selection #%d: /proc/sys [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/proc/sys") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      case 3:
        printf("Selection #%d: /usr [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/usr") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      case 4:
        printf("Selection #%d: /usr/bin [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/usr/bin") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      case 5:
        printf("Selection #%d: /bin [SUCCESS]\n", i+1);
        getcwd(cwd, sizeof(cwd));
        printf("Current reported directory: %s\n", cwd);
        if(chdir("/bin") != 0)
        {
          perror("failed to change directories\n");
        }
        break;
      default:
        printf("location out of range\n");
        break;
    }
    int childPid = fork();
    if(childPid == 0) // child process
    {
      printf("  [Child, PID: %d]: Executing 'ls -alh' command...\n", getpid());
      execvp("ls", argument_list);
    }
    else if(childPid > 0) // parent process
    {
      printf("[Parent]: I am waiting for PID %d to finish.\n", childPid);
      waitpid(childPid, &code, 0);
      status = WEXITSTATUS(code);
      printf("[Parent]: Child %d finished with status code %d. Onward!\n", childPid, status);
    }
    else
    {
      perror("fork error\n");
    }
  }
  return 0;
}
