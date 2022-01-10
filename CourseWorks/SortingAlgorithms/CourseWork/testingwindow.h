#ifndef TESTINGWINDOW_H
#define TESTINGWINDOW_H

#include <QDialog>

namespace Ui {
class TestingWindow;
}

class TestingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestingWindow(QWidget *parent = nullptr);
    ~TestingWindow();

    enum sortMethods {
        BubbleSort = 0,
        ShakerSort,
        CombSort,
        InsertionSort,
        Shellsort,
        TreeSort,
        GnomeSort,
        SelectionSort,
        Heapsort,
        QuickSort,
        MergeSort,
        BucketSort,
        LSDSort,
        MSDSort,
        BitonicSort,
        Timsort
    } sortType;
//    Q_ENUM(sortMethods);

private slots:
    void on_returnButton_clicked();

    void on_sortTypeComboBox_activated(int index);

    void on_sortingTest_1_clicked();

    void on_sizeLineEdit_textChanged(const QString &arg1);

    void on_modulusLineEdit_textChanged(const QString &arg1);

    void on_sortedKoeffLineEdit_textChanged(const QString &arg1);

    void on_swapsLineEdit_textChanged(const QString &arg1);

    void on_sortingTest_2_clicked();

    void on_sortingTest_3_clicked();

    void on_sortingTest_4_clicked();

    void on_questionButton_1_clicked();

    void on_questionButton_2_clicked();

    void on_questionButton_3_clicked();

    void on_questionButton_4_clicked();

    void on_questionButton_5_clicked();

    void on_questionButton_6_clicked();

    void on_questionButton_7_clicked();

    void on_questionButton_8_clicked();

private:
    Ui::TestingWindow *ui;
    int size, mod;
    double sortedKoeff, swapsKoeff;
    QString sortTypeString;
    void (*sortMethodPtr)(int *l, int *r);
    int* formArray(int testNumber);
    QString toFile(QString testInfo, bool sorted, unsigned int time, int *array, int testNumber);
};

#endif // TESTINGWINDOW_H
