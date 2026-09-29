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

void get_next_token(char* s)
{
  char c = s[cur_pos];
  if(isdigit(c))
  {
    cur_token.type = INT;
    cur_token.num_value = c - '0'; // converts the digit character into an integer
  }
  else if(c == '+' || c == '-' || c == '*' || c == '/')
  {
    cur_token.type = OP;
    cur_token.op_value = s[cur_pos];
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

void interpret_text(char* s)
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
}

int main(void)
{
  char* s = malloc(sizeof(char) * INPUT_LENGTH); // exactly 1000 bytes

  printf("Interpreter is running... ( enter 'q' to quit )\n");
  printf("0 - INT, 1 - OPERATOR\n");
  while(true)
  {
    printf(">>> ");
    fgets(s, INPUT_LENGTH, stdin);

    if(s[0] == 'q')
      break;

    interpret_text(s);
  }
  free(s);

  return 0;
}
