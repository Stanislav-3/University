#include <stdio.h>
#include <stdlib.h>
#include "list.c"
#include "tree.c"
#include "string.h"
#include "time.h"

/**
 * Дан стек, элементы которого содержат номер обрабатываемого дерева i ( i ≤ n ) и копируемые в дерево данные (целое число d).
 * Сформировать на основе стека n бинарных деревьев поиска. Подсчитать и вывести на печать сумму значений в каждом дереве.
 */
int input() {
    char ch[3] = {0};
    scanf("%[^\n]s", ch);
    if (ch[2] != 0 || !(ch[0] >= '1' && ch[0] <= '9') ||
       (!(ch[1] >= '0' && ch[1] <= '9') && ch[1] != 0)) {
        printf("Invalid input...\n");
        exit(0);
    }
    return atoi(ch);
}

void listInitialization(struct listItem **list, int n) {
    int i;
    for (i = 0; i < n; i++) {
        int valuesNumber, j;
        valuesNumber = rand() % 15 + 1;
        for (j = 0; j < valuesNumber; j++) {
            struct listItem *head = (struct listItem*)calloc(n, sizeof(struct listItem));
            if (list[i]) {
                (list[i])->prev = head;
            }
            head->next = list[i];
            head->prev = NULL;
            head->d = rand() % 50 + 1;
            list[i] = head;
        }
    }
}

int listPop(struct listItem **list) {
    int value;
    if(!list) {
        return -1;
    }
    else {
        struct listItem *temp = *list;
        value = (*list)->d;
        *list = (*list)->next;
        free(temp);
        if (*list) {
            (*list)->prev = NULL;
        }
    }
    return value;
}

void addTree(struct treeItem **tree, int d) {
    if (*tree == NULL) {
      *tree = (struct treeItem *)calloc(1, sizeof(struct treeItem));
      (*tree)->d = d;
      (*tree)->left = (*tree)->right = NULL;
    } else if (d < (*tree)->d) {
        addTree(&(*tree)->left, d);
    } else if (d > (*tree)->d) {
        addTree(&(*tree)->right, d);
    }
}

void outputTree(struct treeItem *root) {
    if (!root) {
        printf("*");
        return;
    }
    if (root->d) {
        printf("%d", root->d);
    }
    if (!root->left && !root->right) return;
    printf("(");
    outputTree(root->left);
    printf(",");
    outputTree(root->right);
    printf(")");
}

int sumTree(struct treeItem *root) {
    int l = 0, r = 0;
    if (!root) return 0;
    if(root->left) {
        l = sumTree(root->left);
    }
    if(root->right) {
        r = sumTree(root->right);
    }
    return l + r + root->d;
}

void deleteTree(struct treeItem *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main(void) {
    int n, i;
    struct listItem **list;
    struct treeItem **trees;
    printf("Enter amount of trees(<100): ");
    n = input();
    list = (struct listItem**)calloc(n, sizeof(struct listItem*));
    trees = (struct treeItem**)calloc(n, sizeof(struct treeItem*));
    /* Filling the list with random amount of future tree values */
    srand((int)time(0));
    listInitialization(list, n);
    /* Fill the trees with the values from the list */
    for (i = 0; i < n; i++) {
        while(list[i]) {
            addTree(&trees[i], listPop(&list[i]));
        }
    }
    /* Output each tree and calculate sum of the elements */
    for (i = 0; i < n; i++) {
        printf("Tree №%d: ", i);
        outputTree(trees[i]);
        printf("\nSum: %d\n", sumTree(trees[i]));
    }
    /* Empty the memory */
    free(list);
    for (i = 0; i < n; i++) {
        deleteTree(trees[i]);
    }
    free(trees);
    return 0;
}
