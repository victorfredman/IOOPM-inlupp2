#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

/*int ask_question_int(char *question)
{

  int result = 0;
  int conversions = 0;
  do
    {
      printf("%s\n", question);
      conversions = scanf("%d", &result);
      int c;
      do
        {
          c = getchar();
        }
      while (c != '\n' && c != EOF);
      putchar('\n');
    }
  while (conversions < 1);
  return result;
}
*/

static answer_t make_int(char *str)
{
    return (answer_t) { .int_value = atoi(str) }; //Kompilatorn klagade på att vi fick in fel typ i ask question 
                                                  //int och string så behövde lägga till dessa så de returnerar rätt typ
}

static answer_t make_string(char *str)
{
    return (answer_t) { .string_value = strdup(str) };
}

void clear_input_buffer(void)
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
}

int read_string(char *buf, int buf_siz){
    int count = 0;
    int c;

    c = getchar();

    while(c != '\n' && c != EOF && count < (buf_siz - 1)){

      buf[count] = c;

      count++;

      c = getchar();

    }

    buf[count] = '\0';

    if(c != '\n' && c != EOF){
      clear_input_buffer();
    }

    return count;
}

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

bool is_number(char *str)
{
    int length = strlen(str); //Längden av strängen

    if(length == 0){ //Om längden är 0
        return false;
    }

    int start = 0; //Sätt ett startvärde som används senare i loopen

    if(str[0] == '-'){ //Om strängen börjar med ett minustecken

        if(length == 1){ //Om det bara är ett minustecken
            return false;
        }

        start = 1; //Hoppa över minustecknet i loopen
    }

    for(int i = start; i < length; i++){//Loopa igenom alla tecken och kolla om de är inte är en siffra
        if(!isdigit(str[i])){
            return false;
        }
    }
    return true;
}

answer_t ask_question(char *question, check_func *check, convert_func *convert)
{
   int buf_size = 255;
   char buf[buf_size];

   do {
    printf("%s\n", question);
    read_string(buf, buf_size);

   }
   while(check(buf) == false);
   return convert(buf);

}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, make_int);
  return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, make_string).string_value;
}

/*char *ask_question_string(char *question, char *buf, int buf_siz){
    int len = 0;

    do{

        printf("%s\n", question);
        len = read_string(buf, buf_siz);
    }
    while(len == 0);

    return buf;
}*/