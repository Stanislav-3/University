/**
 * Variant 28
 * The text in entered. Program swaps the shortest and the longest word in each sentence and
 * counts amount of symbols in the shortest and the longest word in a text.
 */
#include <stdio.h>
#include <stdlib.h>
#define size 1024

void SymbolsCount(char *text) {
    /* Replay == 1 if there are several words of min/max length */
    int minReplay = 1, maxReplay = 1, i = 0, min = size, max = 0;
    while (text[i] != '\0') {
        int count = 0;
        for(; (((text[i] >= 65) && (text[i] <= 90))||
              ((text[i] >= 97) && (text[i] <= 122))); i++, count++);
        /* Set cursor to the begining of a next word */
        i++;
        for(; (!((text[i] >= 65) && (text[i] <= 90)) &&
               !((text[i] >= 97) && (text[i] <= 122))) && text[i] != '\0'; i++);
        if(!count) continue;
        if (count == min) {
            minReplay = 1;
        }
        if (count == max) {
            maxReplay = 1;
        }
        if (count < min) {
            min = count;
            minReplay = 0;
        }
        if (count > max) {
            max = count;
            maxReplay = 0;
        }
    }
    if (min == max) {
        printf("All words are of a length of %d\n", min);
        return;
    }
    if (!minReplay) {
        printf("The shortest word consistrs of %d letters\n", min);
    }
    else {
        printf("There is no the shortest word\n");
    }
    if (!maxReplay) {
        printf("The longest word consistrs of %d letters\n", max);
    }
    else {
        printf("There is no the longest word\n");
    }
}

void Swap(char *text, int sBegin, int sEnd) {
    /* min and max - amount of letters in the shortest and the longest word */
    /* Replay == 1 if there are several words of min/max length */
    int min = size, max = 0, replay = 1;
    /* minp and maxp pointer to the shortest and longest word */
    char *minp = NULL, *maxp = NULL;
    while(sBegin <= sEnd) {
        int count = 0;
        for(; ((text[sBegin] >= 65) && (text[sBegin] <= 90))||
              ((text[sBegin] >= 97) && (text[sBegin] <= 122)); sBegin++, count++);
        if(count) {
            if (count == min) {
                replay = 1;
            }
            if (count == max) {
                replay = 1;
            }
            if (count < min) {
                min = count;
                replay = 0;
                minp = &text[sBegin - count];
            }
            if (count > max) {
                max = count;
                replay = 0;
                maxp = &text[sBegin - count];
            }
        }
        /* Set cursor to the begining of a next word */
        sBegin++;
        for(; (!((text[sBegin] >= 65) && (text[sBegin] <= 90)) &&
               !((text[sBegin] >= 97) && (text[sBegin] <= 122))) && sBegin <= sEnd; sBegin++);
        
    }
    /* Swap words */
    if (!replay && max != min) {
        int i, delta = max - min;
        /* Memorize the shortest word */
        char *lnword = (char*)calloc(max + 1, sizeof(char));
        for (i = 0; i < max; i++) {
            lnword[i] = maxp[i];
        }
        if (minp < maxp) {
            /* Longest replace with shortest */
            for(i = 0; i < min; i++) {
                maxp[i + delta] = minp[i];
            }
            /* Shift */
            for(i = 0; (maxp - 1 - i) != (minp + min - 1); i++) {
                maxp[delta - 1 - i] = maxp[- 1 - i];
            }
            /* Shortest replace with longest */
            for(i = 0; i < max; i++) {
                minp[i] = lnword[i];
            }
        }
        else {
            /* Longest replace with shortest */
            for(i = 0; i < min; i++) {
                maxp[i] = minp[i];
            }
            /* Shift */
            for(i = 0; (maxp + i + min) != (minp - delta); i++) {
                maxp[min + i] = maxp[i + delta + min];
            }
            /* Shortest replace with longest */
            for(i = 0; i < max; i++) {
                minp[i - delta] = lnword[i];
            }
        }
        free(lnword);
    }
}

void Input(char *text) {
    int i;
    char ch;
    for (i = 0; i < size; i++) {
        text[i] = 0;
    }
    i = 0;
    printf("Enter a text (<%d symbols)\n", size);
    while ((ch = getchar()) != '\n') {
        text[i++] = ch;
    }
    text[i] = '\0';
    text[size - 1] = '\0';
    
}
int main(void) {
    char text[size];
    int sBegin = 0, sEnd = 0;
    Input(text);
    do {
        sBegin = sEnd;
        for (; ((text[sEnd] != '.') && (text[sEnd] != '?') && (text[sEnd] != '!')) && text[sEnd] != '\0'; sEnd++);
        /* Swap the shortest and the longest word in a sentence */
        Swap(text, sBegin, sEnd);
        /* Set cursor to the begining of a next sentence */
        for(; (!((text[sEnd] >= 65) && (text[sEnd] <= 90)) &&
               !((text[sEnd] >= 97) && (text[sEnd] <= 122))) && text[sEnd] != '\0'; sEnd++);
    } while(sBegin < sEnd);
    printf("%s\n", text);
    /* Prints an amount of symbols in the shortest and the longest word in a text */
    SymbolsCount(text);
    return 0;
}
