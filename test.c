#include <stdio.h>

void interpret_text(char* string)
{
  char c;

  while((c = *string) != '\0')
  {
    printf("%c\n", c);
    string++; 
  }
}

int main()
{

  return 0;
}
