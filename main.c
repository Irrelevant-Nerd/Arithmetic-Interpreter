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

void print_current_token(char *s)
{
  printf("CHAR: %c\n", s[cur_pos]);
  printf("TYPE: %d\n", cur_token.type);
}

void get_next_token(char* s)
{
  char c = s[cur_pos];
  if(isdigit(c))
  {
    cur_token.type = INT;
    cur_token.num_value = c - '0'; // converts the digit character into an integer

    print_current_token(s);
    printf("VALUE: %d\n\n", cur_token.num_value);

  }
  else if(c == '+' || c == '-' || c == '*' || c == '/')
  {
    cur_token.type = OP;
    cur_token.op_value = s[cur_pos];

    print_current_token(s);
    printf("VALUE: %c\n\n", cur_token.op_value);
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
  }
}

void parse(int type)
{
  if(cur_token.type)
  {
    printf("Syntax error: Expected token of type %s, but received type %s\n", translate(type), translate(cur_token.type));
    exit(-1);
  }
}

void interpret_text(char* s)
{
  while(s[cur_pos] != '\0') // if it hits '\0', stop the loop
  {
    get_next_token(s);
    cur_pos++;
  }
}

int main(void)
{
  char* s = malloc(sizeof(char) * INPUT_LENGTH); // exactly 1000 bytes

  printf("Interpreter is running... ( CTRL+C to exit )\n");
  printf("0 - INT, 1 - OPERATOR\n");
  while(true)
  {
    printf(">>> ");
    fgets(s, INPUT_LENGTH, stdin);
    interpret_text(s);
  }
  free(s);

  return 0;
}
