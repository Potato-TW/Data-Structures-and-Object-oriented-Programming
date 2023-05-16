#include "GameCharacter.h"

GameCharacter::GameCharacter() :Object() {};
GameCharacter::GameCharacter(string _name, string _tag, int _maxHealth, int _sp,
    int _attack, int _defense) :
    Object(_name, _tag)
{
    maxHealth = _maxHealth;
    currentHealth = _maxHealth;
    sp = _sp;
    maxSp=_sp;
    attack = _attack;
    defense = _defense;
}

//GameCharacter(string,string,int,int,int);
//    string name;
//    int maxHealth;
//    int currentHealth;
//    int attack;
//    int defense;

bool GameCharacter::checkIsDead() {
    bool isDead = 0;

    if (currentHealth == 0) {
        isDead = 1;
    }

    return isDead;
}

void GameCharacter::setMaxHealth(int newHealth) { maxHealth = newHealth; }
void GameCharacter::setCurrentHealth(int newHealth) {
    currentHealth = newHealth;

    if(currentHealth<=0)
        currentHealth=0;
    if(currentHealth>=maxHealth)
        currentHealth=maxHealth;
 }
void GameCharacter::setAttack(int newAttack) { attack = newAttack; }
void GameCharacter::setDefense(int newDefense) { defense = newDefense; }
void GameCharacter::setSp(int newSp){
    sp=newSp;
    if(sp<=0)
        sp=0;
    if(sp>=maxSp)
        sp=maxSp;
}
void GameCharacter::setMaxSp(int n){maxSp=n;}
void GameCharacter::addSp(){
    if(sp>=maxSp)  return ;
    sp++;
}

int GameCharacter::getMaxHealth() { return maxHealth; }
int GameCharacter::getCurrentHealth() { return currentHealth; }
int GameCharacter::getAttack() { return attack; }
int GameCharacter::getDefense() { return defense; }
int GameCharacter::getSp(){return sp;}
int GameCharacter::getMaxSp(){return maxSp;}
