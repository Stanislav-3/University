/**
 * Replace words from file in the text from other file
 */
#include <stdio.h>
#include <stdlib.h>
#define size 50

/* Returns 0 if words are equal */
int wrdcmp(char *str1, char *str2) {
    int i = 0;
    char *str1Copy;
    for(; str1[i]; i++);
    str1Copy = (char*)calloc(i + 1, sizeof(char));
    for(i = 0; str1[i] != '\0'; i++) {
        str1Copy[i] = str1[i];
    }
    str1Copy[i] = '\0';
    /* Clear the word */
    i = 0;
    while ((!((str1Copy[i] >= 65) && (str1Copy[i] <= 90)) && !((str1Copy[i] >= 97) && (str1Copy[i] <= 122))) && str1Copy[i] != '\0') {
        for(i = 0; str1Copy[i] != '\0'; i++) {
            str1Copy[i] = str1Copy[i + 1];
        }
        i = 0;
    }
    for (; (((str1Copy[i] >= 65) && (str1Copy[i] <= 90)) || ((str1Copy[i] >= 97) && (str1Copy[i] <= 122))) && str1Copy[i] != '\0'; i++);
    str1Copy[i] = '\0';
    /* Compare words */
    i = 0;
    do {
        if (str1Copy[i] != str2[i]) return 1;
        i++;
    } while (str1Copy[i] != 0 || str2[i] != 0);
    free(str1Copy);
    return 0;
}
int main(void) {
    FILE *ftext = NULL, *fwords = NULL, *fnewtext = NULL;
    char temp;
    char text[size] = {0};
    ftext = fopen("/Users/stanislav/Desktop/c/Лабораторная 4/4_2/4_2/text.txt", "r+");
    fwords = fopen("/Users/stanislav/Desktop/c/Лабораторная 4/4_2/4_2/words.txt","r");
    if (!ftext || !fwords) {
        printf("Files did not open...\n");
    }
    printf("Text:\n");
    while (fscanf(ftext, "%c", &temp) != EOF) {
        printf("%c", temp);
    }
    printf("\n\nChange-words list:\n");
    while (fscanf(fwords, "%c", &temp) != EOF) {
        printf("%c", temp);
    }
    printf("\n\nChanged text:\n");
    /* Cursor to the beginning */
    rewind(ftext);
    /* Scan a word from a text */
    fnewtext = fopen("/Users/stanislav/Desktop/c/Лабораторная 4/4_2/4_2/newtext", "w+");
    if (!fnewtext) {
        printf("File did not open...\n");
    }
    while (fscanf(ftext, "%s", text) != EOF) {
        char word[size] = {0};
        int replay = 0;
        /* Scan a word to replace */
        rewind(fwords);
        while (fscanf(fwords, "%s", word) != EOF) {
            /* if the words are equal */
            if (!wrdcmp(text, word)) {
                int i = 0;
                /* Note down trash before the replacing word (if there is) */
                while ((text[i] != '\0') && (!((text[i] >= 65) && (text[i] <= 90)) &&
                                                         !((text[i] >= 97) && (text[i] <= 122)))) {
                    fprintf(fnewtext, "%c", text[i]);
                    i++;
                }
                /* Note down a new word replacing word */
                fscanf(fwords, "%s", word);
                fprintf(fnewtext, "%s", word);
                /* Note down trash after the replacing word (if there is) */
                for (;(text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122); i++);
                while ((text[i] != '\0')) {
                    fprintf(fnewtext, "%c", text[i]);
                    i++;
                }
                fprintf(fnewtext, "%c", ' ');
                replay = 1;
                break;
            }
            /* If the words are not equal */
            else {
                /* Just move to other word */
                fscanf(fwords, "%s", word);
            }
        }
        /* Executes only if there were no word in the text from the list */
        if (!replay) {
            fprintf(fnewtext, "%s%c", text, ' ');
        }
    }
    /* Output result file */
    rewind(fnewtext);
    while (fscanf(fnewtext, "%c", &temp) != EOF) {
        printf("%c", temp);
    }
    fclose(ftext);
    fclose(fnewtext);
    fclose(fwords);
    printf("\n");
    return 0;
}
