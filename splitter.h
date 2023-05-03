#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct word_t
{
    char* word;
    struct word_t *nextWord;
} WORD;

WORD* get_words(char*);
void write_to_file(char*, WORD*);

void word_append(WORD**, char*);
void print_words(WORD*);
