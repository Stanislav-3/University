#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <QList>
#include <QString>
#include <QListWidget>
#include <QMessageBox>
#include <QtMath>
#include <QTreeWidget>

class Tree
{
public:
    Node *root;
    Tree();
    void Initialization(QTreeWidgetItem *itm, QWidget *widget, Tree **tree, QList<QString> initialInfo);
    void Balance(Tree *tree);
    void Add(QWidget *widget, Node **tree, QString name,  int score);
    void Search(QWidget *widget, Node *tree, int score, QListWidget *listWidget);
    void Delete(QWidget *widget, Node **tree, int score, QListWidget *listWidget);
    void DeleteAll(Node **tree);
    int View(QTreeWidgetItem *parent, Node *tree);
    void PreOrderTraversal(Node *tree, QListWidget *listWidget);
    void InOrderTraversal(Node *tree, QListWidget *listWidget);
    void PostOrderTraversal(Node *tree, QListWidget *listWidget);

};

#endif // TREE_H
