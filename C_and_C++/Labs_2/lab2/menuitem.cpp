#include "menuitem.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>

int MenuItem::Initialization(MenuItem **menu, int &count) {
    QFile menuFile("/Users/stanislav/Desktop/c++/laba2/Menu.txt");
    if (!menuFile.open(QFile::ReadOnly | QFile::Text)) {
        return 0;
    }
    QTextStream stream(&menuFile);
    // Count amount of items in the menu
    while (stream.readLine() != "") {
        count++;
    }
    stream.seek(0);
    *menu = new MenuItem [count];
    for (int i = 0; i < count; i++) {
        stream >> (*menu)[i].Name;
        stream >> (*menu)[i].Category;
        stream >> (*menu)[i].Price;
    }
    menuFile.close();
    return 1;
}
