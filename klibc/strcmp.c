/*
 * strcmp.c
 */

#include <string.h>

int strcmp(const char *s1, const char *s2)
{
  const unsigned char *c1 = s1, *c2 = s2;
  unsigned char ch;
  int d = 0;

  while ( 1 ) {
    d = (int)*c2++ - (int)(ch = *c1++);
    if ( d || !ch )
      break;
  }

  return d;
}
