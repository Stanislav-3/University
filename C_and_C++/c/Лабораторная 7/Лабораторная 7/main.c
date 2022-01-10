#include <stdlib.h>
#include "dialog.h"

/**
 * Variant 17
 * DeltaTest.
 * Разработать локальную систему тестирования.
 * Провести тестирование по языку программирования С.
 */
int main(void) {
    char menu = 0;
    archive *data = NULL;
    archive *current = NULL;
    int qustionNumber = 1, correctAnswerCounter = 0;
    if(!initialization(&data)) return -1;
    current = data;
    while(!menu) {
        printf("\x1B[2J\x1B[H");
        printf("Hello to ""Delta test"" for c!\n\n"
               "Menu\n"
               ">Input <Enter> to start testing\n"
               ">Input <h> for help\n"
               ">Input <e> to finish\n"
               ">Input <t> to switch on \"Teacher's mode\"\n>>>");
        menu = input();
        switch (menu) {
            case '\n':
                /* Menu -> Testing */;
                if (qustionNumber != 1) {
                    /* If user already asked some questions */
                    char answer;
                    printf("\x1B[2J\x1B[H");
                    printf("Do you want to continue from previous step?\n"
                           ">Input <y> for ""Yes""\n"
                           ">Input <n> for ""No"" (Your progress will be lost)\n");
                    answer = input();
                    if (answer == 'y') {
                        current = startTest(current, &qustionNumber, &correctAnswerCounter);
                    } else {
                        qustionNumber = 1;
                        correctAnswerCounter = 0;
                        current = startTest(data, &qustionNumber, &correctAnswerCounter);
                    }
                } else {
                    /* If the test progress is empty */
                    current = startTest(data, &qustionNumber, &correctAnswerCounter);
                }
                if (current) {
                    /* The test is not done yet */
                    menu = 0;
                } else {
                    /* The test is done */
                    char answer;
                    printf("\x1B[2J\x1B[H");
                    printf("Congrats! You've done the test!\n"
                           "Correct answers: %d out of %d\n",
                           correctAnswerCounter, qustionNumber - 1);
                    if (correctAnswerCounter == qustionNumber - 1) {
                        printf("Brilliant! Everything's correct :D\n");
                    } else if (correctAnswerCounter > (qustionNumber - 1) / 2) {
                        printf("Not bad! Mostly done :)\n");
                    } else if (!correctAnswerCounter) {
                        printf("You need to get prepared better... :(\n"
                               "Or...maybe it's not yours?\n");
                    } else {
                        printf("Not bad...Good luck in your future career! :)\n");
                    }
                    printf("\nDo you want to return to the main menu?\n"
                           ">Input <y> for ""Yes""\n"
                           ">Input <n> for ""No""\n");
                    answer = input();
                    if (answer == 'y') {
                        menu = 0;
                    }
                }
                break;
            case 'h':
                printf("\x1B[2J\x1B[H");
                printf("Menu -> Help\n");
                menuHelp();
                menu = 0;
                break;
            case 'e':
                updateFile(data);
                deleteAll(&data);
                return 0;
                break;
            case 't':
                printf("\x1B[2J\x1B[H");
                printf("Menu->Teacher's mode\n");
                techerMode(&data);
                menu = 0;
                break;
            default:
                printf("\x1B[2J\x1B[H");
                printf("Invalid input!\n"
                       "Press any key to continue...");
                getchar();
                break;
        }
    }
    updateFile(data);
    deleteAll(&data);
    return 0;
}
