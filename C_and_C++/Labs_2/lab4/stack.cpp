#include "stack.h"

void Stack::pushChar(Stack **head, QChar ch)
{
    Stack *newHead = new Stack();
    newHead->symbol = ch;
    if (!head) {
        *head = newHead;
    }
    else {
        newHead->next = *head;
        *head = newHead;
    }
}

void Stack::pushDouble(Stack **head, double dbl)
{
    Stack *newHead = new Stack();
    newHead->number = dbl;
    if (!head) {
        *head = newHead;
    }
    else {
        newHead->next = *head;
        *head = newHead;
    }
}

QChar Stack::topChar(Stack *head)
{
    if (head) {
        return head->symbol;
    }
    else {
        return 0;
    }
}

double Stack::topDouble(Stack *head)
{
    if (head) {
        return head->number;
    }
    else {
        return 0;
    }
}

void Stack::pop(Stack **head)
{
    if (!head) {
        return;
    }
    else {
        Stack *temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

void Stack::empty(Stack **head)
{
    while(*head) {
        Stack *temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

int Stack::infixToPostfix(Stack *head, QString infixExpression, QString *postfixExpression) {
    infixExpression = infixExpression + "$";
    pushChar(&head, '$');
    int i = 0;
    for(;;) {
        switch (infixExpression[i].toLatin1()) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
            *postfixExpression += infixExpression[i];
            i++;
            break;
        case '+':
        case '-':
            if (topChar(head) == '$' || topChar(head) == '(') {
                pushChar(&head, infixExpression[i]);
                i++;
            }
            else {
                *postfixExpression += topChar(head);
                pop(&head);
            }
            break;
        case '*':
        case '/':
            if (topChar(head) == '*' || topChar(head) == '/') {
                *postfixExpression += topChar(head);
                pop(&head);
            }
            else {
                pushChar(&head, infixExpression[i]);
                i++;
            }
            break;
        case '(':
            pushChar(&head, infixExpression[i]);
            i++;
            break;
        case ')':
            if (topChar(head) == '$') {
                empty(&head);
                return 0;
            } else if (topChar(head) == '(') {
                pop(&head);
                i++;
            } else {
                *postfixExpression += topChar(head);
                pop(&head);
            }
            break;
        case '$':
            if (topChar(head) == '$') {
                empty(&head);
                return 1;
            } else if (topChar(head) == '(') {
                empty(&head);
                return 0;
            } else {
                *postfixExpression += topChar(head);
                pop(&head);
            }
            break;
        }
    }
    empty(&head);
    return 0;
}

QString Stack::calculateResult(Stack *head, QString postfixExpression, double a, double b, double c, double d, double e) {
    postfixExpression = postfixExpression + "$";
    int i = 0;
    double x1, x2;
    while (postfixExpression[i] != '$') {
        switch (postfixExpression[i].toLatin1()) {
        case 'a':
            pushDouble(&head, a);
            i++;
            break;
        case 'b':
            pushDouble(&head, b);
            i++;
            break;
        case 'c':
            pushDouble(&head, c);
            i++;
            break;
        case 'd':
            pushDouble(&head, d);
            i++;
            break;
        case 'e':
            pushDouble(&head, e);
            i++;
            break;
        case '+':
            x1 = topDouble(head);
            pop(&head);
            x2 = topDouble(head);
            pop(&head);
            pushDouble(&head, x2 + x1);
            i++;
            break;
        case '-':
            x1 = topDouble(head);
            pop(&head);
            x2 = topDouble(head);
            pop(&head);
            pushDouble(&head, x2 - x1);
            i++;
            break;
        case '*':
            x1 = topDouble(head);
            pop(&head);
            x2 = topDouble(head);
            pop(&head);
            pushDouble(&head, x2 * x1);
            i++;
            break;
        case '/':
            x1 = topDouble(head);
            pop(&head);
            x2 = topDouble(head);
            pop(&head);
            pushDouble(&head, x2 / x1);
            i++;
            break;
        }
    }
    double result = head->topDouble(head);
    return QString::number(result);
}
