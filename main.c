#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// MACROS
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
    cur_token.num_value = c - '0'; // converts the digit character into an integer
  }
  else if(isoperator(c))
  {
    cur_token.type = OP;
    cur_token.op_value = s[cur_pos];
  }
  else if(iswhitespace(c))
  {
  }
  else
  {
    printf("Invalid token received at position %d: %c", cur_pos, c);
    exit(-1);
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
  // parsing is the process of expecting chars type
  // if a text follows a correct syntax, its valid, if not then its invalid
  // in order to identify whether it follows a correct syntax or not is through parsing
  if(cur_token.type != type) // if the current type is not the ssame to expected type
  {
    printf("Syntax error: Expected token of type %s, but received type %s at position %d\n", translate(type), translate(cur_token.type), cur_pos);
    exit(-1);
  }
  cur_pos++; // if theres no syntax error, then we can advance
}

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

int interpret_text(char* s)
{
  get_next_token(s);
  parse(INT);
  int left = cur_token.num_value;

  get_next_token(s);
  parse(OP);
  char op = cur_token.op_value;

  get_next_token(s);
  parse(INT);
  int right = cur_token.num_value;

  return get_result(left, op, right);
}

int main(void)
{
  char* s = malloc(sizeof(char) * INPUT_LENGTH); // exactly 1000 bytes

  printf("Interpreter is running... ( enter 'q' or 'clear' to quit )\n");
  while(true)
  {
    printf(">>> ");
    fgets(s, INPUT_LENGTH, stdin);

    if(s[0] == 'q')
    {
      break;
    }


    int result = interpret_text(s);
    printf("Result: %d\n", result);

    cur_pos = 0; // reset the cur_pos after every interpretation
  }
  free(s);

  return 0;
}
