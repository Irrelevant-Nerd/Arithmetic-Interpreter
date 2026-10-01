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

#define INPUT_LENGTH 1000

int main(void)
{
  char* s = malloc(sizeof(char) * INPUT_LENGTH);

  printf("The intepreter is now running ( Enter 'exit' to leave )\n");
  while(true)
  {
    printf(">>> ");
    fgets(s, INPUT_LENGTH, stdin);

    if(strcmp(s, "exit") == 0)
    {
      break;
    }

    int result = interpret_text(s);
    printf("Result: %d\n", result);

    cur_pos = 0;
  }

  free(s);

  return 0;
}
