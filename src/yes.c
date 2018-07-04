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

Repeatedly outputs provided text or "y" until killed.
TODO: Think of a way to remove the for loop
*/

#include <stdio.h>
#include <string.h>

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "yes"
#define VERSION "0.1"
#define AUTHORS "Brian Lindsay"

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
