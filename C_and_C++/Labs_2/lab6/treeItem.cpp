#include "treeItem.h"

Tree::Tree()
{
    root = nullptr;
}

void Tree::Initialization(QTreeWidgetItem *itm, QWidget *widget, Tree **tree, QList<QString> initialInfo)
{
    *tree = new Tree;
    for (int i = 0, j = initialInfo.count(); i < j; i++) {
        QStringList list = initialInfo[i].split(" ");
        Add(widget, &(*tree)->root, list[0], list[1].toInt());
    }
    View(itm, (*tree)->root);
}

// For the "Balance(Tree *tree)"
void rotateRight(Node *node) {
    if (!node) return;
    if (!node->left) return;
    node->score = node->score ^ node->left->score;
    node->left->score = node->score ^ node->left->score;
    node->score = node->score ^ node->left->score;
    QString temp = node->name;
    node->name = node->left->name;
    node->left->name = temp;
    Node *copy = node->left;
    node->left = copy->left;
    copy->left = copy->right;
    copy->right = node->right;
    node->right = copy;
}

void rotateLeft(Node *node) {
    if (!node) return;
    if (!node->right) return;
    node->score = node->score ^ node->right->score;
    node->right->score = node->score ^ node->right->score;
    node->score = node->score ^ node->right->score;
    QString temp = node->name;
    node->name = node->right->name;
    node->right->name = temp;
    Node *copy = node->right;
    node->right = copy->right;
    copy->right = copy->left;
    copy->left = node->left;
    node->left = copy;
}
//DSW algorithm
void Tree::Balance(Tree *tree)
{
    // Tree-to-vine
    int count = 0;
    Node *node = tree->root;
    while (node) {
        while ((node)->left) {
            rotateRight(node);
        }
        node = node->right;
        count += 1;
    }
    // Vine-to-tree
    int size = pow(2, qFloor(log2(count + 1))) - 1;
    node = tree->root;
    for (int i = 0; i < count - size; i++) {
        if (i == 0) {
            rotateLeft(node);
            node = tree->root;
        } else {
            rotateLeft(node->right);
            node = node->right;
        }
    }
    while (size > 1) {
        size /= 2;
        rotateLeft(tree->root);
            Node *temp = tree->root;
            for (int i = 0; i < size - 1; i++) {
                rotateLeft(temp->right);
                temp = temp->right;
            }
    }
}

void Tree::Add(QWidget *widget, Node **node, QString name,  int score)
{
    if(!(*node)) {
        (*node) = new Node;
        (*node)->left = (*node)->right = nullptr;
        (*node)->score = score;
        (*node)->name = name;
    } else if ((*node)->score < score) {
        Add(widget, &(*node)->right, name, score);
    } else if ((*node)->score > score) {
        Add(widget, &(*node)->left, name, score);
    } else {
            QMessageBox::information(widget, "Warning...", "That score already exists!\nIt's impossible!");
    }
}

void Tree::Search(QWidget *widget, Node *tree, int score, QListWidget *listWidget)
{
    if (!tree) {
        QMessageBox::information(widget, "Information...", "The item isn't found!");
        return;
    }
    if (tree->score == score) {
        QMessageBox::information(widget, "Information...", "The item is successfuly found!");
        listWidget->clear();
        listWidget->addItem("Name\tScore");
        listWidget->addItem(tree->name + "\t" + QString::number(tree->score));
    } else if (tree->score < score) {
        Search(widget, tree->right, score, listWidget);
    } else if (tree->score > score) {
        Search(widget, tree->left, score, listWidget);
    }
}

void Tree::Delete(QWidget *widget, Node **tree, int score, QListWidget *listWidget)
{
    if (!(*tree)) {
        QMessageBox::information(widget, "Warning...", "The item isn't found!");
        return;
    }
    if ((*tree)->score == score) {
        QMessageBox::information(widget, "Information...", "The item is successfuly deleted!");
        Node *ptr = *tree;
        if (!(*tree)->left && !(*tree)->right) {
            *tree = nullptr;
        } else if (!(*tree)->left) {
            *tree = ptr->right;
        } else if (!(*tree)->right) {
            *tree = ptr->left;
        } else {
            Node *mostLeftParent = (*tree);
            Node *mostLeft = (*tree)->right;
            while (mostLeft->left) {
                mostLeftParent = mostLeft;
                mostLeft = mostLeft->left;
            }
            if (ptr->right->left) {
                mostLeftParent->left = mostLeft->right;
            } else {
                mostLeftParent->right = mostLeft->right;
            }
            ptr->score = mostLeft->score;
            ptr->name = mostLeft->name;
            ptr = mostLeft;
        }
        delete ptr;
    } else if ((*tree)->score < score) {
        Delete(widget, &(*tree)->right, score, listWidget);
    } else if ((*tree)->score > score) {
        Delete(widget, &(*tree)->left, score, listWidget);
    }
}

void Tree::DeleteAll(Node **node)
{
    if (!(*node)) return;
    DeleteAll(&(*node)->left);
    DeleteAll(&(*node)->right);
    delete *node;
}

int Tree::View(QTreeWidgetItem *parent, Node *tree)
{
    if (!tree) return 0;
    QTreeWidgetItem *itm = new QTreeWidgetItem();
    itm->setText(0, tree->name);
    itm->setText(1, QString::number(tree->score));
    parent->addChild(itm);
    if (tree->left) {
        View(itm, tree->left);
    }
    if (tree->right) {
        View(itm, tree->right);
    }
    return 1;
}

void Tree::PreOrderTraversal(Node *tree, QListWidget *listWidget)
{
    if (!tree) return;
    listWidget->addItem(tree->name + "\t" + QString::number(tree->score));
    PreOrderTraversal(tree->left, listWidget);
    PreOrderTraversal(tree->right, listWidget);
}

void Tree::InOrderTraversal(Node *tree, QListWidget *listWidget)
{
    if (!tree) return;
    InOrderTraversal(tree->left, listWidget);
    listWidget->addItem(tree->name + "\t" + QString::number(tree->score));
    InOrderTraversal(tree->right, listWidget);
}

void Tree::PostOrderTraversal(Node *tree, QListWidget *listWidget)
{
    if (!tree) return;
    PostOrderTraversal(tree->left, listWidget);
    PostOrderTraversal(tree->right, listWidget);
    listWidget->addItem(tree->name + "\t" + QString::number(tree->score));
}
