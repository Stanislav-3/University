#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include <string.h>
#define size 1024

/**
 *С помощью двунаправленного списка определить, является ли строка палиндромом
 *(т.е. одинаково читается справа налево и слева направо).
 *Пробелы и знаки пунктуации – игнорировать.
 */
void addChar(struct ListItem **list, char ch) {
    struct ListItem *head = (struct ListItem*)calloc(1, sizeof(struct ListItem));
    head->ch = ch;
    if(*list) {
        (*list)->prev = head;
    }
    head->prev = NULL;
    head->next = *list;
    *list = head;
}

void createList(struct ListItem **list, char *string) {
    unsigned long i, j;
    i = 0;
    j = strlen(string) - 1;
     while (i < j) {
        while (!((string[i] >= 'a' && string[i] <= 'z') ||
                 (string[i] >= 'A' && string[i] <= 'Z')) && i < j) {
            i++;
        }
        while (!((string[j] >= 'a' && string[j] <= 'z') ||
                 (string[j] >= 'A' && string[j] <= 'Z')) && i < j) {
            j--;
        }
        if (i == j) return;
        addChar(list, string[i]);
        addChar(list, string[j]);
        i++;
        j--;
    }
}

int isPalindrome(struct ListItem *list) {
    if (!list) return 0;
    while (list) {
        if (list->ch != list->next->ch) return 0;
        list = list->next->next;
    }
    return 1;
}

void deleteList(struct ListItem **list) {
    while(*list) {
        struct ListItem *temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

int main(void) {
    char *string = (char*)calloc(sizeof(char), size + 1);
    struct ListItem *list = NULL;
    printf("Program checks whether the english string is a palindrome\n"
           "Enter a string:\n");
    scanf("%[^\n]s", string);
    if (string[size] != 0) {
        printf("Error!\nThe string is too long(it must be <= %d)\n", size);
        return -1;
    }
    createList(&list, string);
    if (isPalindrome(list)) {
        printf("The string is a palindrome!\n");
    } else {
        printf("The string is not a palindrome!\n");
    }
    free(string);
    deleteList(&list);
    return 0;
}
