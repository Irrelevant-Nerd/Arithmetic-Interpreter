#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INPUT_LENGTH 1000
#define INT 0
#define OP 1

typedef struct
{
  int type;
  char op_value;
  int num_value;

} Token;

int cur_pos = 0;
Token cur_token;

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

char* translate(int type)
{
  switch(type)
  {
    case 0:
      return "INTEGER";
    case 1:
      return "OPERATOR";
    default:
      return "N/A";
  }
}

void parse(int type)
{
  // series of tokens must follow the correct syntax call syntax analysis
  if(cur_token.type != type) // if the current type is not the same to expected type
  {
    cur_pos--; // decrement the cur_pos to accurately pinpoint where the error happens
    printf("Syntax error: Expected token of type %s, but received type %s at position %d: \n", translate(type), translate(cur_token.type), cur_pos);
    exit(-1);
  }
}

bool isoperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool iswhitespace(char c)
{
  return c == ' ';
}

void get_next_token(char* s)
{
  char c = s[cur_pos];

  while(iswhitespace(c)) // we wont get out of this loop until the current character is not a whitespace anymore
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
    printf("Invalid token received at position %d: %c", cur_pos, c);
    exit(-1);
  }
}

int interpret_text(char* s)
{
  // currently, the valid syntax is: number operator number
  // not: number operator number operator number

  int result = 0;

  get_next_token(s);
  parse(INT);
  int left = cur_token.num_value;

  get_next_token(s);
  parse(OP);
  char op = cur_token.op_value;

  get_next_token(s);
  parse(INT);
  int right = cur_token.num_value;

  result = get_result(left, op, right);

  return result;
}

int main(void)
{
  char* s = malloc(sizeof(char) * INPUT_LENGTH); // allocating exactly 1000 bytes

  printf("Interpreter is running... ( enter 'q' to quit )\n");
  while(true)
  {
    printf(">>> "); // input here
    fgets(s, INPUT_LENGTH, stdin); // fgets receieves our input in string

    if(s[0] == 'q')
    {
      break; // abnormal termination
    }

    int result = interpret_text(s); // our string goes through set of process in interpret_text() function
    printf("Result: %d\n", result);

    cur_pos = 0; // reset the cur_pos after every interpretation
  }
  free(s); // free the memory to avoid memory leak

  return 0;
}
