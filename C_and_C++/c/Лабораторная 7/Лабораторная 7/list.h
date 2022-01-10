#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100

typedef struct listItem {
    struct listItem *prev, *next;
    char *question, *answers[4];
    int correctAnswer;
} archive;

void addToArchive(archive **head, char *question, char *answers[], int correctAnswer) {
    int i;
    archive *newHead = (archive*)malloc(sizeof(archive));
    newHead->question = question;
    for (i = 0; i < 4; i++) {
        newHead->answers[i] = answers[i];
    }
    newHead->correctAnswer = correctAnswer;
    if (*head) {
        (*head)->prev = newHead;
    }
    newHead->prev = NULL;
    newHead->next = *head;
    *head = newHead;
}

void deleteAll(archive **head) {
    int i;
    while (*head) {
        archive *temp = *head;
        (*head) = (*head)->next;
        free(temp->question);
        for (i = 0; i < 4; i++) {
            free(temp->answers[i]);
        }
        free(temp);
    }
}

archive* deleteItem(archive **item) {
    archive *temp;
    archive *head;
    int j;
    if (!(*item)) return NULL;
    temp = *item;
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev) {
        head = temp->prev;
        temp->prev->next = temp->next;
        /* Search a head */
        while (head->prev) {
            head = head->prev;
        }
    }
    else {
        /* delete a head */
        *item = temp->next;
        head = *item;
    }
    free(temp->question);
    for (j = 0; j < 4; j++) {
        free(temp->answers[j]);
    }
    free(temp);
    return head;
}

void viewItem(archive *item, int number) {
    int j;
    printf("? ? ? ? ? ? ? ? ?\n"
       "?  Question №%d\t?\n"
       "? ? ? ? ? ? ? ? ?\n%s\n", number + 1, item->question);
    for (j = 0; j < 4; j++) {
        printf("%d) %s\n", j + 1, item->answers[j]);
    }
    printf("Correct answer: %d\n", item->correctAnswer);
}

void viewAll(archive *head) {
    int i = 0;
    while (head) {
        viewItem(head, i);
        i++;
        printf("\n");
        head = head->next;
    }
}

archive* searchItem(archive *head, int number) {
    int counter = 0;
    while (head && counter != number) {
        head = head->next;
        counter++;
    }
    if (counter == number) {
        return head;
    }
    else {
        return NULL;
    }
}

void searchByQuestion(archive *head, char *question) {
    int counter = 0;
    while (head) {
        if (!strcmp(head->question, question)) {
            printf("\x1B[2J\x1B[H");
            printf("Menu -> Teacher's mode -> Search data -> Search by question\n"
            "Done!\n");
            viewItem(head, counter);
            printf("Press any key to return...");
            getchar();
            return;
        }
        head = head->next;
        counter++;
    }
    printf("Nothing is found!\n"
           "Press any key to return...");
    getchar();
}

void searchByAnswer(archive *head, char *answer) {
    int j, counter = 0;
    while (head) {
        for (j = 0; j < 4; j++) {
            if (!strcmp(head->answers[j], answer)) {
                printf("\x1B[2J\x1B[H");
                printf("Menu -> Teacher's mode -> Search data -> Search by answer\n"
                       "Done!\n");
                viewItem(head, counter);
                printf("Press any key to return...");
                getchar();
                return;
            }
        }
        head = head->next;
        counter++;
    }
    printf("Nothing is found!\n"
           "Press any key to return...");
    getchar();
}

void searchByCorrectAnswer(archive *head, int correctAnswer) {
    int counter = 0;
    int isFound = 0;
    while (head) {
        if (correctAnswer == head->correctAnswer) {
            if (!isFound) {
                printf("\x1B[2J\x1B[H");
                printf("Menu -> Teacher's mode -> Search data -> Search by correct answer\n"
                "Done!\n");
            }
            viewItem(head, counter);
            printf("\n");
            isFound = 1;
        }
        head = head->next;
        counter++;
    }
    if (!isFound) {
        printf("Nothing is found!\n");
    }
    printf("Press any key to return...");
    getchar();
}
