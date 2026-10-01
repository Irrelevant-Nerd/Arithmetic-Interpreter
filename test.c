#include <stdio.h>
#include <string.h>
#include <ctype.h>


// THIS PARSING OF MINE IS NOT CLOSE TO BEING FINISH
// but this is what i got for now

int get_result(int left, char op, int right)
{
  switch(op)
  {
    case '+':
      return left + right;
    case '-':
      return left - right;
    case '*':
      return left * right;
    case '/':
      return left / right;
    default: // this is most likely wont happen, but still i prefer to include default here
      return -1;
  }
}

bool isoperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int main()
{
  char* string = "1+2+4+6";

  int counter = 0;

  char c = string[counter];

  int result = 0;

  int right = 0;
  char cur_op = ' ';
  int left = 0;

  while(c != '\0')
  {
    // 1 + 1
    if(isdigit(c) && cur_op != ' ' && left != 0)
    {
      right = c - '0';
    }

    else if(isdigit(c))
    {
      if(cur_op != ' ')
        left = (c - '0') * (cur_op == '-' ? -1 : 1);
      else
        left = c - '0';
    }

    else if(isoperator(c))
    {
      cur_op = c;
    }

    else
    {
      printf("invalid!\n");
      break;
    }

    result = get_result(left, cur_op, right);

    counter++;
  }
  printf("result: %d", result);

  return 0;
}
