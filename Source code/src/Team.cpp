#include "Team.h"
#include <sstream>
#include <iostream>
using namespace std;

Team::Team(){

}

Team::~Team(){
    for(int i=0;i<heros.size();i++){
        delete heros[i];
    }
    heros.clear();
}

//CONCTRUCTEUR DE COPIE DE TEAM
Team::Team(const Team& other){
    this->color = other.color;
    for(int i=0; i<other.heros.size();i++){
        heros.push_back(other.heros[i]->clone());
    }
}

Team& Team::operator=(const Team& rhs){ //OPERATEUR D'AFFECTATION
    if(this == &rhs) return *this;

    for(int i=0;i<heros.size();i++){
        delete heros[i];
    }
    heros.clear();

    this->color = rhs.color;

    for(int i=0; i<rhs.heros.size();i++){
        heros.push_back(rhs.heros[i]->clone());
    }

    return *this;
}

void Team::addHero(Hero* r){//Ahouter un héro
    heros.push_back(r->clone());
}

void Team::removeHero(Hero& r){//Supprimer un héro
    for(int i=0; i<heros.size();i++){
        if(*heros[i]==r){
            Hero* tmp=*(heros.begin()+i);
            heros.erase(heros.begin()+i);
            delete tmp;
            return;
        }
    }
}

string Team::str()const{
    stringstream result;

    result  <<"Heros: "<<endl;
    for(int i=0;i<heros.size();i++){
        result <<heros.at(i)->str()<<endl;
    }

    return result.str();
}

void Team::setColor(sf::Color c){
    color = c;
}

//Renvoie le premier hero uniquement
vector<Hero*> Team::getHero()const{
    return heros;
}
Hero* Team::getHeroByIndex(int i)const{//Obtenir hero par son index
    return heros[i];
}
sf::Color Team::getColor()const{
    return color;
}
int Team::getSizeHeroList()const{
    return heros.size();
}
