#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    vector<string> scripts;
    vector<Item> commodity;
public:
    NPC();
    NPC(string, string);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    string triggerEvent(Object*) override;

    /* Set & Get function*/
    void setScript(string);
//    void setCommodity(vector<Item>);
    string getScript();
//    vector<Item> getCommodity();
};

class Merchant:public NPC{
private:
    vector<string> scripts;
    vector<pair<Item, int>> sales;
public:
    Merchant();
    Merchant(string, string);
//    Merchant(string, vector<string>, vector<pair<Item, int>>);
    void showSales();
    void setScript(string);
//    void setCommodity(vector<Item>);
    string triggerEvent(Object*) override;
    string getScript();
//    vector<Item> getCommodity();
};

class Cat:public NPC{
private:
    string sound;
public:
    Cat();
    Cat(string, string);
    void setSound();
    string getSound();
    string triggerEvent(Object*) override;
};

class Blacksmiths:public NPC{
private:
    vector<string> scripts;
    vector<string> services;
public:
    Blacksmiths();
    Blacksmiths(string, string);
    void setScript(string);
    string getScript();
    void showServices();
    string triggerEvent(Object*) override;
};

#endif // NPC_H_INCLUDED
