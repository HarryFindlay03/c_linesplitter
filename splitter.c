#include "splitter.h"

int g_NUM_SPLIT = 11;
char* g_SPLIT[] = {"et", "nec", "sed", "tamen", "at", "sic", "ut", "cum", "vel", "iam", "ergo"};

int main()
{
    char file_name[255];
    int byte_count;

    printf("==========================\n");
    printf("DARTH YING's LINE SPLITTER\n");
    printf("==========================\n\n\n");
    printf("Enter full path of where file is located: ");
    scanf("%s", file_name);

    printf("\n\n\n");

    WORD* words = get_words(file_name);
    write_to_file(file_name, words);

    printf("FILE SPLIT SUCCESSFULLY! 🕺🕺\n\n\n");

    return 0;
}

WORD* get_words(char* file_name)
{
    FILE* fp;
    WORD* words = NULL;

    int buffer_size = 255;
    char buffer[buffer_size];

    const char delim[2] = " ";
    char* token;

    if((fp = fopen(file_name, "r")) == NULL)
    {
        printf("There has been an error with the file name !\nPLEASE EXIT AND TRY AGAIN!\n\n");
        exit(-1);
    }

    while(fgets(buffer, buffer_size, fp))
    {
        /* get the first token */
        token = strtok(buffer, delim); 

        /* walk through other tokens */
        while(token != NULL)
        {
            // printf("%s\n", token);
            word_append(&words, token);
            token = strtok(NULL, delim);
        }
    }

    fclose(fp);
    return words;
}

void write_to_file(char* file_name, WORD* words)
{
    int i, counter, condition;
    FILE* fp;
    char ext[] = "_SPLIT\0";
    char final_ext[] = ".txt\0";

    /* Changing filename */
    char* ptr = file_name;
    char* ptr_ext;

    while(*ptr != '.')
        ptr++;

    for(ptr_ext = ext; *ptr_ext;)
        *ptr++ = *ptr_ext++;
    
    for(ptr_ext = final_ext; *ptr_ext;)
        *ptr++ = *ptr_ext++; 
    
    /* attempting to open file */
    if((fp = fopen(file_name, "w")) == NULL)
    {
        printf("There has been an error with the file name !\nPLEASE EXIT AND TRY AGAIN!\n\n");
        exit(-1);
    }

    /* main loop */
    counter = 0;
    fputs(words->word, fp);
    while(words->nextWord != NULL)
    {
        words = words->nextWord;
        fputs(words->word, fp);

        condition = 0;
        counter++;

        if(counter == 9 && !condition)
        {
            fputc('\n', fp);
            counter = 0;
            condition = 1;
            continue;
        }

        /* checking word does not have a full stop */
        char* word_ptr;
        for(word_ptr = words->word; *word_ptr; word_ptr++)
        {
            if(condition)
                break;

            if(*word_ptr == '.')
            {
                fputc('\n', fp);
                counter = 0;
                condition = 1;
                break;
            }
        }
                
        /* checking words is not in SPLIT list */
        for(i = 0; i < g_NUM_SPLIT; i++)
        {
            if(condition)
                break;

            if((!(strcmp(words->word, g_SPLIT[i]))) && (counter > 5))
            {
                fputc('\n', fp);
                counter = 0;
                condition = 1;
                break;
            }
        }
    }

    fclose(fp);
    return;
}

void word_append(WORD** head, char* data)
{
    if(*head == NULL)
    {
        if(!(*head = (WORD*)malloc(sizeof(WORD))))
        {
            printf("Memory allocation failed!\n");
            exit(-1);
        }

        if(!((*head)->word = (char*)malloc(sizeof(strlen(data) + 1))))
        {
            printf("Memory allocation failed!");
            exit(-1);
        }
        
        (*head)->nextWord = NULL;
        return;
    }

    WORD* newWord;
    
    if(!(newWord = (WORD*)malloc(sizeof(WORD))))
    {
        printf("Memory allocation failed!\n");
        exit(-1);
    }
    
    if(!(newWord->word = (char*)malloc(sizeof(strlen(data) + 1))))
    {
        printf("Memory allocation failed!");
        exit(-1);
    }
    
    strcpy(newWord->word, data);
    strcat(newWord->word, " ");
    
    WORD* temp = *head;
    while(temp->nextWord != NULL)
        temp = temp->nextWord;
    
    temp->nextWord = newWord;
    newWord->nextWord = NULL;
    
    return;
}

void print_words(WORD* head)
{
    while(head != NULL)
    {
        printf("%s ", head->word);
        head = head->nextWord;
    }
    
    printf("\n");
    return;
}
