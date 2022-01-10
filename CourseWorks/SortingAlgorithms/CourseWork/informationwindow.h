#ifndef INFORMATIONWINDOW_H
#define INFORMATIONWINDOW_H

#include <QDialog>

namespace Ui {
class InformationWindow;
}

class InformationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InformationWindow(QWidget *parent = nullptr);
    ~InformationWindow();

private slots:
    void on_bubbleSortButton_clicked();

    void on_returnButton_clicked();

    void on_helpButton_clicked();

    void on_shakerSortButton_clicked();

    void on_insertionSortButton_clicked();

    void on_shellsortButton_clicked();

    void on_selectionSortButton_clicked();

    void on_quickSortButton_clicked();

    void on_combSortButton_clicked();

    void on_mergeSortButton_clicked();

    void on_heapsortButton_clicked();

    void on_gnomeSortButton_clicked();

    void on_timsortButton_clicked();

    void on_bucketSortButton_clicked();

    void on_LSDSortButton_clicked();

    void on_MSDSortButton_clicked();

    void on_treeSortButton_clicked();

    void on_bitonicSortButton_clicked();

    void on_moreButton_clicked();

private:
    Ui::InformationWindow *ui;

    void showInformation(int windowLength, QString sortName, QString gifPath, int gifLength, QString CC, QString memory,
                         QString stability, QString otherInformation, QString desciption);
};

#endif // INFORMATIONWINDOW_H
