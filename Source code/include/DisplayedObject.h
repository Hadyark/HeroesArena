#ifndef DISPLAYEDOBJECT_H
#define DISPLAYEDOBJECT_H
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class DisplayedObject {

private:
	sf::Texture m_textureDown;
	sf::Texture m_textureUp;
	std::string m_filename;
	sf::RectangleShape *hpBar;
	bool m_loaded;
	sf::Image spriteSheet;
	sf::Sprite* m_spriteCurrent;//Sprite actuel
	//Les différentes vues du sprite
	sf::Sprite m_spriteDownRight;
	sf::Sprite m_spriteDownLeft;
	sf::Sprite m_spriteUpLeft;
	sf::Sprite m_spriteUpRight;

	enum SpriteState {DOWN_RIGHT, DOWN_LEFT, UP_LEFT, UP_RIGHT};
    SpriteState stateOfSprite;

public:

	// X and Y location of the object
	float m_x;
	float m_y;

	DisplayedObject();
	virtual ~DisplayedObject();

	// Loads the object from a file
	virtual void load(std::string filename);

	// Draws the object
	virtual void draw(sf::RenderWindow &window);

	// Sets a new position of the object
	virtual void setPosition(float x, float y);

	virtual sf::Sprite& getSprite();
	virtual void setSpriteCurrent();
    virtual void animSprite(string newState);

	float getX();
    float getY();
    void setHpBar(sf::Color color, int hp, int cHp);
};


#endif // DISPLAYEDOBJECT_H
