#include "TileMapView.h"

TileMapView::TileMapView()
{
    //ctor
}

TileMapView::~TileMapView()
{
    //dtor
}
bool TileMapView::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int row, unsigned int col)
{
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    this->m_vertices.resize(col * row * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (int i = 0; i < col; ++i){
        for (int j = 0; j < row; ++j) {

            // on récupère le numéro de tuile courant
            int tileNumber = tiles[i + j * col];

            // on en déduit sa position dans la texture du tilesets
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x); //tu = colonne de la texture du fichier
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x); //tu = ligne de la texture du fichier

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * col) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}
void TileMapView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}
