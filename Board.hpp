#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <istream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Dir.hpp"
#include "Player.hpp"

class Board : public sf::Drawable {

private:
    int _width, _height;
    std::vector< std::vector<int> > tilemap;
    sf::Vector2f tilesize;
    sf::Vector2f ptilesize;

    int _nb_players;
    std::vector<Player*> players;
    int this_player;

    sf::Texture texture;

	sf::RectangleShape box;
	
    sf::Sprite* bg;
    sf::Sprite* wall;
    std::vector<sf::Sprite*> traps;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Board(std::istream& in, int player_id);

    int update(std::vector<Dir> movements, float dTime);

};

#endif // _BOARD_HPP_
