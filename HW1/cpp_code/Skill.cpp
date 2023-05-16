#include"Skill.h"

Skill::Skill() {};
Skill::Skill(string _name, string _tag, int _damage, int _sp) :
    name(_name), tag(_tag), damage(_damage), sp(_sp) {};

string Skill::getSkillName(){return name;}
string Skill::getSkillTag(){return tag;}
int Skill::getSkillSp(){return sp;}
int Skill::getSkillDamage(){return damage;}

void Skill::setSkillName(string n){name=n;}
void Skill::setSkillTag(string n){tag=n;}
void Skill::setSkillSp(int n){sp=n;}
void Skill::setSkillDamage(int n){damage=n;}
