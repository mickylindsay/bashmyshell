
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

Integer to null terminated char buffer. If negative value and base ten the
buffer will include minus '-'. Other bases are assumed to be unisigned.
`base` between 2 and 36.
`buf` assumed to be large enough. NOT SAFE. FUCK AROUND AND FIND OUT.
 */

 #include "itoa.h"
 #include <stdlib.h>

char *itoa( int value, char *buf, int base) {
  if (base < 2 || base > 36) exit(1);
  if (!buf) exit(2);

  char *i = buf;
  int temp = value < 0 ? -value : value;

  while (temp > 0) {
    int c = temp % base;
    *(i++) = c < 10 ? c + 48 : c + 87;
    temp /= base;
  }

  if (base == 10 && value < 0) *(i++) = '-';
  *i = 0;

  i--;
  char c;
  char *ptr = buf;
  while (ptr <= i) {
    c = *ptr;
    *(ptr++) = *i;
    *(i--) = c;
  }
  return buf;
}
