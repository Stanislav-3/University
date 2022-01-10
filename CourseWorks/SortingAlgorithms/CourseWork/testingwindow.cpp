#include "testingwindow.h"
#include "ui_testingwindow.h"
#include "sortingmethods.h"
#include <QMessageBox>
#include <QDir>
#include <QFile>

TestingWindow::TestingWindow(QWidget *parent) :QDialog(parent), ui(new Ui::TestingWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("<Information>");
    this->setFixedSize(320, 381);
    sortType = BubbleSort;
    sortTypeString = "BubbleSort";
    sortMethodPtr = SortingMethods::bubbleSort;
    size = ui->sizeLineEdit->text().toInt();
    mod = ui->modulusLineEdit->text().toInt();
    sortedKoeff = ui->sortedKoeffLineEdit->text().toInt();
    swapsKoeff = ui->swapsLineEdit->text().toInt();
    srand(time(0));
}

TestingWindow::~TestingWindow()
{
    delete ui;
}

void TestingWindow::on_returnButton_clicked()
{
    TestingWindow::~TestingWindow();
}

void TestingWindow::on_sortTypeComboBox_activated(int index)
{
    sortType = (sortMethods)index;
    switch (sortType) {
        case BubbleSort:
            sortMethodPtr = SortingMethods::bubbleSort;
            sortTypeString = "BubbleSort";
            break;
        case ShakerSort:
            sortMethodPtr = SortingMethods::shakerSort;
            sortTypeString = "ShakerSort";
            break;
        case CombSort:
            sortMethodPtr = SortingMethods::combSort;
            sortTypeString = "CombSort";
            break;
        case InsertionSort:
            sortMethodPtr = SortingMethods::insertionSort;
            sortTypeString = "InsertionSort";
            break;
        case Shellsort:
            sortMethodPtr = SortingMethods::shellsort;
            sortTypeString = "Shellsort";
            break;
        case TreeSort:
            sortMethodPtr = SortingMethods::treeSort;
            sortTypeString = "TreeSort";
            break;
        case GnomeSort:
            sortMethodPtr = SortingMethods::gnomeSort;
            sortTypeString = "GnomeSort";
            break;
        case SelectionSort:
            sortMethodPtr = SortingMethods::selectionSort;
            sortTypeString = "SelectionSort";
            break;
        case Heapsort:
            sortMethodPtr = SortingMethods::heapsort;
            sortTypeString = "Heapsort";
            break;
        case QuickSort:
            sortMethodPtr = SortingMethods::quickSort;
            sortTypeString = "QuickSort";
            break;
        case MergeSort:
            sortMethodPtr = SortingMethods::mergeSort;
            sortTypeString = "MergeSort";
            break;
        case BucketSort:
            sortMethodPtr = SortingMethods::bucketSort;
            sortTypeString = "BucketSort";
            break;
        case LSDSort:
            sortMethodPtr = SortingMethods::LSDSort;
            sortTypeString = "LSDSort";
            break;
        case MSDSort:
            sortMethodPtr = SortingMethods::MSDSort;
            sortTypeString = "MSDSort";
            break;
        case BitonicSort:
            sortMethodPtr = SortingMethods::bitonicSort;
            sortTypeString = "BitonicSort";
            break;
        case Timsort:
            sortMethodPtr = SortingMethods::timsort;
            sortTypeString = "Timsort";
            break;
    }
}

void TestingWindow::on_sizeLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int newSize = arg1.toInt(&ok);
    if (!ok || newSize < 0 || newSize > (int)1e9) {
        ui->sizeLineEdit->setText(QString::number(size));
    }
    else {
        size = newSize;
    }
}

void TestingWindow::on_modulusLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int newModulus = arg1.toInt(&ok);
    if (!ok || newModulus < 1 || newModulus > (int)1e9) {
        ui->modulusLineEdit->setText(QString::number(mod));
    }
    else {
        mod = newModulus;
    }
}

void TestingWindow::on_sortedKoeffLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    double newSortedKoeff = arg1.toDouble(&ok);
    if (!ok || newSortedKoeff < 0 || newSortedKoeff > 100) {
        ui->sortedKoeffLineEdit->setText(QString::number(sortedKoeff));
    }
    else {
        sortedKoeff = newSortedKoeff;
    }
}

void TestingWindow::on_swapsLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    double newSwaps = arg1.toDouble(&ok);
    if (!ok || newSwaps < 0 || newSwaps > 100) {
        ui->swapsLineEdit->setText(QString::number(swapsKoeff));
    }
    else {
        swapsKoeff = newSwaps;
    }
}

void TestingWindow::on_questionButton_1_clicked()
{
    QMessageBox::information(this, "<Information>", "Random certain size array of numbers by certain modulus is initialized (size & modulus you can define below)");
}

void TestingWindow::on_questionButton_2_clicked()
{
    QMessageBox::information(this, "<Information>", "Random certain size array of numbers by certain modulus with a sorted part is initialized (size & modulus & sorted part you can define below)");
}

void TestingWindow::on_questionButton_3_clicked()
{
    QMessageBox::information(this, "<Information>", "Random certain size array of numbers by certain modulus with a certain swaps in initialized (size & modulus & amount of swaps you can define below)");
}

void TestingWindow::on_questionButton_4_clicked()
{
    QMessageBox::information(this, "<Information>", "Random certain size array of numbers by certain modulus sorted in reverse order is initialized (size & modulus you can define below)");
}

void TestingWindow::on_questionButton_5_clicked()
{
    QMessageBox::information(this, "<Information>", "Size cannot be less than 0 or more than\n1 000 000 000");
}

void TestingWindow::on_questionButton_6_clicked()
{
    QMessageBox::information(this, "<Information>", "Modulus cannot be less than 0 or more than 1 000 000 000");
}

void TestingWindow::on_questionButton_7_clicked()
{
    QMessageBox::information(this, "<Information>", "Sorted koefficient cannot be less than 0 % or more than 100 %");
}

void TestingWindow::on_questionButton_8_clicked()
{
    QMessageBox::information(this, "<Information>", "Swaps koefficient cannot be less than 0 % or more than 100 %");
}

int* TestingWindow::formArray(int testNumber)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % mod;
    }
    if (testNumber == 2) {
        /* Partly sorted */
        int lInd;
        if (qRound(sortedKoeff) != 100) {
            lInd = rand() % (int)(size * (1 - sortedKoeff / 100));
        }
        else {
            lInd = 0;
        }
        int rInd = lInd + size * (sortedKoeff / 100);
        if (rInd > size) rInd = size;
        std::sort(arr + lInd, arr + rInd);
    }
    else if (testNumber == 3) {
        /* Sorted array with swaps */
        int swaps = size * (swapsKoeff / 100);
        std::sort(arr, arr + size);
        for (int i = 0; i < swaps; i++) {
            int j = rand() % size;
            int k = rand() % size;
            std::swap(arr[j], arr[k]);
        }
    }
    else if (testNumber == 4) {
        /* Reversed */
        std::sort(arr, arr + size, std::greater<int>());
    }

    return arr;
}

QString TestingWindow::toFile(QString testInfo, bool sorted, unsigned int time, int *array, int testNumber)
{
    QDir dir = QDir::currentPath();
    for (int i = 0; i < 4; i++) {
        dir.cdUp();
    }
    QString path = dir.path();
    QString testsPath = path;
    QString fileName;
    if (sorted) {
        fileName = testInfo + "(sorted)";
    }
    else {
        fileName = testInfo + "(raw)";
    }
    if (!QDir(path).exists("Tests")) {
        QDir(path).mkdir("Tests");
    }
    path += "/Tests/" + fileName + ".txt";
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::critical(this, "Error!","File is not open!");
        return "";
    }
    file.write(fileName.toUtf8() + '\n');
    if (sorted) {
        file.write("TIME: " + QString::number(time).toUtf8() + " ms\n");
    }
    file.write("SIZE: " + QString::number(size).toUtf8() + "\n"
               "MODULUS: " + QString::number(mod).toUtf8() + "\n");
    if (testNumber == 2) {
         file.write("SORTED: " + QString::number(sortedKoeff).toUtf8() + " %\n");
    }
    if (testNumber == 3) {
         file.write("Swaps: " + QString::number(swapsKoeff).toUtf8() + " %\n");
    }
    if (testNumber == 4) {
         file.write("REVERSED\n");
    }

    for (int i = 0; i < size; i++) {
        file.write(QString::number(array[i]).toUtf8() + ' ');
    }
    file.close();
    return testsPath;
}

void TestingWindow::on_sortingTest_1_clicked()
{
    int *array = formArray(1);
    toFile("Test1_" + sortTypeString, false, 0, array, 1);
    unsigned int time = clock();
    sortMethodPtr(array, array + size);
    time = clock() - time;
    QString testsPath = toFile("Test1_" + sortTypeString, true, time, array, 1);
    QMessageBox::information(this, "Test1_" + sortTypeString,
                             "Time: " + QString::number(time) + "ms\n"
                             "Size:" + QString::number(size) + "\n"
                             "Mod:" + QString::number(mod) + "\n"
                             "Sorted and unsorted arrays you can find in\n\"" + testsPath + "\"");
    delete array;
}

void TestingWindow::on_sortingTest_2_clicked()
{
    int *array = formArray(2);
    toFile("Test2_" + sortTypeString, false, 0, array, 2);
    unsigned int time = clock();
    sortMethodPtr(array, array + size);
    time = clock() - time;
    QString testsPath = toFile("Test2_" + sortTypeString, true, time, array, 2);
    QMessageBox::information(this, "Test2_" + sortTypeString,
                             "Time: " + QString::number(time) + "ms\n"
                             "Size:" + QString::number(size) + "\n"
                             "Mod:" + QString::number(mod) + "\n"
                             "Sorted:" + QString::number(sortedKoeff) + "%\n"
                             "Sorted and unsorted arrays you can find in\n\"" + testsPath + "\"");
    delete array;
}

void TestingWindow::on_sortingTest_3_clicked()
{
    int *array = formArray(3);
    toFile("Test3_" + sortTypeString, false, 0, array, 3);
    unsigned int time = clock();
    sortMethodPtr(array, array + size);
    time = clock() - time;
    QString testsPath = toFile("Test3_" + sortTypeString, true, time, array, 3);
    QMessageBox::information(this, "Test3_" + sortTypeString,
                             "Time: " + QString::number(time) + "ms\n"
                             "Size:" + QString::number(size) + "\n"
                             "Mod:" + QString::number(mod) + "\n"
                             "Swaps:" + QString::number(swapsKoeff) + "%\n"
                             "Sorted and unsorted arrays you can find in\n\"" + testsPath + "\"");
    delete array;
}

void TestingWindow::on_sortingTest_4_clicked()
{
    int *array = formArray(4);
    toFile("Test4_" + sortTypeString, false, 0, array, 4);
    unsigned int time = clock();
    sortMethodPtr(array, array + size);
    time = clock() - time;
    QString testsPath = toFile("Test4_" + sortTypeString, true, time, array, 4);
    QMessageBox::information(this, "Test4_" + sortTypeString,
                             "Time: " + QString::number(time) + "ms\n"
                             "Size:" + QString::number(size) + "\n"
                             "Mod:" + QString::number(mod) + "\n"
                             "Revered\n"
                             "Sorted and unsorted arrays you can find in\n\"" + testsPath + "\"");
    delete array;
}
