/*
   Copyright (C) 2018 Brian Lindsay

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.

Word count programming for the number of lines, bytes, characters, words, 
and the max line length.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "usage.h"

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "wc"
#define VERSION "0.1"
#define AUTHORS "Brian Lindsay"

#define LINE 0x01
#define WORD 0x02
#define CHAR 0x04
#define BYTE 0x08
#define MAXL 0x10
#define FIO  0x20
#define STDI 0x80

#define IS_SET(_x, _b) ((_x) & (_b))
#define MAX(_x, _y)    ((_x) > (_y)) ? (_x) : (_y)

struct counter{
  int line;
  int word;
  int c;
  int byte;
  int max;
  char *name;
  FILE *stream;
};

char cur_mode;
struct counter *total;

void print_help(){
  printf("Usage: %s [OPTION]... [FILE]...\n", PROGRAM_NAME);
  printf("Counts and outputs the number of lines, words, bytes for the provided FILE paths or stdin.\n\n");
  printf("When no files are provided stdin is read from.\n\n");
  printf("These option will change which values are printed. Print order is always: line, word, character, byte, max line length.\n");
  printf("  -c,\t--bytes  \tprint the byte counts\n");
  printf("  -m,\t--chars  \tprint the character counts\n");
  printf("  -l,\t--lines  \tprint the newline counts\n");
  printf("  -L,\t--max-len\tprint the max line length\n");
  printf("  -w,\t--words  \tprint the words counts\n");
  printf("     \t--help   \tprint this message\n");
  printf("     \t--version\tprint version info\n");
  printf("\nbashmyshell <http://github.com/demisardonic/bashmyshell/>\n");
  exit(1);
}

void print_version(){
  printf("%s (%s) %s\n", PROGRAM_NAME, PACKAGE_NAME, VERSION);
  printf("%s\n", LICENSE);
  printf("Written by %s\n", AUTHORS);
  exit(1);
}

static void print_counter(struct counter *c){
  int i;
  int *ptr = &(c->line);
  for(i = 0; i < 5; i++){
    if(IS_SET(cur_mode, (0x01 << i)))
      printf("\t%d", *(ptr+i));
  }
  if(c->name)
    printf("\t%s\n", c->name);
}

//Counts the number of words while skipping repeated spaces
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

//Iterates though the stream and counts the characters, lines, words, etc.
//if there are multiple streams, keep track of the total
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
  if(total){
    total->c += counter->c;
    total->byte += counter->byte;
    total->line += counter->line;
    total->max = counter->max;
    total->word += counter->word;
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

  //Handle command line arguments
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
	  USAGE(argv[i]);
	}
	break;
      default:
	USAGE(argv[i]);
      }
    }else{
      //Attempt to read the given file and add it to a list of FILE
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
    //Use stdin
    struct counter *new_counter = (struct counter *) calloc(1, sizeof(struct counter));
    new_counter->stream = stdin;
    list_append(list, new_counter);
  }else if(list_size(list) > 1){
    //If there are multiple files must track the total
    total = (struct counter *) calloc(1, sizeof(struct counter));
    total->name = "TOTAL";
  }
  //Iterate through the list and perform the count
  list_foreach(list, &wc_counter);
  if(total){
    //Print the total count if it exists
    print_counter(total);
  }
  //free the dynamic allocated pointers
  list_destroy(list);
  free(total);
  
  return 1;
}
