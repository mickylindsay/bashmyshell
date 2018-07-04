/*
wc
Word count programming for the number of lines, bytes, characters, words, and the max line length.
 */

//TODO: Total when multiple files input
//TODO: usage and help printing
//TODO: Comment this stuff

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define LINE 0x01
#define WORD 0x02
#define CHAR 0x04
#define BYTE 0x08
#define MAXL 0x10
#define FIO  0x20
#define STDI 0x80

#define IS_SET(_x, _b) ((_x) & (_b))
#define MAX(_x, _y)    ((_x) > (_y)) ? (_x) : (_y)

char cur_mode;

struct counter{
  int line;
  int word;
  int c;
  int byte;
  int max;
  char *name;
  FILE *stream;
};

static void usage_error(const char *op){
  printf("wc: invalid option '%s'\n", op);
  printf("Try 'wc --help' for more information.\n");
  exit(2);
}

static void print_help(){
  
}

static void print_version(){

}

static void print_counter(struct counter * const c){
  int i;
  int *ptr = &(c->line);
  for(i = 0; i < 5; i++){
    if(IS_SET(cur_mode, (0x01 << i)))
      printf("\t%d", *(ptr+i));
  }
  if(c->name)
    printf("\t%s\n", c->name);
}

static int count_words(const char * c){
  int count = 0;
  char *ptr = (char *) c;
  while(*(ptr++))
    if(*ptr == ' ' && *(ptr - 1) != ' ')
      count++;
  if(ptr > c)
    count++;
  return count;
  
}

static void wc_counter(const void *c){
  struct counter *counter = (struct counter *) c;
  char *buffer;
  buffer = calloc(1024, sizeof(char));
  size_t bufsize = 1024;
  int len;
  while((len = getline(&buffer, &bufsize, counter->stream)) > 0){
    //TODO: characters vs byte
    counter->c += len;
    counter->byte += len;
    counter->line++;
    counter->max = MAX(counter->max, len);
    counter->word += count_words(buffer);
  }
  print_counter(counter);
}

static void free_stream(void *data){
  struct counter *counter = (struct counter *) data;
  fclose(counter->stream);
  free(counter);
}

int main(int argc, char **argv){
  list_t *list;
  int i;
  cur_mode = STDI | LINE | WORD | CHAR;
	list_create(&list, &free_stream);
  for(i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      char c = argv[i][1];
      cur_mode = STDI;
      switch(c){
      case 'c':
	cur_mode |= BYTE;
	break;
      case 'm':
	cur_mode |= CHAR;
	break;
      case 'l':
	cur_mode |= LINE;
	break;
      case 'L':
	cur_mode |= MAXL;
	break;
      case 'w':
	cur_mode |= WORD;
	break;
      case '-':	
	if(!strcmp("--bytes", argv[i])){
	  cur_mode |= BYTE;
	}else if(!strcmp("--chars", argv[i])){
	  cur_mode |= CHAR;
	}else if(!strcmp("--lines", argv[i])){
	  cur_mode |= LINE;
	}else if(!strcmp("--files", argv[i])){
	  cur_mode |= FIO;
	}else if(!strcmp("--max-line-length", argv[i])){
	  cur_mode |= MAXL;
	}else if(!strcmp("--words", argv[i])){
	  cur_mode |= WORD;
	}else if(!strcmp("--help", argv[i])){
	  print_help();
	}else if(!strcmp("--version", argv[i])){
	  print_version();
	}else{
	  usage_error(argv[i]);
	}
	break;
      default:
	usage_error(argv[i]);
      }
    }else{
      FILE *in = fopen(argv[i], "r");
      if(in){
	if(IS_SET(cur_mode,  STDI)){
	  cur_mode &= ~STDI;
	}
	struct counter *new_counter = (struct counter *) calloc(1, sizeof(struct counter));
	new_counter->stream = in;
	new_counter->name = argv[i];
	list_append(list, new_counter);
      }
    }
  }
  if(!list_size(list) && IS_SET(cur_mode, STDI)){
    struct counter *new_counter = (struct counter *) calloc(1, sizeof(struct counter));
    new_counter->stream = stdin;
    list_append(list, new_counter);
  }
  list_foreach(list, &wc_counter);
  list_destroy(list);
  return 1;
}
