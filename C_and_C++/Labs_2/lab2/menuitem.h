#ifndef MENUITEM_H
#define MENUITEM_H

class MenuItem
{
public:
    char Name[30] = {0};
    char Category[30] = {0};
    double Price;
public:
    int Initialization(MenuItem **menu, int &count);
};

#endif // MENUITEM_H
