/*
 * stdio.h
 */

#ifndef _STDIO_H
#define _STDIO_H

#include <klibc/extern.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

/* This structure doesn't really exist, but it gives us something
   to define FILE * with */
struct _IO_file;
typedef struct _IO_file FILE;

#define stdin  ((FILE *)0)
#define stdout ((FILE *)1)
#define stderr ((FILE *)2)

#ifndef EOF
# define EOF (-1)
#endif

#ifndef BUFSIZ
# define BUFSIZ 4096
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

static __inline__ int fileno(FILE *__f)
{
  /* This should really be intptr_t, but size_t should be the same size */
  return (int)(size_t)__f;
}

static __inline__ FILE * __create_file(int __fd)
{
  return (FILE *)__fd;
}

__extern FILE *fopen(const char *, const char *);

static __inline__ int fclose(FILE *__f)
{
  extern int close(int);
  return close(fileno(__f));
}
static __inline__ int fseek(FILE *__f, off_t __o, int __w)
{
  extern off_t lseek(int, off_t, int);
  return (lseek(fileno(__f), __o, __w) == (off_t)-1) ? -1 : 0;
}
static __inline__ off_t ftell(FILE *__f)
{
  extern off_t lseek(int, off_t, int);
  return lseek(fileno(__f), 0, SEEK_CUR);
}

__extern int fputs(const char *, FILE *);
__extern int puts(const char *);

__extern size_t __fread(void *, size_t, FILE *);
__extern size_t __fwrite(const void *, size_t, FILE *);

#ifndef __NO_FREAD_FWRITE_INLINES
__extern __inline__ size_t
fread(void *__p, size_t __s, size_t __n, FILE *__f)
{
  return __fread(__p, __s*__n, __f)/__s;
}
__extern __inline__ size_t
fwrite(void *__p, size_t __s, size_t __n, FILE *__f)
{
  return __fwrite(__p, __s*__n, __f)/__s;
}
#endif

__extern int printf(const char *, ...);
__extern int vprintf(const char *, va_list);
__extern int fprintf(FILE *, const char *, ...);
__extern int vfprintf(FILE *, const char *, va_list);
__extern int sprintf(char *, const char *, ...);
__extern int vsprintf(char *, const char *, va_list);
__extern int snprintf(char *, size_t n, const char *, ...);
__extern int vsnprintf(char *, size_t n, const char *, va_list);

__extern int sscanf(const char *, const char *, ...);
__extern int vsscanf(const char *, const char *, va_list);

#endif /* _STDIO_H */
