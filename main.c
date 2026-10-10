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
    case -1: return "INVALID";
    case 0: return "INTEGER";
    case 1: return "OPERATOR";
    default: return "NONE";
  }
}

bool isoperator(char c)
{
  return c == '+' || c == '-';
}

bool iswhitespace(char c)
{
  return c == ' ' || c == '\t'; // tab is treated as whitespace
}

bool is_quit(const char* s)
{
  // ignore any whitespace
  while(iswhitespace(*s))
  {
    s++;
  }

  if(*s == 'q' || *s == 'Q')
  {
    s++;
  }

  // if char does not equal to any of these, return false
  else
  {
    return false;
  }

  while(iswhitespace(*s))
  {
    s++;
  }

  // if end of the string, return true
  return *s == '\0';
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

void get_next_token(char* s)
{
  char c = s[cur_pos];

  while(iswhitespace(c))
  {
    cur_pos++;
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
    printf("TokenError: Invalid token received at position %d: %c\n", cur_pos, c);
    cur_token.type = INVALID;
    cur_pos++;
  }
}

int interpret_text(char* s)
{
  int result = 0;

  get_next_token(s);

  if(!parse(INT)) // if the first character is not INT, we return -1 immediately;
  {
    result = -1;
    return result;
  }
  result = cur_token.num_value;

  while(true)
  {
    while(iswhitespace(s[cur_pos]))
    {
      cur_pos++;
    }
    if(s[cur_pos] == '\0') // loops stops when we reach the null terminator '\0'
    {
      break;
    }
    get_next_token(s);

    if(!parse(OP))
    {
      result = -1;
      break;
    }

    char op = cur_token.op_value;

    get_next_token(s);

    if(!parse(INT))
    {
      result = -1;
      break;
    }
    int operand = cur_token.num_value;

    result = calculate(result, op, operand);
  }

  return result;
}

#define BUF_SIZE 256

char* scan(char *buf, size_t capacity)
{
  if (fgets(buf, capacity, stdin) == NULL)
    return NULL;

  char *p = strchr(buf, '\n');

  if (p)
  {
    *p = '\0';
  }
  else
  {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
  }
  return buf;
}

int main(void)
{
  char buf[BUF_SIZE]; // we store our text here

  printf("The intepreter is now running ( Enter 'q' or 'Q' to quit )\n");
  while(true)
  {
    printf(">>> ");
    char* text = scan(buf, sizeof(buf));

    if(text == NULL)
    {
      break;
    }

    if(is_quit(text))
    {
      break;
    }

    printf("%d\n", interpret_text(text));
    cur_pos = 0; // reset the position
  }

  return 0;
}
