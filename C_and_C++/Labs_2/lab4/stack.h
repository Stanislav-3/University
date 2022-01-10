#ifndef STACK_H
#define STACK_H
#include <QChar>
#include <QString>
#include "QDebug"
class Stack
{
    Stack *next;

    QChar *symbol;
    double number;

public:
    void pushChar(Stack **head, QChar ch);
    void pushDouble(Stack **head, double dbl);
    QChar topChar(Stack *head);
    double topDouble(Stack *head);
    void pop(Stack **head);
    void empty(Stack **head);
    int infixToPostfix(Stack *head, QString infixExpression, QString *postfixExpression);
    QString calculateResult(Stack *head, QString postfixExpression, double a, double b, double c, double d, double e);
};

#endif // STACK_H
