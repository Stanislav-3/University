#include "list.h"

int initialization(archive **head) {
    FILE *fp;
    char *question, *answers[4];
    int correctAnswer, i;
    if (!(fp = fopen("/Users/stanislav/Desktop/c/Лабораторная 7/Лабораторная 7/Data", "r"))) {
        printf("Sorry...we have some problems with the archive :(\n");
        return 0;
    }
    while(!feof(fp)) {
        question = (char*)calloc(sizeof(char), size + 1);
        fscanf(fp, "%[^\n]s", question);
        if (question[size] != 0) return 0;
        /* fgets() - reads '\n' in all cases */
        for (i = 0; i < 4; i++) {
            fgetc(fp);
            answers[i] = (char*)calloc(sizeof(char), size + 1);
            fscanf(fp, "%[^\n]s", answers[i]);
            if (answers[i][size] != 0) return 0;
        }
        fgetc(fp);
        fscanf(fp, "%d", &correctAnswer);
        addToArchive(head, question, answers, correctAnswer);
        question = NULL;
        for (i = 0; i < 4; i++) {
            answers[i] = NULL;
        }
        fgetc(fp);
        fgetc(fp);
    }
    return 1;
}

void addToFile(archive *head) {
    FILE *fp;
    int j;
    if (!(fp = fopen("Data", "a"))) {
        printf("Sorry...we have some problems with the archive :(\n");
        return;
    }
    fputs("\n\n", fp);
    fputs(head->question, fp);
    for (j = 0; j < 4; j++) {
        fputc('\n', fp);
        fputs(head->answers[j], fp);
    }
    fputc(head->correctAnswer, fp);
    fclose(fp);
}

void updateFile(archive *head) {
    FILE *fp;
    int j;
    if (!(fp = fopen("Data", "w"))) {
        printf("Sorry...we have some problems with the archive :(\n");
        return;
    }
    while(head) {
        if (head->prev) {
            fputs("\n\n", fp);
        }
        fputs(head->question, fp);
        for (j = 0; j < 4; j++) {
            fputc('\n', fp);
            fputs(head->answers[j], fp);
        }
        fputc('\n', fp);
            fputc(head->correctAnswer + '0', fp);
        head = head->next;
    }
    fclose(fp);
}
