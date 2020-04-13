#include "Battle.h"
#include <SFML/Graphics.hpp>
#include "DisplayedObject.h"
#include "TileMapView.h"
#include <math.h>
#include "Warrior.h"
#include "Hud.h"

const int FPS = 30; // Nombre d'images par seconde
const int resolutionX = 1280;
const int resolutionY = 720;
const int nbTileW = 32; //Nombre de case en X
const int nbTileH = 18; //Nombre de case en Y
bool isSpriteSelected = false; //Est ce que un personange est selectionné
int index = 0; //Index du personange selectionné
Spell* spell =0; //Sort préparé

sf::RenderTexture mapRender;
sf::Texture textureGrid;
sf::Sprite mapSprite;
sf::Sprite gridSprite;
sf::ConvexShape convex;
Hud hud;

Battle::Battle()
{
    teamBlue.setColor(sf::Color::Blue);
    teamRed.setColor(sf::Color::Red);
}

Battle::~Battle()
{
    //dtor
}
void Battle::play(sf::RenderWindow& window, vector<Hero*> heros)
{//Permet de jouer une partie
    buildBattle(heros);
    stateTeam = sf::Color::Blue;

    //Tant que la fenetre est ouverte ou qu'il y a encore un héros dans chaque équipe
    //La partie continue
    while (window.isOpen() && checkEndGame()==true) {
        if (stateTeam == sf::Color::Blue) {
            currentTeam = &teamBlue;
        }
        else {
            currentTeam = &teamRed;
        }
        // on g�re les �v�nements
        sf::Event event;
        drawMap(window);
        //En fonction de la touche appuyée, appelle une méthode pour effectuer une action
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                cout << "Close";
            }
            if (!isSpriteSelected) {//Si un personnage est sélectionee
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    nextRound();//Tour suivant
                }
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    index = selectHero(event, currentTeam);//Selectionne un hero (Retourne -1 si pas de héro)
                    if(index == -1){
                        isSpriteSelected = false;
                    }else{//Change le visuel du héro
                        isSpriteSelected = true;
                        currentTeam->getHeroByIndex(index)->getSprite().scale(1.1f, 1.1f);
                        currentTeam->getHeroByIndex(index)->getSprite().setColor(sf::Color(255, 255, 255, 128));
                        hud.DisplayInfoHero(*currentTeam->getHeroByIndex(index), currentTeam->getColor());
                    }
                }
            }
            else {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    deselectHero();//Déselectionne le héro
                    nextRound();//Tour suivant
                }
                else if (event.type == sf::Event::KeyPressed) {
                    spell=prepareSpell(event);//Prépare un sort
                }
                else if (event.type == sf::Event::MouseButtonReleased && spell != 0) {
                    if(!currentTeam->getHeroByIndex(index)->getAlreadyPlayed()){
                        castSpell(event, spell);//Lance un sort
                        hud.DisplayInfoHero(*currentTeam->getHeroByIndex(index), currentTeam->getColor());//Affiche l'hud
                    }
                    deselectHero();//Déselectionne le héro
                    spell =0;//Pas de sort selectionné
                }
                else if (event.type == sf::Event::MouseButtonReleased && spell == 0) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        moveHero(event);//Bouger le héro
                        hud.DisplayInfoHero(*currentTeam->getHeroByIndex(index), currentTeam->getColor());//Affiche l'hud
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        deselectHero();//Déselectionne le héro
                    }
                }
            }
        }
    }
}
void Battle::buildBattle(vector<Hero*> heros){//Construit la carte et l'affiche
    // on définit le niveau à l'aide de numéro de tuiles
    const int levelFloor[] = {
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 92,  47,  47,  47,  93,  307, 307, 92,  47,  47,  47,  93,  307, 307, 92,  47,  47,  47,  47,  93,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 46,  0,   0,   0,   0,   47,  47,  0,   0,   0,   0,   44,  82,  82,  46,  0,   0,   0,   0,   44,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 46,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 307, 91,  136, 136, 136, 136, 90,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 46,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 307, 217, 217, 83,  217, 217, 217, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 91,  136, 0,   0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 307, 239, 239, 83,  239, 239, 239, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 217, 217, 46,  0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 307, 307, 307, 83,  307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 239, 239, 46,  0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 92,  47,  47,  47,  47,  47,  93,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 46,  0,   0,   0,   0,   0,   0,   0,   0,   44,  307, 46,  0,   0,   0,   0,   0,   44,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 91,  136, 0,   0,   0,   0,   0,   0,   0,   44,  82,  46,  0,   0,   0,   0,   0,   44,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 217, 217, 136, 136, 136, 136, 136, 136, 136, 90,  307, 91,  136, 136, 136, 136, 136, 90,  307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 239, 239, 217, 217, 217, 217, 217, 217, 217, 217, 307, 217, 217, 217, 217, 217, 217, 217, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 239, 239, 239, 239, 239, 239, 239, 239, 307, 239, 239, 239, 239, 239, 239, 239, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307
};
    // on crée la tilemap avec le niveau précédemment défini
    TileMapView mapFloor;
    mapFloor.load("assets/tiles/mitchell-32-1024x576.png", sf::Vector2u(32, 32), levelFloor, 18, 32);

    const int levelObject[] = {
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 60,  307, 307, 61,  307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 62,  307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 84,  307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 60,  307, 61,  307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307
    };
    TileMapView mapObject;
    //Charge la texture de la map
    mapObject.load("assets/tiles/mitchell-32-1024x576.png", sf::Vector2u(32, 32), levelObject, 18, 32);
    //Charge la texture de la grille
    textureGrid.loadFromFile("assets/tiles/grid-40.png", sf::IntRect(0, 0, 1280, 720));

    gridSprite.setTexture(textureGrid);


    mapRender.create(1024, 576); //Crée un rendu de résolution 1024 sur 576
    mapRender.draw(mapFloor);   //Dessine le sol de la carte dans ce rendu
    mapRender.draw(mapObject);  //Dessine les objets de la carte dans ce rendu
    mapRender.display();

    mapSprite.setTexture(mapRender.getTexture());
    sf::Vector2f targetSize(resolutionX, resolutionY);
    mapSprite.setScale(targetSize.x / mapSprite.getLocalBounds().width,targetSize.y / mapSprite.getLocalBounds().height);

    //Ajoute les héros dans leur équipe et les place sur le plateau
    for(int i=0; i<heros.size()/2; i++){
        teamBlue.addHero(heros[i]);
        teamBlue.getHeroByIndex(i)->load("assets/sprites/"+heros[i]->getName()+".png");
        teamBlue.getHeroByIndex(i)->setPosition(460+i*200,500);
    }
    for(int i=0; i<heros.size()/2; i++){
        teamRed.addHero(heros[i+heros.size()/2]);
        teamRed.getHeroByIndex(i)->load("assets/sprites/"+heros[i+heros.size()/2]->getName()+".png");
        teamRed.getHeroByIndex(i)->setPosition(460+i*200,300);
    }

}
void Battle::drawMap(sf::RenderWindow& window)//Désinne la map
{
    // on dessine le niveau
    window.clear();
    window.draw(mapSprite);
    window.draw(gridSprite);
    window.draw(convex);
    hud.draw(window);
    for (int i = 0; i < teamBlue.getHero().size(); i++) {//Déssine le héros ainsi que sa barre de pv
        teamBlue.getHeroByIndex(i)->setHpBar(teamBlue.getColor(), teamBlue.getHeroByIndex(i)->getHp(), teamBlue.getHeroByIndex(i)->getCHp());
        teamBlue.getHeroByIndex(i)->draw(window);
    }
    for (int i = 0; i < teamRed.getHero().size(); i++) {//Déssine le héros ainsi que sa barre de pv
        teamRed.getHeroByIndex(i)->setHpBar(teamRed.getColor(), teamRed.getHeroByIndex(i)->getHp(), teamRed.getHeroByIndex(i)->getCHp());
        teamRed.getHeroByIndex(i)->draw(window);
    };
    sf::Text text;//Affiche l'annonce central
    if(currentTeam->getColor()==sf::Color::Blue){
        text.setString("               Team blue \n(Press enter to finish your turn)");
        text.setColor(sf::Color::Blue);
    }else if(currentTeam->getColor()==sf::Color::Red){
        text.setString("               Team red \n(Press enter to finish your turn)");
        text.setColor(sf::Color::Red);
    }
    text.setPosition(sf::Vector2f(window.getSize().x/2, 5));
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,0);
    window.draw(text);
    window.display();
}
void Battle::nextRound()//Passe au tour suivant
{
    Hero* hero;
    //Reset les persos pour le prochain tour
    for (int i=0; i < currentTeam->getHero().size(); i++) {
        hero = currentTeam->getHeroByIndex(i);
        hero->resetCMovement();
        hero->setAlreadyPlayed(false);
    }
    if (stateTeam == sf::Color::Blue) {//Si l'équipe bleu jouait, passe au tour de l'équipe rouge
        currentTeam = &teamRed;
        stateTeam = sf::Color::Red;
        cout << "A Team rouge de jouer" << endl;
    }
    else {//L'inverse
        currentTeam = &teamBlue;
        stateTeam = sf::Color::Blue;
        cout << "A Team bleu de jouer" << endl;
    }
}
int Battle::selectHero(sf::Event event, Team* team)//Permet de sélectionner un héro sur le plateau
{
    Hero* hero;
    int x(event.mouseButton.x);//Position x de la souris
    int y(event.mouseButton.y);//Position y de la souris

    //Pour chaque héro, on vérifie si la position de la souris est sur son sprite
    for (int i = 0; i < currentTeam->getHero().size(); i++) {
        hero = team->getHeroByIndex(i);
        if (hero->getSprite().getGlobalBounds().contains(x, y)) {
            return i;//Si oui retorune l'index de ce héro
        }
    }
    return -1;
}
void Battle::deselectHero()//Déselectionne un héro.
{//Change le visuel
    Hero* hero = currentTeam->getHeroByIndex(index);
    hero->getSprite().scale(1.0f / 1.1f, 1.0f / 1.1f);
    hero->getSprite().setColor(sf::Color(255, 255, 255, 255));
    isSpriteSelected = false;
}
void Battle::moveHero(sf::Event event)//Bouger le héro
{
    bool test=true;
    Hero* hero = currentTeam->getHeroByIndex(index);
    int x2(event.mouseButton.x);//Position x de la souris
    int y2(event.mouseButton.y);//Position y de la souris
    int x3 = x2 / (resolutionX / nbTileW) * 40 + 20;//permet de recentrer la position du clic au centre de la case sélectionnée
    int y3 = y2 / (resolutionY / nbTileH) * 40 + 20;//Et de récuperer les coordonnées de la case
    //Vérife si la case est occupée en vérifiant tout les sprites de chaque héro
    for(int i=0; i<teamBlue.getHero().size();i++){
        if((teamBlue.getHeroByIndex(i)->getX() == x3 && teamBlue.getHeroByIndex(i)->getY() == y3)){
            test=false;
            cout<<"Case occupée"<<endl;
        }
    }
    for(int i=0; i<teamRed.getHero().size();i++){
        if((teamRed.getHeroByIndex(i)->getX() == x3 && teamRed.getHeroByIndex(i)->getY() == y3)){
            test=false;
            cout<<"Case occupée"<<endl;
        }
    }//Si c'est pas occupé
    if(test){
       if (hero->movePossible(x3, y3)) {//Bouge le héro et change son visuel
        hero->setPosition(x3, y3);
        hero->getSprite().scale(1.0f / 1.1f, 1.0f / 1.1f);
        hero->getSprite().setColor(sf::Color(255, 255, 255, 255));

        isSpriteSelected = false;
        }
    }
}
Spell* Battle::prepareSpell(sf::Event event)//Prépare un sort
{
    Hero* hero = currentTeam->getHeroByIndex(index);
    int i;
    switch (event.key.code) {//En fonction de la touche, selectionne le bon sort et le return
        case (sf::Keyboard::Num1):
            cout << "Sort 1" << endl;
            return hero->getSpell(0);
            break;
        case (sf::Keyboard::Num2):
            cout << "Sort 2" << endl;
            return hero->getSpell(1);
            break;
        case (sf::Keyboard::Num3):
            cout << "Sort 3" << endl;
            return hero->getSpell(2);
            break;
        case (sf::Keyboard::Num4):
            cout << "Sort 4" << endl;
            return hero->getSpell(3);
            break;
        default:
            break;
    }
}
void Battle::castSpell(sf::Event event, Spell* spell){//Utilise le sort
    Hero* hero = currentTeam->getHeroByIndex(index);
    int ind =selectHero(event, &teamBlue);//récupère l'index du héro ciblé
    //Check son équipe et utilse le sort contre lui
    if(ind != -1){
        if(hero->castSpell(teamBlue.getHeroByIndex(ind),spell)){
            teamBlue.removeHero(*teamBlue.getHeroByIndex(ind));
        }
    }
    ind =selectHero(event, &teamRed);
    if(ind != -1){
        if(hero->castSpell(teamRed.getHeroByIndex(ind),spell)){
            teamRed.removeHero(*teamRed.getHeroByIndex(ind));
        }
    }
}

bool Battle::checkEndGame(){//Vérifie s'il reste un héro dans chaque équipe
    if(teamBlue.getSizeHeroList()>0 && teamRed.getSizeHeroList()>0){
       return true;
    }
    return false;
}
