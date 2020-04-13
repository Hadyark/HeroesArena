#include "DisplayedObject.h"

DisplayedObject::DisplayedObject()
    : m_loaded(true)
{
}

DisplayedObject::~DisplayedObject()
{
}

// Loads the displayed object if
// a valid filename is provided
void DisplayedObject::load(std::string filename)//Charge les sprites
{
    if (spriteSheet.loadFromFile(filename) == false) {
        m_loaded = false;
    }
    else {
        m_textureDown.loadFromImage(spriteSheet, sf::IntRect(205, 0, 102, 160));

        m_spriteDownLeft.setTexture(m_textureDown);
        m_spriteDownLeft.scale(0.5f, 0.5f);
        m_spriteDownLeft.setOrigin(51, 120);

        m_spriteDownRight.setTexture(m_textureDown);
        m_spriteDownRight.scale(-0.5f, 0.5f);
        m_spriteDownRight.setOrigin(51, 120);

        m_textureUp.loadFromImage(spriteSheet, sf::IntRect(402, 160, 110, 160));

        m_spriteUpLeft.setTexture(m_textureUp);
        m_spriteUpLeft.scale(0.5f, 0.5f);
        m_spriteUpLeft.setOrigin(51, 120);

        m_spriteUpRight.setTexture(m_textureUp);
        m_spriteUpRight.scale(-0.5f, 0.5f);
        m_spriteUpRight.setOrigin(51, 120);

        m_spriteCurrent = &m_spriteDownLeft;

        hpBar = new sf::RectangleShape(sf::Vector2f(30, 5));
        hpBar->setOrigin(15,-10);
        m_loaded = true;
    }
}

void DisplayedObject::draw(sf::RenderWindow& window)//Déssine le sprite utilisé actuellement
{
    if (m_loaded) {

        window.draw(*m_spriteCurrent);
        window.draw(*hpBar);
    }
}

void DisplayedObject::setPosition(float x, float y)//Modifié la position du sprite
{
    if (m_loaded) {
        m_x = x;
        m_y = y;
        getSprite().setPosition(x, y);
        hpBar->setPosition(x, y);
        hpBar->setFillColor(sf::Color::White);
    }
}

sf::Sprite& DisplayedObject::getSprite()
{
    return *m_spriteCurrent;
}

void DisplayedObject::setSpriteCurrent()//Modifie le sprite actuel
{

    switch (stateOfSprite) {
        case DisplayedObject::DOWN_LEFT: {
            m_spriteCurrent = &m_spriteDownLeft;
            break;
        }
        case DisplayedObject::DOWN_RIGHT: {
            m_spriteCurrent = &m_spriteDownRight;
            break;
        }
        case DisplayedObject::UP_LEFT: {
            m_spriteCurrent = &m_spriteUpLeft;
            break;
        }
        case DisplayedObject::UP_RIGHT: {
            m_spriteCurrent = &m_spriteUpRight;
            break;
        }
        default: {
            break;
        }
    }
}

void DisplayedObject::animSprite(string newState)//Change l'état du sprite actuel
{
    if (newState == "DOWN_LEFT") {
        DisplayedObject::stateOfSprite = DOWN_LEFT;
    }
    else if (newState == "DOWN_RIGHT") {
        DisplayedObject::stateOfSprite = DOWN_RIGHT;
    }
    else if (newState == "UP_LEFT") {
        DisplayedObject::stateOfSprite = UP_LEFT;
    }
    else if (newState == "UP_RIGHT") {
        DisplayedObject::stateOfSprite = UP_RIGHT;
    }
    else if (newState == "UP" && DisplayedObject::stateOfSprite == UP_RIGHT) {
        DisplayedObject::stateOfSprite = UP_RIGHT;
    }
    else if (newState == "UP" && DisplayedObject::stateOfSprite == UP_LEFT) {
        DisplayedObject::stateOfSprite = UP_LEFT;
    }
    else if (newState == "DOWN" && DisplayedObject::stateOfSprite == DOWN_RIGHT) {
        DisplayedObject::stateOfSprite = DOWN_RIGHT;
    }
    else if (newState == "DOWN" && DisplayedObject::stateOfSprite == DOWN_LEFT) {
        DisplayedObject::stateOfSprite = DOWN_LEFT;
    }
}

float DisplayedObject::getX()
{
    return m_x;
}

float DisplayedObject::getY()
{
    return m_y;
}
void DisplayedObject::setHpBar(sf::Color color, int hp, int cHp)//Modife la visuel de la barre de pv
{
    hpBar->setFillColor(color);
    hpBar->setSize(sf::Vector2f(30*cHp/hp, 5));
}
