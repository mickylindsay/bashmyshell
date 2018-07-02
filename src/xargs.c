/*
Executes the command passed as commandline arguments with the data recieved
via stdin/pipe.

TODO:
  Write a better split_line.
  Write a char** append function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

/*
Splits the given line by spaces and places them into args.
arg_size is the number of splits
*/
int split_line(const char* line, char **args, int *arg_size){
  int end = 0;
  int start = 0;
  int length = strlen(line);
  char c;
  *arg_size = 0;
  do{
    c = line[end++];
    if(c == ' ' || end >= length){
      int tmp_len = end - start;
      if(c == ' '){
	    tmp_len--;
      }
      args[*arg_size] = (char *) malloc(sizeof(char) * tmp_len + 1);
      memcpy(args[*arg_size], (line + start), tmp_len);
      args[*arg_size][tmp_len] = '\0';
      start = end;
      (*arg_size)++;
    }
  } while(end < length);
  return 0;
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
    args[num_args] = (char *) calloc(strlen(argv[num_args + pass_args]) + 1, sizeof(char));
    strcpy(args[num_args], argv[num_args + pass_args]);
    num_args--;
  }
  pid_t pid = fork();	 
  if(pid == -1){
  }else if(!pid){
    execvp(argv[1], args);
  }else{
    wait(NULL);
  }
  char **ptr = args;
  while(*ptr)
    free(*(ptr++));
  free(args);
    
  free(buffer);
  free(total);
}
