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
*/

#ifndef _USAGE_H
#define _USAGE_H

#define LICENSE "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/license/gpl.html>.\n" \
  "This is free software: you are free to change and redistriute it.\n" \
  "There is NO WARRANTY, to the extent permitted by law.\n"

#define USAGE(_op)  do {\
  printf("%s: invalid option '%s'\n", PROGRAM_NAME, _op); \
  printf("Try '%s --help' for more information.\n", PROGRAM_NAME); \
  exit(2); \
  } while(0)

void print_help();
void print_version();

#endif
