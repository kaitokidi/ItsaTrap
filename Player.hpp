#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Dir.hpp"
 
class Player : public sf::Drawable {

public:

	int getwins();
	void incwins();
	void tornaInici();
	void incSpriteSourceX();
	sf::Vector2f getPosition();
	void setSpriteSourceY(int y);
	sf::Vector2i getSpriteSize();
	sf::Vector2i getSpriteSource();
	void move(Dir mov, float dTime);
	void setSpriteSize(int x, int y);
	void setPosition(float x, float y);
	void setSpriteSource(int x, int y);
	Player(std::string name, int amplada, int altura, sf::Vector2f posIni);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(sprite, states);
    }

private:

	int SPRITE_WIDTH = 64;
	int SPRITE_HEIGHT = 128;

	sf::Vector2f position;
	sf::Vector2f positionInicial;
	sf::Vector2i spriteSource;
	sf::Vector2i spriteSize;

	sf::Sprite sprite;
	sf::Texture texture;

	static const int SPEED = 25;
	static const int maxCont = 10;
	int xcont;
	int wins;

};

#endif // _PLAYER_HPP_
