#ifndef MAPOBJECT_H_INCLUDED
#define MAPOBJECT_H_INCLUDED
#include<iostream>
#include<vector>
#include"Object.h"
#include"Item.h"
#include"BackpackSystem.h"
#include"Skill.h"
using namespace std;

class Skill;

class Box:public Object{
private:
    int money;
    int key;
    bool needkey;
    vector<Skill> treasure;

public:
    Box();
    Box(string, string, int , int, vector<Skill>, bool);
    string triggerEvent(Object*) override;

    bool getNeedkey();
    vector<Skill> getTreasure();
    void setTreasure(vector<Skill>);

};




#endif // MAPOBJECT_H_INCLUDED
