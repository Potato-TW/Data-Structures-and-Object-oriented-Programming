#ifndef BACKPACKSYSTEM_H_INCLUDED
#define BACKPACKSYSTEM_H_INCLUDED

#include<iostream>
#include<vector>
#include<iomanip>
#include "Item.h"
#include<queue>
#include"Object.h"
using namespace std;

class Item;

class Backpack:public Object{
private:
    int money;
    int key;
    vector<Item> pack;

public:
    Backpack();
    Backpack(int);

    // use item
    string triggerEvent(Object*) override;

    vector<Item> getPack();

    void showPack();
    void purchase(int);
    int usePotion();

    void setKey(int);
    void setItem(Item);
    void setItems(vector<Item>);
    void setMoney(int);
    void setPack(vector<Item>);

    int getMoney();
    int getKey();
};

#endif // BACKPACKSYSTEM_H_INCLUDED
