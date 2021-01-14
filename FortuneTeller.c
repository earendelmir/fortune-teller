#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define LEN 300
#define NUM_ANSWERS 18
#define NUM_QSTARTERS 16
#define NUM_QUITTERS 5


void ask(const char *prompt, char *string);
void clear(char *string);
void lower(char *string);
bool validQuestion(const char *question);
bool wantsToQuit(const char *question);
void answer();


int main(void) {
  printf("Welcome, I am The Fortune Teller; I know all about the past, the present and the future.\n");
  printf("I will answer 3 questions from you today.\n");
  printf("If you no longer require my services please kindly tell me to shut up and I will vanish.\n");

  srand(time(NULL));
  char string[LEN];
  unsigned short int count = 0;

  while (count < 3) {
    ask("Ask me anything: ", string);
    if (wantsToQuit(string))
      break;
    if (validQuestion(string)) {
      answer();
      count++;
    }
  }

  printf("I hope you found the answers you were looking for!\n");
  return (EXIT_SUCCESS);
}



void ask(const char *prompt, char *string) {
  clear(string);

  do {
    // prints the prompt (if given) before taking the user input
    printf("\n%s", prompt ? prompt : "\n> ");
    fgets(string, sizeof(char)*LEN, stdin);
  // keeps asking if the string is empty
  } while (string[0] == '\n');

  // removes the last character which is a newline
  string[strlen(string)-1] = '\0';

  lower(string);
}



// clears the string
void clear(char *string) {
  unsigned short int len = strlen(string);
  for (unsigned short int i = 0; i < len; i++)
    string[i] = '\0';
  string = NULL;
}



// turns all the letters of the string to lowercase
void lower(char *string) {
  unsigned short int len = strlen(string);
  for (unsigned short int i = 0; i < len; i++)
    if (string[i] >= 'A' && string[i] <= 'Z')
      string[i] += 32;
}



bool validQuestion(const char *question) {
  // only accepts strings which end with a ? to make sure they are questions and not affirmations
  if (question[strlen(question)-1] != '?') {
    printf("I don't see a \"?\" at the end; are you sure you asked a proper question?\n");
    return false;
  }

  // gets the first word of the sentence
  char firstWord[LEN/10];
  unsigned short int len = strlen(question), i, index = 0;
  for (i = 0; i < len; i++)
    if (question[i] == ' ')
      // breaks the loop if a space is encountered (and a word has already been found)
      if (index > 0)
        break;
      // keeps looking if no valid character has been found yet
      else
        continue;
    else
      firstWord[index++] = question[i];
  firstWord[index] = '\0';

  // if the first word is one of the following then the question is considered valid
  static const char *qStarters[NUM_QSTARTERS] = {"who", "when", "where", "what", "how", "can", "could", "should",\
                                                  "shall", "will", "do", "does", "did", "am", "is", "are"};
  for (i = 0; i < NUM_QSTARTERS; i++)
    if (strcmp(firstWord, qStarters[i]) == 0)
      return true;

  printf("Are you sure you asked a proper question?\n");
  return false;
}



// checks wether the user input can be translated into "quit program"
bool wantsToQuit(const char *question) {
  static const char *quitters[NUM_QUITTERS] = {"shut up", "please shut up", "quit", "exit", "stop"};
  for (unsigned short int i = 0; i < NUM_QUITTERS; i++)
    if (strcmp(question, quitters[i]) == 0)
      return true;
  return false;
}



void answer() {
  // array of possible answers
  static const char *answers[NUM_ANSWERS] = {"You tell me!", "You don't really need to know that.", "Do you really want to know?",\
  "Ask yourself this: \"do I want to know the answer?\"", "Look inside yourself and you will know.", "That is a tricky question...",\
  "This question deserves no answer.", "Everybody knows that!", "You will soon learn the truth.", "Anything might happen.",\
  "It's not up to me to answer such a question.", "Is that something people actually ask?", "You know, I've been asked that many times!",\
  "I believe you already know the answer.", "I'll tell you tomorrow.", "I'll tell you some other time.", "Maybe...", "Uhm..."};

  static unsigned short int index = 0, oldindex = 0;
  // chooses a random index correspondent to the string in the array that will be printed
  // the loop is used to avoid the same answer being picked twice in a row
  while (index == oldindex)
    index = rand() % NUM_ANSWERS;
  oldindex = index;

  printf("%s\n", answers[index]);
}