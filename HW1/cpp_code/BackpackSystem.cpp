#include "BackpackSystem.h"
using namespace std;

Backpack::Backpack() {};
Backpack::Backpack(int _money) : Object("backpack", "backpack"), money(_money) {
    key=0;
};

void Backpack::showPack() {
    cout<<"Money: "<<money<<" dollars\n";
    cout<<"Key: "<<key<<endl;
    cout<<"Pack: "<<endl;

    vector<string> tags;
    for(auto it=pack.begin();it!=pack.end();it++){
        bool no=1;
        for(auto itt=tags.begin();itt!=tags.end();itt++){
            if(it->getTag()==*itt){
                no=0;
                break;
            }
        }
        if(no){
            string temp;
            temp = it->getTag();
            tags.push_back(temp);
        }
    }

//    for(int i=0;i<tags.size();i++){
//        cout<<tags.at(i)<<" ";
//    }cout<<endl;

    char num = 'A';
    for(auto itt=tags.begin();itt!=tags.end();itt++){
        for (auto it = pack.begin(); it != pack.end(); it++) {
            if(it->getTag()!=*itt)
                continue;

            cout<<num<<": ";
            cout << setiosflags(ios::left) << setw(15) << it->getName();

            if(it->getTag() == "right"){
                cout<<" atk: "<<it->getAttack();
            }
            if (it->getTag() == "left"||it->getTag() == "head"||it->getTag() == "body")
                cout<<" def: "<<it->getDefense();

            cout<<" hp: "<<it->getCurHealth() << " / " << it->getMaxHealth();
            cout << endl;
            num++;
        }
    }

//    if(tags.empty())
//        cout<<"NULL\n";


}
void Backpack::setItem(Item newItem) {
    pack.push_back(newItem);
}
void Backpack::setMoney(int newMoney) {
    money = newMoney;
}
void Backpack::setPack(vector<Item> newone){pack=newone;}
void Backpack::setKey(int num){key = num;}
void Backpack::setItems(vector<Item> newone){pack=newone;}

int Backpack::getKey(){return key;}
int Backpack::getMoney() { return money; }
void Backpack::purchase(int cost){
    if(money-cost<0){
        cout<<"You don't have enough money!"<<endl;
        return ;
    }

    money-=cost;
}

vector<Item> Backpack::getPack(){return pack;}
string Backpack::triggerEvent(Object* obj){return "1";}


