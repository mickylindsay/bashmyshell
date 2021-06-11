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
#include <pwd.h>

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "whoami"
#define VERSION "0.1"
#define AUTHORS "Micky Lindsay"

// v0.1 Uses both unistd.h and pwd.h. :puke:
// Next step remove getpwuid call.

int main(void){
  uid_t id = geteuid();
  printf("%s\n", getpwuid(id)->pw_name);
  return 0;
}
