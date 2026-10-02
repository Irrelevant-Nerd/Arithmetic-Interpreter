#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
  INVALID = -1,
  INT = 0,
  OP = 1,
} Types;

typedef struct
{
  int type;
  char op_value;
  int num_value;

} Token;

Token cur_token;

int cur_pos = 0;

int calculate(int x, char op, int y)
{
  switch(op)
  {
    case '+':
      return x + y;
    case '-':
      return x - y;
    default:
      return -1;
  }
}

char* translate(int type)
{
  switch(type)
  {
    case 0:
      return "INTEGER";
    case 1:
      return "OPERATOR";
    default:
      return "INVALID";
  }
}

bool parse(int type)
{
  if(cur_token.type != type)
  {
    printf("SyntaxError: Expected token of type %s, but received type %s at position %d:\n", translate(type), translate(cur_token.type), cur_pos);
    return false;
  }

  return true;
}

bool isoperator(char c)
{
  return c == '+' || c == '-';
}

bool iswhitespace(char c)
{
  return c == ' ';
}

void get_next_token(char* s)
{
  char c = s[cur_pos];

  while(iswhitespace(c))
  {
    cur_pos ++;
    c = s[cur_pos];
  }

  if(isdigit(c))
  {
    cur_token.type = INT;
    cur_token.num_value = 0;

    while(isdigit(c))
    {
      cur_token.num_value *= 10;
      cur_token.num_value += s[cur_pos] - '0';

      cur_pos++;
      c = s[cur_pos];
    }
  }

  else if(isoperator(c))
  {
    cur_token.type = OP;
    cur_token.op_value = s[cur_pos];
    cur_pos++;
  }
  else
  {
    cur_pos--;
    printf("Invalid token received at position %d: %c\n", cur_pos, c);
    cur_token.type = INVALID;
  }
}

int interpret_text(char* s)
{
  int result = 0;

  get_next_token(s);

  if(!parse(INT))
    return -1;

  result = cur_token.num_value;

  while(cur_pos < strlen(s)-1)
  {
    get_next_token(s);

    if(!parse(OP))
      break;

    char op = cur_token.op_value;

    get_next_token(s);

    if(!parse(INT))
      break;

    int operand = cur_token.num_value;

    result = calculate(result, op, operand);
  }
  return result;
}

#define BUF_SIZE 256

void scan(char* buf)
{
  fgets(buf, sizeof(buf), stdin);
  char *p;

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
  char string[BUF_SIZE]; // we store our string here

  printf("The intepreter is now running ( Enter 'q' to quit )\n");
  while(true)
  {
    printf(">>> ");
    scan(string);

    if(strcmp(string, "q") == 0)
    {
      break;
    }
    printf("%d\n", interpret_text(string));
    cur_pos = 0; // reset the position
  }

  return 0;
}
