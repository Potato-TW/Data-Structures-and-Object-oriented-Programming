#include "Monster.h"

Monster::Monster(string _name, string _tag, int _maxHealth, int _sp,
    int _attack, int _defense) :
    GameCharacter(_name, _tag, _maxHealth, _sp, _attack, _defense) {};

string Monster::triggerEvent(Object* object) { return "1"; }
