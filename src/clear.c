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

Clears the current terminal and exits
puts declaration instead of header include to reduce executable size
2J is the ANSI escape code for clear screen and return cursor
H is the ANSI escape code to reset cursor to top left
*/

#define PACKAGE_NAME "bashmyshell"
#define PROGRAM_NAME "clear"
#define VERSION "0.1"
#define AUTHORS "Brian Lindsay"

int puts(const char *);
int main(void){
  puts("\x1b[2J");
  puts("\x1b[H");
}
