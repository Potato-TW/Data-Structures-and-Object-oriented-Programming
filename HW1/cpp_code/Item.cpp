#include "Item.h"
Item::Item():Object("",""), name(""), maxHealth(0), curHealth(0), attack(0), defense(0){};

Item::Item(string _name, string _tag, int _health, int _attack, int _defense) :
    Object(_name, _tag), name(_name), maxHealth(_health), curHealth(_health), attack(_attack), defense(_defense) {};

int Item::getMaxHealth() { return maxHealth; }
int Item::getCurHealth() { return curHealth; }
int Item::getAttack() { return attack; }
int Item::getDefense() { return defense; }
string Item::getName() { return name; }

void Item::setName(string n){name=n;}
void Item::setMaxHealth(int n){maxHealth=n;}
void Item::setCurHealth(int newHealth) {
    curHealth=newHealth;
    if(curHealth<0){
        curHealth=0;
    }
    if(curHealth>maxHealth)
        curHealth=maxHealth;
}
void Item::setAttack(int newAttack) { attack = newAttack; }
void Item::setDefense(int newDefense) { defense = newDefense; }

string Item::triggerEvent(Object* object) { return "1"; }
