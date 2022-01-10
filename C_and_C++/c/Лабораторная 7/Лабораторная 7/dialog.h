#include "file.h"

char input() {
    char ch, buff[2] = {0};
    int i = -1;
    do {
        i++;
        ch = getchar();
        buff[i] = ch;
    } while (ch != '\n' && i < 2);
    if (i) {
        buff[i] = 0;
    }
    if (buff[1]) {
        /* Clear the input stream */
        while(getchar() != '\n');
        return 0;
    }
    return buff[0];
}

int inputNumber() {
    char buff[100] = {0};
    int i = -1;
    do {
        i++;
        buff[i] = getchar();
        if (!(buff[i] >= '0' && buff[i] <= '9') && buff[i] != '\n') {
            while(getchar() != '\n');
            return 0;
        }
    } while (buff[i] != '\n');
    buff[i] = 0;
    return atoi(buff);
}

void menuHelp() {
    printf("It's a programm for checking your knowledge in C programming language. "
           "You will be trying to answer questions :)\n"
           """Teacher's mode"" is for a teacher for altering questions.\n"
           "Press any key to return...");
    getchar();
}

void testHelp() {
    printf("\x1B[2J\x1B[H");
    printf("Menu -> Testing -> Help\n");
    printf("Hey! Everything's simple :)\n"
           "Just input the number of the answer and you will know whether it's correctly\n"
           "Don't worry, if not you will have time to think over\n"
           "Press any key to return...");
    getchar();
}

void developerModeHelp() {
    printf("\x1B[2J\x1B[H");
    printf("Menu -> Teacher's mode -> Help\n");
    printf("Hey! Everything's simple :)\n"
           "Just input the number of the menu or 'e'(to return)\n"
           "Press any key to return...");
    getchar();
}

void seeCurrentDataHelp() {
    printf("\x1B[2J\x1B[H");
    printf("Menu -> Teacher's mode -> See current data -> Help\n");
    printf("Hey! Everything's simple :)\n"
           "Input 1 to see all the information\n"
           "Input 2 to see exact question(if it not exists you will be informed)\n"
           "Input 'e' to return\n"
           "Press any key to return...");
    getchar();
}

void deleteDataHelp() {
    printf("\x1B[2J\x1B[H");
    printf("Menu -> Teacher's mode -> Delete data -> Help\n");
    printf("Hey! Everything's simple :)\n"
           "Input 1 to delete all the information\n"
           "Input 2 to delete exact question(if it not exists you will be informed)\n"
           "Input 'e' to return\n"
           "Press any key to return...");
    getchar();
}

void searchDataHelp() {
    printf("\x1B[2J\x1B[H");
    printf("Menu -> Teacher's mode -> Search data -> Help\n");
    printf("Hey! Everything's simple :)\n"
           "Input 1 to search question with a question\n"
           "Input 2 to search question with an answer\n"
           "Input 3 to search question with correct answer\n"
           "Input 'e' to return\n"
           "Press any key to return...");
    getchar();
}

archive* startTest(archive *head, int *questionNumber, int *correctAnswerCounter) {
    int j, i = *questionNumber;
    int failed = 0;
    char answer;
    while(head) {
        printf("\x1B[2J\x1B[H");
        printf("Menu -> Testing\n");
        printf("? ? ? ? ? ? ? ? ?\n"
           "?  Question №%d\t?\n"
           "? ? ? ? ? ? ? ? ?\n%s\n", i, head->question);
        for (j = 0; j < 4; j++) {
            printf("%d) %s\n", j + 1, head->answers[j]);
        }
        printf("\n>Input 'e' to return\n"
               ">Input 'h' for help\n"
               "Input correct answer\n>>>");
        answer = input();
        if (answer == 'e') break;
        if (answer == 'h') {
            testHelp();
            continue;
        }
        if (answer == head->correctAnswer + '0') {
            /* Correct answer */
            (*questionNumber)++;
            if (!failed) {
                (*correctAnswerCounter)++;
            }
            failed = 0;
            printf("Congrats!\nYou answered correctly :)\n"
                   "Press any key to continue...");
            getchar();
            head = head->next;
            i++;
        } else {
            /* Incorrect answer */
            failed = 1;
            printf("Ooops...\nYou answered incorrectly :(\n"
                   "The correct answer is %d\n"
                   "Don't worry and take a minute to think :) (You will be asked again)\n"
                   "Press any key to continue...",
                   head->correctAnswer);
            getchar();
        }
    }
    return head;
}

void techerMode(archive **head) {
    char answer;
    for (;;) {
        printf("\x1B[2J\x1B[H");
        printf("Menu -> Teacher's mode\n"
               "What do you want to do?\n"
               "1) See current data\n"
               "2) Add data\n"
               "3) Delete data\n"
               "4) Search data\n"
               "\n>Input 'e' to return\n"
               ">Input 'h' for help\n>>>");
        answer = input();
        switch (answer) {
            case 'e':
                return;
                break;
            case 'h':
                developerModeHelp();
                break;
            case '1':
                /* See current data */
                for (;;) {
                    printf("\x1B[2J\x1B[H");
                    printf("Menu -> Teacher's mode -> See current data\n"
                           "What do you want to do?\n"
                           "1) See all data\n"
                           "2) See exact data\n"
                           "\n>Input 'e' to return\n"
                           ">Input 'h' for help\n>>>");
                    answer = input();
                    if (answer == 'e') break;
                    if (answer == 'h') {
                        seeCurrentDataHelp();
                        continue;
                    }
                    if (answer - '0' == 1) {
                        /* See all data */
                        printf("\x1B[2J\x1B[H");
                        printf("Menu -> Teacher's mode -> See current data -> See all data\n");
                        viewAll(*head);
                        printf("Press any key to return...");
                        getchar();
                        break;
                    } else if (answer - '0' == 2) {
                        /* See axact data */
                        int number;
                        archive *chosenItem;
                        printf("\x1B[2J\x1B[H");
                        printf("Menu -> Teacher's mode -> See current data -> See exact data\n"
                               "What question do you want to see?\n"
                               "Input a number\n>>");
                        number = inputNumber();
                        if (!number) {
                            printf("Invalid input...\n"
                                   "Press any key to return...");
                            getchar();
                            break;
                        }
                        chosenItem = searchItem(*head, number - 1);
                        if (!chosenItem) {
                            printf("The question №%d doesn't exist\n", number);
                        }
                        else {
                            printf("\x1B[2J\x1B[H");
                            printf("Menu -> Teacher's mode -> See current data -> See exact data\n");
                            viewItem(chosenItem, number - 1);
                        }
                        printf("Press any key to return...");
                        getchar();
                        break;
                    } else {
                        printf("Invalid input...\n"
                               "Press any key to return...");
                        getchar();
                        break;
                    }
                }
                break;
            case '2':
                /* Add data */
                for(;;) {
                    char *question, *answers[4];
                    int correctAnswer = 0;
                    int j;
                    printf("\x1B[2J\x1B[H");
                    printf("Menu -> Teacher's mode -> Add data\n");
                    printf("Enter a question (or 'e' to return):\n");
                    question = (char*)calloc(sizeof(char), size + 1);
                    for (j = 0; j < 4; j++) {
                        answers[j] = (char*)calloc(sizeof(char), size + 1);
                    }
                    /* Question input */
                    for(j = 0; j < 1; j++) {
                        scanf("%[^\n]s", question);
                        getchar();
                        if (question[size] != 0) {
                            /* if overflow */
                            printf("The question is too long! (it must be <= %d)\n"
                                   "Input again(or 'e' to exit)\n", size);
                            for(j = 0; j < size + 1; j++) {
                                question[j] = 0;
                            }
                            j = -1;
                        }
                        if (!strcmp(question, "e")) {
                            free(question);
                            question = NULL;
                            break;
                        }
                    }
                    if (!question) break;
                    /* Answers input */
                    printf("Enter answers (or 'e' to return):\n");
                    for (j = 0; j < 4; j++) {
                        printf("%d) ", j + 1);
                        scanf("%[^\n]s", answers[j]);
                        getchar();
                        if (answers[j][size] != 0) {
                            /* if overflow */
                            int i;
                            printf("The answer is too long! (it must be <= %d)\n"
                                   "Input shorter answer(or 'e' to exit)\n", size);
                            for(i = 0; i < size + 1; i++) {
                                answers[j][i] = 0;
                            }
                            j--;
                        }
                        if (!strcmp(answers[j], "e")) {
                            free(question);
                            question = NULL;
                            break;
                        }
                    }
                    if (!question) break;
                    /* Correct answer input */
                    printf("Input correct answer (or 'e' to return):\n");
                    while(!correctAnswer) {
                        correctAnswer = input() - '0';
                        if (correctAnswer == 'e' - '0') break;
                        if (!(correctAnswer >= 1 && correctAnswer <= 4)) {
                            printf("Invalid input (it must be 1<=value<=4)\n"
                            "Input again(or 'e' to exit)\n");
                            correctAnswer = 0;
                        }
                    }
                    if (!question) {
                        for (j = 0; j < 4; j++) {
                            free(answers[j]);
                        }
                        break;
                    }
                    addToArchive(head, question, answers, correctAnswer);
                    addToFile(*head);
                    break;
                }
                break;
            case '3':
                /* Delete data */
                for(;;) {
                    char answer;
                    printf("\x1B[2J\x1B[H");
                    printf("Menu -> Teacher's mode -> Delete data\n"
                           "What do you want to do?\n"
                           "1) Delete all data\n"
                           "2) Delete exact data\n"
                           "\n>Input 'e' to return\n"
                           ">Input 'h' for help\n>>>");
                    answer = input();
                    if (answer == 'e') break;
                    if (answer == 'h') {
                        deleteDataHelp();
                        continue;
                    }
                    if (answer - '0' == 1) {
                        printf("\x1B[2J\x1B[H");
                        printf("Menu -> Teacher's mode -> Delete data -> Delete all data\n");
                        /* Confirming */
                        printf("Are you sure you want to delete everything from the archive?\n"
                               "Input <y> to confirm\n>>>");
                        answer = input();
                        if (answer == 'y') {
                            printf("Everything is deleted!\n");
                            deleteAll(head);
                        } else {
                            printf("Nothing is deleted!\n");
                        }
                        printf("Press any key to return...");
                        getchar();
                    } else if (answer - '0' == 2) {
                        int number;
                        archive *chosenItem;
                        printf("\x1B[2J\x1B[H");
                        printf("Menu -> Teacher's mode -> Delete data -> Delete exact data\n"
                               "What question do you want to delete?\n"
                               "Input a number\n>>");
                        number = inputNumber();
                        if (!number) {
                           printf("Invalid input...\n"
                                  "Press any key to return...");
                           getchar();
                           break;
                        }
                        chosenItem = searchItem(*head, number - 1);
                        if (!chosenItem) {
                            printf("The question №%d doesn't exist\n"
                                   "Press any key to return...", number);
                            getchar();
                            break;
                        }
                        /* Confirming */
                        printf("Are you sure you want to delete this question from the archive?\n"
                               "Input <y> to confirm\n");
                        viewItem(chosenItem, number - 1);
                        printf(">>>");
                        answer = input();
                        if (answer == 'y') {
                            printf("The question is deleted!\n");
                            *head = deleteItem(&chosenItem);
                        } else {
                            printf("Nothing is deleted!\n");
                        }
                        printf("Press any key to return...");
                        getchar();
                    }  else {
                           printf("Invalid input...\n"
                                  "Press any key to return...");
                           getchar();
                    }
                    break;
                }
                break;
            case '4':
                /* Search data */
                for(;;) {
                    printf("\x1B[2J\x1B[H");
                    printf("Menu -> Teacher's mode -> Search data\n"
                           "What do you want to do?\n"
                           "1) Search by question\n"
                           "2) Search by answers\n"
                           "3) Search by correct answer\n"
                           "\n>Input 'e' to return\n"
                           ">Input 'h' for help\n>>>");
                    answer = input();
                    if (answer == 'e') break;
                    if (answer == 'h') {
                        searchDataHelp();
                        continue;
                    }
                    if (answer - '0' == 1) {
                        /* Search by question */
                        char question[size + 1] = {0};
                        int j;
                        for(;;) {
                            printf("\x1B[2J\x1B[H");
                            printf("Menu -> Teacher's mode -> Search data -> Search by question\n"
                                   "Input question (or 'e' to return):\n");
                            scanf("%[^\n]s", question);
                            getchar();
                            if (question[size] != 0) {
                                /* if overflow */
                                printf("The question is too long! (it must be <= %d)\n"
                                       "Input again(or 'e' to exit)\n"
                                       "Press any key to return...", size);
                                getchar();
                                for(j = 0; j < size + 1; j++) {
                                    question[j] = 0;
                                }
                                continue;
                            }
                            if (!strcmp(question, "e")) break;
                            searchByQuestion(*head, question);
                            break;
                        }
                    } else if (answer - '0' == 2) {
                        /* Search by answer */
                        char answer[size + 1] = {0};
                        int j;
                        for(;;) {
                            printf("\x1B[2J\x1B[H");
                            printf("Menu -> Teacher's mode -> Search data -> Search by answer\n"
                                   "Input question (or 'e' to return):\n");
                            scanf("%[^\n]s", answer);
                            getchar();
                            if (answer[size] != 0) {
                                /* if overflow */
                                printf("The answer is too long! (it must be <= %d)\n"
                                       "Input again(or 'e' to exit)\n"
                                       "Press any key to return...", size);
                                getchar();
                                for(j = 0; j < size + 1; j++) {
                                    answer[j] = 0;
                                }
                                continue;
                            }
                            if (!strcmp(answer, "e")) break;
                            searchByAnswer(*head, answer);
                            break;
                        }
                    } else if (answer - '0' == 3) {
                        /* Search by correct answer */
                        int correctAnswer;
                        for(;;) {
                            printf("\x1B[2J\x1B[H");
                            printf("Menu -> Teacher's mode -> Search data -> Search by correct answer\n"
                                   "Input correct answer (or 'e' to return):\n");
                            correctAnswer = input();
                            if (correctAnswer == 'e') break;
                            if (!(correctAnswer - '0' >= 0 && correctAnswer - '0' <= 4)) {
                                /* if invalid input */
                                printf("Incorrect input...\n"
                                       "Input again(or 'e' to exit)\n"
                                       "Press any key...");
                                getchar();
                                continue;
                            }
                            searchByCorrectAnswer(*head, correctAnswer - '0');
                            break;
                        }
                    } else {
                        printf("Invalid input...\n"
                               "Press any key to return...");
                        getchar();
                    }
                    break;
                }
                break;
            default:
                printf("Invalid input...\n"
                       "Press any key...");
                getchar();
        }
    }
}
