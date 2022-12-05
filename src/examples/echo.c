#include <stdio.h>
#include <syscall.h>

int
main (int argc, char **argv)
{
  // exec(argv[1]);
    int i,j;
  printf ("\n");

  for (i = 0; i < argc; i++)
    printf ("%s ", argv[i]);
  printf ("\n");

  return EXIT_SUCCESS;
}
