/*
yes
Repeatedly outputs provided text or "y" until killed.

AUTHOR: Micky Lindsay
CREATED: 7/2/2018

TODO: Think of a way to remove the for loop
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  int i;
  char *buf = "y";
  //Kind of a hack. Since argv is continuous,
  //change the null termination to a space.
  for (i = 1; i < argc - 1; i++){
    argv[i][strlen(argv[i])] = ' ';
  }
  
  if(i > 1) buf = *(argv+1);
  while(puts(buf) > 0);
  return 1;
}
