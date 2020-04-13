#include "Hero.h"
#include <sstream>
#include <iostream>
#include <math.h>
using namespace std;

int Hero::compteur = 0;

Hero::Hero(string name,int hp,int movement){
    this->name = name;
    this->hp = hp;
    this->cHp = hp;
    this->movement = movement;
    this->cMovement = movement;
    this->alreadyPlayed=false;

    compteur++; //GENERATION DE L'ID UNIQUE
    id=new int;
    *id=compteur;
}

Hero::~Hero(){
    for(int i=0;i<spells.size();i++){ //LIBERATION DE LA MEMOIRE DES SORTS ET DE L'ID DU HERO
        delete spells[i];
    }
    spells.clear();
    delete id;
}

Hero::Hero(const Hero& other){ //Const de copie
    this->name = other.name;
    this->hp = other.hp;
    this->cHp = other.hp;
    this->movement = other.movement;
    this->cMovement = other.cMovement;
    this->alreadyPlayed=other.alreadyPlayed;;

    id = new int(*other.id);

    for(int i=0;i<other.spells.size();i++){
        addSpell(other.spells[i]);
    }
}

Hero& Hero::operator=(const Hero& rhs){//Opérateur d'afféctation
    if(this == &rhs) return *this;

    this->name = rhs.name;
    this->hp = rhs.hp;
    this->cHp = rhs.hp;
    this->movement = rhs.movement;
    this->cMovement = rhs.cMovement;
    this->alreadyPlayed = rhs.alreadyPlayed;

    for(int i=0;i<spells.size();i++){
        delete spells[i];
    }
    spells.clear();

    for(int i=0;i<rhs.spells.size();i++){
        addSpell(rhs.spells[i]);
    }

    delete id;
    id=new int (*rhs.id);

    return *this;
}

void Hero::addSpell(Spell* s){//Ajoute un sort à la liste de sort du personnage
    spells.push_back(s->clone());
}

string Hero::str()const{
    stringstream result;

    result  <<"ID: "<<*id<<endl
            <<"Name: "<<name<<endl
            <<"HP: "<<hp<<endl
            <<"Movement: "<<movement<<endl<<endl
            <<"Sorts: "<<endl;
    for(int i=0;i<spells.size();i++){
        result <<spells.at(i)->str()<<endl;
    }

    return result.str();
}

Hero* Hero::clone()const{
    return new Hero(*this);
}

bool Hero::operator==(const Hero& h) const{
    if(*id == *h.id){
        return true;
    }
    return false;
}

bool Hero::isRanged(int rangeX, int rangeY, int range){//Vérifie si le héro est à porté
    int testX = getX() - rangeX;
    int testY = getY() - rangeY;

    if (abs(testX) + abs(testY) <= range * 40) {
        return true;
    }
    return false;
}

bool Hero::castSpell(Hero* h, Spell* s){//Utilise un sort contre un personnage
    if(isRanged(h->getX(),h->getY(),s->getRange())){
        h->setCHp(h->getCHp()-s->getPower());
        if(h->getCHp()>h->getHp()){
            h->setCHp(h->getHp());cout<<h->getHp();
        }
        else if(h->getCHp()<=0){
            return true;
        }
      alreadyPlayed=true;
    }
    return false;
}

bool Hero::movePossible(int moveX, int moveY)//Bouge le personange
{
    int x = getX();
    int y = getY();

    int testX = x - moveX;
    int testY = y - moveY;
    if (abs(testX) + abs(testY) <= cMovement * 40 && getCMovement() > 0) {
        //Nombre déplacement effectue
        int nbMove=(abs(testX) + abs(testY)) / 40;
        setCMovement(getCMovement()-nbMove);
         if(testX < 0){
            if(testY == 0){
                cout<<"Deplacement a droite"<<endl;
                animSprite("DOWN_RIGHT");
            }
            else if(testY < 0){
                cout<<"Deplacement a droite/bas"<<endl;
                animSprite("DOWN_RIGHT");
            }else if(testY > 0){
                cout<<"Deplacement a droite/haut"<<endl;
                animSprite("UP_RIGHT");
            }
         }else if(testX > 0){
            if(testY == 0){
                cout<<"Deplacement a gauche"<<endl;
                animSprite("DOWN_LEFT");
            }
            else if(testY < 0){
                cout<<"Deplacement a gauche/bas"<<endl;
                animSprite("DOWN_LEFT");
            }else if(testY > 0){
                cout<<"Deplacement a gauche/haut"<<endl;
                animSprite("UP_LEFT");
            }
        }else if(testX == 0){
            if(testY < 0){
                cout<<"Deplacement en bas"<<endl;
                animSprite("DOWN");
            }
            else if(testY > 0){
                cout<<"Deplacement en haut"<<endl;
                animSprite("UP");
            }
        }
        setSpriteCurrent();
        return true;
    }
    else {
        cout << "Pas assez de point de deplacement" << endl;
        return false;
    }
}

//GETTERS ET SETTERS
string Hero::getName()const{
    return name;
}

int Hero::getHp()const{
    return hp;
}

void Hero::setHp(int newHp){
    hp=newHp;
}

int Hero::getCHp()const{
    return cHp;
}

void Hero::setCHp(int newHp){
    cHp=newHp;
}

int Hero::getMovement()const{
    return movement;
}

void Hero::setMovement(int newMovement){
    movement= newMovement;
}

int Hero::getCMovement()const{
    return cMovement;
}

void Hero::setCMovement(int newCMovement){
    cMovement= newCMovement;
}

void Hero::resetCMovement(){
    cMovement= movement;
}

Spell* Hero::getSpell(int numero)const{
    return spells[numero];
}

vector<Spell*>& Hero::getSpells() {
    return spells;
}
bool Hero::getAlreadyPlayed(){
    return alreadyPlayed;
}
void Hero::setAlreadyPlayed(bool play){
    alreadyPlayed=play;
}
