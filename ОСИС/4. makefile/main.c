#include <stdio.h>
#include "DublyLinkedList.h"
#include "ListStrings.h"
#include "Client.h"
#include "ClintList.h"
#include "Goods.h"
#include "GoodsList.h"


void PrintMenu();
void addGood(struct ClientList *clientList, struct GoodsList * goodsList);
void removeGood(struct ClientList *clientList, struct GoodsList* goodsList);
void AppendToFile(FILE *file, struct ClientList* clientLiist, struct GoodsList * goodsList);
void Initialize(FILE *file, struct ClientList* clientList, struct GoodsList * goodsList);
void readWord(char *buffer, FILE *file);
void saveWord(FILE *file, char *str);
int CalculatePrice(struct GoodsList goodsList);
int CalculateMoney(struct GoodsList goodsList);
int CalcProfit(struct GoodsList goodsList);


int main() {

    FILE *file;
    if((file = fopen("DataBase.txt", "r")) == NULL)
    {
        printf("ERROR. File isn't opened\n");
        return 1;
    }
    else{
        printf("\nFile opened successfully\n");
    }

    struct GoodsList* goodsList = (struct GoodsList*) malloc(sizeof(struct GoodsList));
    struct ClientList* clientList = (struct ClientList*) malloc(sizeof(struct ClientList));

    goodsList->head = NULL;
    goodsList->tail = NULL;
    clientList->head = NULL;
    clientList->tail = NULL;

    Initialize(file, clientList, goodsList);

    while(1){
        PrintMenu();
        int choise;
        printf("Enter: ");
        if(!scanf("%i", &choise)){
            printf("Error with input\n"
                   "Press any key to continue..\n");
            int ch = getchar();
            while(getchar() != '\n');
            while(getchar() != '\n');
            continue;
        }

        switch (choise) {
            case 1:
                PrintClients(*clientList);
                break;
            case 2:
                PrintGoods(*goodsList);
                break;
            case 3:
                addGood(clientList, goodsList);
                break;
            case 4:
                removeGood(clientList, goodsList);
                break;
            case 5:
                CalculatePrice(*goodsList);
                break;
            case 6:
                CalcProfit(*goodsList);
                break;
            case 7:
                AppendToFile(file, clientList, goodsList);
                fclose(file);
                return 0;
            default:
                printf("Wrong Input\n"
                       "Press any key to continue...");
                int ch = getchar();
                while(getchar() != '\n');
                //while(getchar() != '\n');
                continue;
        }


        printf("Press any key to continue...\n");
        int ch = getchar();
        while(getchar() != '\n');
    }

}


void addGood(struct ClientList *clientList, struct GoodsList * goodsList){
    struct Good* newGood = (struct Good*) malloc(sizeof(struct Good));
    char string[20];

    while(getchar() != '\n');
    printf("Enter good name (1 word, Exmpl: Telephone): ");
    scanf("%s", newGood->name);

    while(getchar() != '\n');
    printf("Enter client ID (1word, Exmpl: id12345): ");
    scanf("%s", newGood->clientID);

    while(1) {
        printf("Enter its value in $ (1 number, Exmpl: 1000)\nValue: ");
        if(!scanf("%i", &newGood->value) || newGood->value < 1){
            printf("Wrong input! Enter a positive number!\n");
            while(getchar() != '\n');
            continue;
        }
        else{
            break;
        }
    }

    while(1) {
        printf("Enter amount of money will be gave to Client(1 number, Exmpl: 50)\nMoney: ");
        if(!scanf("%i", &newGood->money) || newGood->money < 1){
            printf("Wrong input! Enter a number!\n");
            while(getchar() != '\n');
            continue;
        }
        if (newGood->value <= newGood->money){
            printf("Our lambard couldn't give more money then good is costs\n"
                   "Suggest less money to Client (money < value)\n");
            continue;
        }
        break;
    }

    while(getchar() != '\n');
    printf("Enter today date (1word, Exmpl: 27_May): ");
    scanf("%s", newGood->date);

    while(getchar() != '\n');
    printf("For how long time give money to Client (1word, Exmpl: 2_month): ");
    scanf("%s", newGood->timeKeeping);

    printf("\n\nAlso we need few information about that client\n");

    struct Client* newClient = (struct Client*) malloc(sizeof(struct Client));

    while(getchar() != '\n');
    printf("What is Client's name? (1word, Exmpl: Vladislav)\nEnter: ");
    scanf("%s", newClient->name);

    while(getchar() != '\n');
    printf("What is Client's Passport number? (1word, Exmpl: AB123456)\nEnter: ");
    scanf("%s", newClient->Passport);

    AddClient(clientList, newClient);
    AddGood(goodsList, newGood);

    printf("All data saved successfully\n\n");
}


void removeGood(struct ClientList *clientList, struct GoodsList* goodsList){
    int num = PrintAllNames(*clientList);

    int choise;
    while(1) {
        if (!scanf("%i", &choise) || choise < 0 || choise > num) {
            printf("Error with input\n"
                   "Press any key to continue..\n");
            int ch = getchar();
            while (getchar() != '\n');
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    struct Node_Client* tempClient = clientList->head;
    struct Node_Good* tempGood = goodsList->head;

    int i;
    for(i = 0; i < choise - 1; i++){
        tempGood = tempGood->next;
        tempClient = tempClient->next;
    }

    DeleteGood(goodsList, tempGood->data);
    DeleteClient(clientList, tempClient->data);

    printf("Element deleted!\n");
}

void AppendToFile(FILE *file, struct ClientList* clientLiist, struct GoodsList * goodsList){
    if((file = fopen("DataBase.txt", "w")) == NULL)
    {
        printf("ERROR. File isn't opened\n");
        return ;
    }

    struct Node_Client* tempClient = NewClient();
    tempClient = clientLiist->head;

    struct Node_Good * tempGood = NewGood();
    tempGood = goodsList->head;

    while(tempClient != NULL){
        fprintf(file, "%s %s %s", tempClient->data->name, tempClient->data->Passport, tempClient->data->history);
        tempClient = tempClient->next;

        fprintf(file, "%s %s %i %i %s %s\n", tempGood->data->name, tempGood->data->clientID, tempGood->data->value,
                tempGood->data->money, tempGood->data->date, tempGood->data->timeKeeping);
        tempGood = tempGood->next;
    }
    fclose(file);

    printf("All new Data saved to the file succefully !\n");

}


void Initialize(FILE *file, struct ClientList* clientList, struct GoodsList * goodsList){

//    if((file = fopen("DataBase.txt", "r")) == NULL)
//    {
//        printf("ERROR. File isn't opened\n");
//        return ;
//    }
//    else{
//        printf("\nFile opened successfully\n");
//    }

    int check = getc(file);
    if (check == EOF){
        printf("No Data to Initialize from file\n"
               "File is empty\n\n");
        return;
    }
    else{
        rewind(file);
    }

    while(1){
        if(feof(file)){
            break;
        }

        struct Client* client = (struct Client*) malloc(sizeof(struct Client));
        struct Good* good = (struct Good*) malloc(sizeof(struct Good));

        saveWord(file, client->name);
        saveWord(file, client->Passport);
        saveWord(file, good->name);
        saveWord(file, good->clientID);

        char buffer[20] = "";
        readWord(buffer, file);
        int value;
        sscanf(buffer, "%d", &value);
        good->value = value;

        int money;
        strcpy(buffer, "");
        readWord(buffer, file);
        sscanf(buffer, "%d", &money);
        good->money = money;

        saveWord(file, good->date);
        saveWord(file, good->timeKeeping);


        AddClient(clientList, client);
        AddGood(goodsList, good);
        char ch = getc(file);
        if(ch == EOF){
            printf("Data from file initialized successfully!\n");
            break;
        }
        else{
            fseek(file, -1, SEEK_CUR);
        }
    }

}


void readWord(char *buffer, FILE *file){
    char ch = (char) fgetc(file);
    while(1){
        strncat(buffer, &ch, 1);
        ch = (char) fgetc(file);
        if((ch == ' ') || (ch == '\n')){
            break;
        }
    }
}


void saveWord(FILE *file, char str[]){
    char buffer[20] = "";
    readWord(buffer, file);
    strcpy(str, buffer);
}


int CalculatePrice(struct GoodsList goodsList){
    int price = 0;
    struct Node_Good* current = goodsList.head;
    if(current == NULL){
        printf("List is empty, can't calculate\n");
        return 0;
    }
    else{
        while(current != NULL ){
            price += current->data->value;
            current = current->next;
        }
    }

    printf("\nThe cost of all stored items: %i $\n\n", price);

    return price;
}


int CalculateMoney(struct GoodsList goodsList){
    int price = 0;
    struct Node_Good* current = goodsList.head;
    if(current == NULL){
        printf("List is empty, can't calculate\n");
        return 0;
    }
    else{
        while(current != NULL ){
            price += current->data->money;
            current = current->next;
        }
    }
    return price;
}


int CalcProfit(struct GoodsList goodsList){
    int profit = CalculatePrice(goodsList) - CalculateMoney(goodsList);

    printf("Profit is: %i $\n", profit);
    return profit;
}


void PrintMenu(){
    printf("\n1. Show all clients info\n"
           "2. Show all goods info\n"
           "3. Add Good and it's Client\n"
           "4. Delete Good\n"
           "5. Calculate Lambard Profit\n"
           "6. Calculate price of all Goods\n"
           "7. Close session\n\n");
}
