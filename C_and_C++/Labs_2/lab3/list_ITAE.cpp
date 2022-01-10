#include "ui_mainwindow.h"
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
//#include <QValidator>
//#include <QRegExpValidator>
#include "QRegularExpression"

class list_ITAE {
public:
    list_ITAE *next;
    list_ITAE *prev;

    QString date, city, time, fromNumber, toNumber;
    int code;
    double tariff;

    int addInfo(list_ITAE **list, QString newInfo) {
        QStringList infoList = newInfo.split(" ", QString::SkipEmptyParts);
        // Check the input
        QRegExp checkNumber("^\\+\\d{1,3}\\(\\d{2,3}\\)\\d{3}-\\d{2}-\\d{2}$");
        QRegExp checkCity("^[A-Z][a-z]+$");
        QRegExp checkCode("^\\d+$");
        QRegExp checkDate("^(0[1-9]|[1-2][0-9]|3[0-1]).(0[1-9]|1[0-2]).(2020|20[0-1][0-9])$");
        QRegExp checkTime("^([0-1][0-9]|2[0-3]).([0-5][0-9])$");
        QRegExp checkTariff("^\\d{1,2}.?\\d{0,2}$");
        if (infoList.size() != 7) return 0;
        if (!checkNumber.exactMatch(infoList[0])) return 0;
        if (!checkNumber.exactMatch(infoList[1])) return 0;
        if (!checkCity.exactMatch(infoList[2])) return 0;
        if (!checkCode.exactMatch(infoList[3])) return 0;
        if (!checkDate.exactMatch(infoList[4])) return 0;
        if(!checkTime.exactMatch(infoList[5])) return 0;
        if(!checkTariff.exactMatch(infoList[6])) return 0;
        // Create a new list
        list_ITAE *head = new list_ITAE;
        if (*list) {
            (*list)->prev = head;
        }
        head->next = *list;
        head->prev = NULL;
        // Fill a new list
        head->fromNumber = infoList[0];
        head->toNumber = infoList[1];
        head->city = infoList[2];
        head->code = infoList[3].toInt();
        head->date = infoList[4];
        head->time = infoList[5];
        head->tariff = infoList[6].toDouble();
        *list = head;
        return 1;
    }

    void viewInfo(list_ITAE *list, Ui::MainWindow *ui) {
        ui->listWidget->clear();
            ui->listWidget->addItem("outgoingNumber\tincomingNumber\tcity\tcityCode\tdate\ttime\ttariff");
            while (list) {
                ui->listWidget->addItem(list->fromNumber + "\t" + list->toNumber + "\t" + list->city + "\t" + QString::number(list->code) + "\t" +
                                    list->date + "\t" + list->time + "\t" + QString::number(list->tariff));
                list = list->next;
        }
    }

    int deleteNumber (list_ITAE **list, QString number) {
        bool numberIsFound = false;
        list_ITAE *listItem = *list;
        while(listItem) {
            if (!QString::compare(number, listItem->fromNumber)) {
                numberIsFound = true;
                list_ITAE *nextListItem = listItem->next;
                //delete an item of a list
                if (listItem->next) {
                    listItem->next->prev = listItem->prev;
                }
                if (listItem->prev) {
                    listItem->prev->next = listItem->next;
                }
                else {
                    *list = listItem->next;
                }
                delete listItem;
                listItem = nextListItem;
                continue;
            }
            listItem = listItem->next;
        }
        if (numberIsFound) return 1;
        return 0;
    }

    int searchNumber(list_ITAE *list, QString number, Ui::MainWindow *ui) {
        bool numberIsFound = false;
        ui->listWidget->clear();
        ui->listWidget->addItem("outgoingNumber\tincomingNumber\tcity\tcityCode\tdate\ttime\ttariff");
        while (list) {
            if (!(QString::compare(number, list->fromNumber) && QString::compare(number, list->toNumber))) {
                numberIsFound = true;
                ui->listWidget->addItem(list->fromNumber + "\t" + list->toNumber + "\t" + list->city + "\t" + QString::number(list->code) + "\t" +
                                    list->date + "\t" + list->time + "\t" + QString::number(list->tariff));
            }
            list = list->next;
        }
        if (numberIsFound) return 1;
        ui->listWidget->clear();
        return 0;
    }

    int searchCity(list_ITAE *list, QString city, Ui::MainWindow *ui) {
        bool cityIsFound = false;
        ui->listWidget->clear();
        ui->listWidget->addItem("outgoingNumber\tincomingNumber\tcity\tcityCode\tdate\ttime\ttariff");
        while (list) {
            if (!QString::compare(city, list->city)) {
                cityIsFound = true;
                ui->listWidget->addItem(list->fromNumber + "\t" + list->toNumber + "\t" + list->city + "\t" + QString::number(list->code) + "\t" +
                                    list->date + "\t" + list->time + "\t" + QString::number(list->tariff));
            }
            list = list->next;
        }
        if (cityIsFound) return 1;
        ui->listWidget->clear();
        return 0;
    }
};
