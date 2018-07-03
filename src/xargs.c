/*
xargs
Executes the provided command and passes the input stream as the commandline arguments.

AUTHOR: Micky Lindsay
CREATED: 7/2/2018
VERSION: 0.1

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

/*
Returns an array of pointers to space seperated strings
Originally borrowed from a function I wrote in university,
but it was garbage so I made a version im actually proud of
check the git history to see
*/
void split_line(char *line, char **args, int *size){
  char *ptr = (char *)line;
  *size = 0;
  args[(*size)++] = ptr;
  while(*(++ptr)){
    if((*ptr) == ' '){
      args[(*size)++] = ++ptr;
      *(ptr - 1) = '\0';
    }
  }
  *(ptr - 1) = '\0';
  args[*size] = NULL;
}

int main(int argc, char **argv){
  char *total;
  total = calloc(1024, sizeof(char));
  
  char *buffer;
  buffer = calloc(1024, sizeof(char));
  size_t bufsize = 1024;
  int len;
  while((len = getline(&buffer, &bufsize, stdin)) > 0){
    strcat(total, buffer);
  }
  char **args = (char **) calloc(64, sizeof(char *));
  int c = 0;
  split_line(total, args, &c);
  int num_args = c + argc - 1;
  int pass_args = argc - 1;
  while(num_args >= pass_args){
    args[num_args] = args[num_args - pass_args];
    num_args--;
  }
  
  while(num_args >= 0){
    args[num_args] = argv[num_args + pass_args];
    num_args--;
  }
  pid_t pid = fork();	 
  if(pid == -1){
  }else if(!pid){
    execvp(argv[1], args);
  }else{
    wait(NULL);
  }
  free(args);
    
  free(buffer);
  free(total);
}
