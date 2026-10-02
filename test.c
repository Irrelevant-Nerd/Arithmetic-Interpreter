#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

void scan(char* buf)
{
  fgets(buf, sizeof(buf), stdin);
  char* p;

  if(!(p=strchr(buf, '\n'))) // if it founds the '\n', do this
  {
    scanf("%*[^\n]"); // clear up to newline
    scanf("%*c");
  }
  else // if not do this
  {
    *p = 0;
  }
}

int main(void)
{
  char buf[BUF_SIZE];
  printf(">>> ");
  scan(buf);
  printf("%s", buf);

  return 0;
}
