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

#define WHITE_SPACE " \n\r\f\v"

/*
Returns 1 if the character c is in the string str, 0 otherwise
 */
int char_in(char c, const char *str){
  char *ptr = (char *) str;
  while(*ptr && *(ptr++) != c);
  return *ptr ? 1 : 0;
}

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
    if(char_in(*ptr, WHITE_SPACE)){
      if(!*(ptr + 1)){
	break;
      }
      args[(*size)++] = ++ptr;
      *(ptr - 1) = '\0';
    }
  }
  
  *(ptr) = '\0';
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
  char **ptr = args + c;
  while(ptr >= args){
    *(ptr+argc-1) = *(ptr);
    ptr--;
  }
  ptr = argv + 1;
  while(*ptr)
    *(args++) = *(ptr++);
  args -= (argc-1);
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
