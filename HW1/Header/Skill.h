#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED
#include<iostream>
#include<vector>
//#include "Object.h"
using namespace std;

class Skill{
private:
    string name;
    string tag;
    int damage;
    int sp;
public:
    Skill();
    Skill(string,string, int, int);

    void setSkillName(string);
    void setSkillTag(string);
    void setSkillSp(int);
    void setSkillDamage(int);


    string getSkillName();
    string getSkillTag();
    int getSkillSp();
    int getSkillDamage();
};



#endif // SKILL_H_INCLUDED
