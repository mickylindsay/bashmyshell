#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

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
      if(!strcmp(";", args[*arg_size])){
		free(args[*arg_size]);
		args[*arg_size] = NULL;
      }
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
		buffer[len - 1] = '\0';
		strcat(total, buffer);
		strcat(total, " ");
	}
	printf("%s\n", total);
	char **args = (char **) calloc(64, sizeof(char *));
	int c = 0;
	split_line(total, args, &c);
	
	pid_t pid = fork();	 
	if(pid == -1){
	}else if(!pid){
	  execvp(argv[1], args);
	}else{
		wait(NULL);
	}
}