#ifndef TILEMAP _H
#define TILEMAP _H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class TileMapView : public sf::Drawable, public sf::Transformable
{
public:
    TileMapView();
    virtual ~TileMapView();
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int row, unsigned int col);



private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    int arrayLevel[18][32];
};

#endif // TILEMAP _H
