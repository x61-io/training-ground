
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define _max_size 25 
#define _KB 1024

int parse_args(char* v)
{
  char* s1, *token;
  char* saveptr;
  token = strtok_r(v, " ", &saveptr);
  v[strcspn(v,"\n")] = '\0';
  while (token != NULL) 
  {
    if (strlen(token) > _max_size)
    {
      fprintf(stderr, "ERR: string > _max_size. Errno %d\n", errno);
      return EMSGSIZE;
    }
    if (strlen(saveptr) == 0) 
    { 
      printf("Item: %s Character count: %zu\n", token, strlen(token));
    } else 
    { 
      printf("Item: %s Character count: %zu \n\tRemaining: %s \n", 
          token, strlen(token), saveptr);
    }
    token = strtok_r(NULL, " ", &saveptr);
  }
  return 0;
}

int
main(void)
{
  int res = 0;
  char* buffer = (char*)malloc(sizeof(char) * _KB);
  if (buffer == NULL)
  {
    fprintf(stderr, "ERROR: %d\n", errno);
    exit(errno);
  }
  printf("input: ");
  fgets(buffer, _KB, stdin);
  printf("output: %s\n", buffer);
  if (parse_args(buffer) != 0) { res = errno; }
  free(buffer);
  return res;
}
