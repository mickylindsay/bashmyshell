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

Prints the effective user
*/

#include <stdio.h>
#include <unistd.h>

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "whoami"
#define VERSION "0.2"
#define AUTHORS "Micky Lindsay"

// v0.2 No longer uses geteuid or getpwuid.
// Instead reads /etc/passwd file, and make SYS call for euid
// Efficient? No.
// And more, much more than this I did it, my way

int main(void){
  char buffer[256];
  char id[32];

  sprintf(id, "%ld", syscall(107));

  FILE *passwd = fopen("/etc/passwd", "r");
  while (fgets(buffer, sizeof(buffer), passwd)){
    char *i = buffer;
    char *j = id;
    int num_colon = 0;
    // Step through passwd file line until past second colon ':'
    while (num_colon < 2)
      if ((i++)[0] == ':') num_colon++;

    // Walk through effective uid and uid in passwd file
    while (j[0] == i[0]) {
      j++;
      i++;
    }

    // If passwd file has reach a colon AND uid string is null byte,
    // found effective user line
    if (j[0] == 0 && i[0] == ':') break;
  }

  // Print current user character by character,
  // because I cant be fucked writting a clever substring
  char *c = buffer;
  while (c[0] != ':') {
    printf("%c", (c++)[0]);
  }
  printf("\n");
  // puts(getpwuid(id)->pw_name);
  return 0;
}

// v0.1 Uses both unistd.h and pwd.h. :puke:
// Next step remove getpwuid call.

// int main(void){
//   uid_t id = geteuid();
//   printf("%s\n", getpwuid(id)->pw_name);
//   return 0;
// }
