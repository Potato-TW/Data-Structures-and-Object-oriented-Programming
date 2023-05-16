#include "Player.h"

Player::Player() :GameCharacter() {};
Player::Player(string _name, string _tag) : GameCharacter(_name, _tag, 20, 5, 100, 0), var(0) {
    Library lib(true);
    skills.push_back(lib.getSkills(0).at(0));
    skills.push_back(lib.getSkills(0).at(1));
}

//int maxHealth;
//int currentHealth;
//int sp;
//int attack;
//int defense;
int Player::getTotalAtk(){
    updateTTA();
    return totalAtk;
}
int Player::getTotalDef(){
    updateTTD();
    return totalDef;
}
vector<Item> Player::getInventory() { return inventory; }
string Player::triggerEvent(Object* object){return "1";}

void Player::changeInventory(Backpack* pack) {
    char in1, in2;
    Item* item1=NULL,* item2=NULL, *temp=NULL;
//    vector<Item*> armed;

    cout<<"Which equipment do you want to put on?"<<endl;
    cout<<"Inventories:" <<endl;

    showInventory();
    cout<<endl;
    pack->showPack();
//    cout<<endl;
//    cout<<"Inventory:\n";
//    char num='A';
//    for(int i=0;i<pack->getPack().size();i++){
//        Item* equip = &pack->getPack().at(i);
//        if(equip->getTag()=="right"||equip->getTag()=="left"||equip->getTag() == "head"||equip->getTag() == "body"){
//            cout<<num<<": ";
//            cout << setiosflags(ios::left) << setw(15) << equip->getName();
//            if(equip->getTag() == "right"){
//                cout<<" atk: "<<equip->getAttack();
//            }
//            if (equip->getTag() == "left"||equip->getTag() == "head"||equip->getTag() == "body")
//                cout<<" def: "<<equip->getDefense();
//
//            cout<<" hp: "<<equip->getCurHealth() << " / " << equip->getMaxHealth();
//            cout << endl;
//
//            num++;
//            armed.push_back(equip);
//        }
//    }
    string tag;
    while(1){
        cout<<"Q: Quit\n";
        cout<<"Input the item in inventories: ";  cin>>in1;
        cout<<endl;

        if(in1=='Q'||in1=='q'){
            return ;
        }

        if(in1>='a')    in1-='a';
        else    in1-='A';

//        0 head
//        1 body
//        2 left
//        3 right

        int a=int(in1);
        if(a<0||a>3){
            cout << "No! No! You have to choose another correct choice!";
            cout<<endl;
            continue;
        }

        switch(a){
        case 0:
            tag="head";
            break;
        case 1:
            tag="body";
            break;
        case 2:
            tag="left";
            break;
        case 3:
            tag="right";
            break;
        }

        for(int i=0;i<inventory.size();i++){
            if(inventory.at(i).getTag()==tag){
                item1=&inventory.at(i);
                break;
            }
        }
//
//        item1=temp;
//        cout<<"item1 is "<<item1->getName()<<endl;
        break;
    }
    string i2;
    while(1){
        cout<<"Q: Quit\n";
        cout<<"Input the item in pack: "; cin>>in2;
        cout<<endl;

         if(in2=='Q'||in2=='q'){
            return ;
        }

        if(in2>='a')    in2-='a';
        else    in2-='A';

        if(int(in2)<0||int(in2)>=pack->getPack().size()){
            cout << "No! No! You have to choose another correct choice!\n";
            cout<<endl;
            continue;
        }


        if(tag!=pack->getPack().at(int(in2)).getTag()){
            cout<<"No! That's not the right position!\n";
            cout<<endl;
            continue;
        }


        i2 = pack->getPack().at(in2).getName();

        Library a(1);
        for (int i = 0; i < a.getEquips().size(); i++) {
            if (i2 == a.getEquips().at(i).getName()) {
                item2 = &a.getEquips().at(i);
                break;
            }
        }

        break;
    }

    if(item1==NULL){
        inventory.push_back(*item2);

        vector<Item> newPack;
        for(int i=0;i<pack->getPack().size();i++){
            if(i!=int(in2)){
                newPack.push_back(pack->getPack().at(i));
            }
        }
        pack->setPack(newPack);

    }
    else{
        vector<Item> newIn;
        for(int i=0;i<inventory.size();i++){
            if(inventory.at(i).getName()==item1->getName()){
                continue;
            }
            newIn.push_back(inventory.at(i));
        }
        newIn.push_back(*item2);

        inventory=newIn;



        newIn.clear();
        int maxtime=0;
        for(int i=0;i<pack->getPack().size();i++){
            if(pack->getPack().at(i).getName()==i2&&maxtime<1){
                maxtime++;
                continue;
            }
            newIn.push_back(pack->getPack().at(i));
        }
        newIn.push_back(*item1);
        pack->setItems(newIn);

    }//b g y b e d a d a

    cout<<"Succeed changing items!"<<endl;
    this->updateState();
}

//void increaseStates(int,int,int);
void Player::changeRoom(Room* newRoom){
    this->setPreviousRoom(this->getCurrentRoom());
    this->setCurrentRoom(newRoom);
    if(newRoom->getIndex()==0){
        this->setPreviousRoom(newRoom);
    }
}

void Player::setTotalAtk(int n){totalAtk=n;}
void Player::setTotalDef(int n){totalDef=n;}
void Player::setCurrentRoom(Room* curR) { currentRoom = curR;}
void Player::setPreviousRoom(Room* prevR) { previousRoom = prevR; }
void Player::setSkills(vector<Skill> newthing){skills=newthing;}
void Player::setInventory(vector<Item> n){inventory=n;}

Room* Player::getCurrentRoom() { return currentRoom; }
Room* Player::getPreviousRoom() { return previousRoom; }
vector<Skill> Player::getSkills(){return skills;}

void Player::showInventory() {
    //    int count = 0;

    char num='A';

    cout<<num<<": ";
    cout<<setiosflags(ios::left) << setw(12) <<"Head: ";
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        if(it->getTag()=="head"){
            cout << setiosflags(ios::left) << setw(15)<< it->getName();
            cout<<" def: "<<it->getDefense()<<" hp: "<<it->getCurHealth()<<" / "<<it->getMaxHealth();
            break;
        }
    }
    num++;
    cout<<endl;

    cout<<num<<": ";
    cout<<setiosflags(ios::left) << setw(12)<<"Body: ";
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        if(it->getTag()=="body"){
             cout << setiosflags(ios::left) << setw(15) << it->getName();
             cout<<" def: "<<it->getDefense()<<" hp: "<<it->getCurHealth()<<" / "<<it->getMaxHealth();
            break;
        }
    }
    num++;
    cout<<endl;

    cout<<num<<": ";
    cout<<setiosflags(ios::left) << setw(12)<<"Left hand: ";
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        if(it->getTag()=="left"){
            cout << setiosflags(ios::left) << setw(15)<< it->getName();
            cout<<" def: "<<it->getDefense()<<" hp: "<<it->getCurHealth()<<" / "<<it->getMaxHealth();
            break;
        }
    }
    num++;
    cout<<endl;

    cout<<num<<": ";
    cout<<setiosflags(ios::left) << setw(12)<<"Right hand: ";
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        if(it->getTag()=="right"){
             cout << setiosflags(ios::left) << setw(15) << it->getName();
             cout<<" atk: "<<it->getAttack()<<" hp: "<<it->getCurHealth()<<" / "<<it->getMaxHealth();
            break;
        }
    }
    cout<<endl;

}
void Player::showSkills(){
    char num='A';

    if(skills.empty()){
        cout<<"You have no skill!"<<endl;
        return ;
    }

    for(auto it=skills.begin();it!=skills.end();it++){
        cout<<num<<": ";
        cout << setiosflags(ios::left) << setw(15)<<it->getSkillName();
        if(it->getSkillTag()=="heal"){
            cout<<" hp: "<<it->getSkillDamage();
        }
        else{
            cout<<" atk: "<<it->getSkillDamage();
        }

        cout<<" sp: "<<it->getSkillSp()<<endl;
        num++;
    }
}
void Player::showState(){
    cout<<"\nName: "<<getName()
        <<"\nHealth: "<<getCurrentHealth()<<" / "<<this->getMaxHealth()
        <<"\nSp: "<<getSp()
        <<"\nAtk: "<<getTotalAtk()
        <<"\nDef: "<<getTotalDef();

    cout<<endl;

    cout<<"\nInventories:\n";
    showInventory();

    cout<<"\nMy skills:\n";
    showSkills();

    cout<<endl;
}

void Player::updateState(){
    updateTTA();
    updateTTD();
}
void Player::updateTTA(){
    totalAtk=this->getAttack();

    for(auto it=inventory.begin();it!=inventory.end();it++){
        totalAtk+=it->getAttack();
    }
}
void Player::updateTTD(){
    totalDef=this->getDefense();

    for(auto it=inventory.begin();it!=inventory.end();it++){
        totalDef+=it->getDefense();
    }
}

void Player::takeDamage(int damage) {
    int true_damage = damage - totalDef;

    if(true_damage<=0)   true_damage=1;

    setCurrentHealth(getCurrentHealth()-true_damage);
}

void Player::setVar(int n){var=n;}
int Player::getVar(){return var;}
