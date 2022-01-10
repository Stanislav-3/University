#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(314, 413);
    ui->listWidget->addItem("You have no items yet!\nBut you can add some :)");
    hashTable = new HashTable;
    hashTable->m = ui->mLineEdit->text().toInt();
    srand(time(0));
}

MainWindow::~MainWindow()
{
    delete ui;
    hashTable->Delete();
    delete hashTable;
}


void MainWindow::on_Exit_clicked()
{
    exit(0);
}

void MainWindow::on_Set_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::information(this, "Warning...", "Information will be lost\nAre you sure?",
                                                                 QMessageBox::No, QMessageBox::Yes);
    if (reply == QMessageBox::No) return;
    int m = ui->mLineEdit->text().toInt();
    if (m > 0 && m <= 1000) {
        hashTable->m = m;
        hashTable->Delete();
    }
    else {
        QMessageBox::critical(this, "Attention!", "Invalid input...\nm∈[1, 1000]");
        ui->mLineEdit->setText(QString::number(hashTable->m));
    }
    ui->listWidget->clear();
    hashTable->Ouput(ui->listWidget);
}

void MainWindow::on_Add_clicked()
{
    // Loop will execute in case the randomized data is already exists
    while(!hashTable->Add(rand() % 1000));
    ui->listWidget->clear();
    hashTable->Ouput(ui->listWidget);
}

void MainWindow::on_Search_clicked()
{
    QString input = QInputDialog::getText(this, "Search", "Your key:");
    if (input == "") return;
    QRegExp checkInput("^\\d+$");
    if(!checkInput.exactMatch(input)) {
        QMessageBox::critical(this, "Error...", "Invalid input!");
        return;
    }
    if (!hashTable->Search(input.toInt())) {
        QMessageBox::information(this, "Warning", "That key doesn't exist");
    }
    else {
        QMessageBox::information(this, "Key is found!", QString::number(hashTable->Encode(input.toInt())) + ": " + QString::number(input.toInt()));
    }
}

void MainWindow::on_Delete_clicked()
{
    QString input = QInputDialog::getText(this, "Delete", "Your key:");
    if (input == "") return;
    QRegExp checkInput("^\\d+$");
    if(!checkInput.exactMatch(input)) {
        QMessageBox::critical(this, "Error...", "Invalid input!");
        return;
    }
    if (!hashTable->Delete(input.toInt())) {
        QMessageBox::information(this, "Warning", "That key doesn't exist");
    }
    else {
        QMessageBox::information(this, "Success!", "Info is deleted");
    }
    ui->listWidget->clear();
    hashTable->Ouput(ui->listWidget);
}

void MainWindow::on_MySolution_clicked()
{
    QMessageBox::information(this, "My task:", "Create hash-table with values ∈[-50, 50]\n"
                                               "And separate them to hash-tables with negative and positive values");
    Solution *generalHashTable = new Solution(hashTable->m);
    Solution *negHashTable = new Solution(hashTable->m);
    Solution *posHashTable = new Solution(hashTable->m);
    generalHashTable->Initialize();
    ui->listWidget->clear();
    ui->listWidget->addItem("General hash-table:");
    generalHashTable->Ouput(ui->listWidget);
    generalHashTable->Separate(negHashTable, posHashTable);
    ui->listWidget->addItem("Negative hash-table:");
    negHashTable->Ouput(ui->listWidget);
    ui->listWidget->addItem("Positive hash-table:");
    posHashTable->Ouput(ui->listWidget);
    delete generalHashTable;
    delete negHashTable;
    delete posHashTable;
}
