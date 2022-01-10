#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(389, 596);
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setColumnWidth(0, 175);
    ui->treeWidget->setColumnWidth(1, 25);
    ui->treeWidget->setHeaderLabels(QStringList() << "Name" << "Score");
    ui->listWidget->addItem("Tap \"View\" to see the \ninformation!");
    item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,"Tap to see\na tree!");
    tree = nullptr;
    tree->Initialization(item, this, &tree, initialInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
    tree->DeleteAll(&tree->root);
}

void MainWindow::on_Exit_clicked()
{
    exit(0);
}

void MainWindow::on_View_clicked()
{
    if (!tree->root) return;
    QMessageBox msgBox(this);
    msgBox.setText("Choose method of tree traversal:");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton("Exit", QMessageBox::DestructiveRole);
    msgBox.addButton("Show all", QMessageBox::ActionRole);
    QAbstractButton *preOrderButton = msgBox.addButton("Pre-order", QMessageBox::ActionRole);
    QAbstractButton *inOrderButton = msgBox.addButton("In-order", QMessageBox::ActionRole);
    QAbstractButton *postOrderButton = msgBox.addButton("Post-order", QMessageBox::ActionRole);
    msgBox.exec();
    ui->listWidget->clear();
    if (msgBox.clickedButton() == preOrderButton) {
        ui->listWidget->addItem("Pre-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PreOrderTraversal(tree->root, ui->listWidget);
    } else if (msgBox.clickedButton() == inOrderButton) {
        ui->listWidget->addItem("In-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->InOrderTraversal(tree->root, ui->listWidget);
    } else if (msgBox.clickedButton() == postOrderButton) {
        ui->listWidget->addItem("Post-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PostOrderTraversal(tree->root, ui->listWidget);
    } else {
        ui->listWidget->addItem("Pre-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PreOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nIn-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->InOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nPost-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PostOrderTraversal(tree->root, ui->listWidget);
    }
}

void MainWindow::on_Add_clicked()
{
    QString input = QInputDialog::getText(this, "Input...", "Name\tScore (<1000)");
    if (input == "") return;
    QStringList inputList = input.split(" ");
    if (inputList.size() != 2) {
        QMessageBox::critical(this, "Error!", "Invalid input...");
        return;
    }
    QRegExp checkName("^[A-Z][a-z]+$");
    QRegExp checkScore("\\d{1,3}");
    if (!checkName.exactMatch(inputList[0])) {
        QMessageBox::critical(this, "Error!", "Invalid input...");
        return;
    }
    if (!checkScore.exactMatch(inputList[1])) {
        QMessageBox::critical(this, "Error!", "Invalid input...");
        return;
    }
    tree->Add(this, &tree->root, inputList[0], inputList[1].toInt());
    ui->listWidget->clear();
    ui->listWidget->addItem("Pre-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->PreOrderTraversal(tree->root, ui->listWidget);
    ui->listWidget->addItem("\nIn-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->InOrderTraversal(tree->root, ui->listWidget);
    ui->listWidget->addItem("\nPost-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->PostOrderTraversal(tree->root, ui->listWidget);
    item->removeChild(item->child(0));
    item->removeChild(item->child(1));
    if(!tree->View(item, tree->root)) {
        item->setText(0,"Tree is empty");
    }
    else {
        item->setText(0,"Tap to see\na tree!");
    }
}

void MainWindow::on_Balance_clicked()
{
    if (!tree->root) return;
    QMessageBox::information(this, "Information...", "Tree is successfully balanced!");
    tree->Balance(tree);
    ui->listWidget->clear();
    ui->listWidget->addItem("Pre-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->PreOrderTraversal(tree->root, ui->listWidget);
    ui->listWidget->addItem("\nIn-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->InOrderTraversal(tree->root, ui->listWidget);
    ui->listWidget->addItem("\nPost-order traversal:");
    ui->listWidget->addItem("Name\tScore");
    tree->PostOrderTraversal(tree->root, ui->listWidget);
    item->removeChild(item->child(0));
    item->removeChild(item->child(1));
    if(!tree->View(item, tree->root)) {
        item->setText(0,"Tree is empty");
    }
    else {
        item->setText(0,"Tap to see\na tree!");
    }
}

void MainWindow::on_Search_clicked()
{
    if (!tree->root) return;
    QString input = QInputDialog::getText(this, "Delete", "Input Score");
    if (input == "") return;
    QRegExp checkScore("\\d+");
    if (!checkScore.exactMatch(input)) {
        QMessageBox::critical(this, "Error!", "Invalid input...");
        return;
    }
    tree->Search(this, tree->root, input.toInt(), ui->listWidget);
}

void MainWindow::on_Delete_clicked()
{
    if (!tree->root) return;
    QString input = QInputDialog::getText(this, "Delete", "Input Score");
    if (input == "") return;
    QRegExp checkScore("\\d+");
    if (!checkScore.exactMatch(input)) {
        QMessageBox::critical(this, "Error!", "Invalid input...");
        return;
    }
    tree->Delete(this, &tree->root, input.toInt(), ui->listWidget);
    ui->listWidget->clear();
    if (tree->root) {
        ui->listWidget->addItem("Pre-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PreOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nIn-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->InOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nPost-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PostOrderTraversal(tree->root, ui->listWidget);
    }
    else {
        ui->listWidget->addItem("The tree is empty!");
    }
    item->removeChild(item->child(0));
    item->removeChild(item->child(1));
    if(!tree->View(item, tree->root)) {
        item->setText(0,"Tree is empty");
    }
    else {
        item->setText(0,"Tap to see\na tree!");
    }
}

void MainWindow::on_MySolution_clicked()
{
    if (!tree->root) return;
    QMessageBox::information(this, "My task:", "Swap info with the smallest and largest keys");
    Soluton mySolution;
    if(tree->root && (tree->root->left || tree->root->right)) {
        mySolution.swap(mySolution.minKey(tree->root), mySolution.maxKey(tree->root));
        item->removeChild(item->child(0));
        item->removeChild(item->child(1));
        if(!tree->View(item, tree->root)) {
            item->setText(0,"Tree is empty");
        }
        else {
            item->setText(0,"Tap to see\na tree!");
        }
        ui->listWidget->clear();
        ui->listWidget->addItem("Pre-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PreOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nIn-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->InOrderTraversal(tree->root, ui->listWidget);
        ui->listWidget->addItem("\nPost-order traversal:");
        ui->listWidget->addItem("Name\tScore");
        tree->PostOrderTraversal(tree->root, ui->listWidget);
        return;
    }
    QMessageBox::critical(this, "Ooops...", "You have only a root!\nor even a stump :)");
}
