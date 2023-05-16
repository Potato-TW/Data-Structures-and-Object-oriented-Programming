#include"MapObject.h"

Box::Box() {};
Box::Box(string _name, string _tag, int _money, int _key, vector<Skill>_treasure, bool _needkey) :
    Object(_name, _tag), money(_money), key(_key), treasure(_treasure), needkey(_needkey){};

string Box::triggerEvent(Object* object) {
    Backpack* pack = dynamic_cast<Backpack*>(object);

    if(money!=0){
        cout<<"You get "<<money<<" dollars from this box!"<<endl;
        pack->setMoney(money + pack->getMoney());
        money=0;
    }

    if(key!=0){
        cout<<"You get "<<key<<" key!"<<endl;
        pack->setKey(key + pack->getKey());
        key=0;
    }

    cout<<endl;
    return "1";
}

bool Box::getNeedkey(){return needkey;}
vector<Skill> Box::getTreasure(){return treasure;}

void Box::setTreasure(vector<Skill> newTreasure){treasure = newTreasure;}
