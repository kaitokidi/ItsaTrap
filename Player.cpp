#include <iostream>
#include "Player.hpp"

Player::Player(std::string name, int amplada, int altura, sf::Vector2f posIni){

    positionInicial = posIni; 
    SPRITE_WIDTH = amplada;
    SPRITE_HEIGHT = altura;
    xcont = 0;
    wins = 0;
	position = posIni;
	spriteSource = sf::Vector2i(0,0);
    spriteSize = sf::Vector2i(SPRITE_WIDTH, SPRITE_HEIGHT);
    sprite.setOrigin(0, SPRITE_HEIGHT);
    if(!texture.loadFromFile(name)){
        std::cout << "Filed at loading " << name << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
    sprite.setPosition(position);
}

void Player::move(Dir mov, float dTime){
    if (mov != None) {
    if(mov-1 == spriteSource.y) {
        position.x += Mx[mov]*SPEED;
        position.y += My[mov]*SPEED;
        if(mov != None)++xcont;
        if(xcont >= maxCont) {
            ++spriteSource.x;
            if(spriteSource.x >= 6) spriteSource.x = 0;
            xcont = 0;
        }
    }
    else spriteSource.y = mov-1;

    sprite.setPosition(position);
     sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
    }
}

void Player::incwins(){
    ++wins;
}

int Player::getwins(){
    return wins;
}

void Player::setPosition(float x, float y){
    position.x = x;
    position.y = y;
    sprite.setPosition(position);
}

void Player::setSpriteSource(int x, int y){
    spriteSource.x = x;
    spriteSource.y = y;
    sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
}

void Player::setSpriteSize(int x, int y){
    spriteSize.x = x;
    spriteSize.y = y;
    sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
}

sf::Vector2f Player::getPosition(){
    return position;
}

sf::Vector2i Player::getSpriteSource(){
    return spriteSource;
}

sf::Vector2i Player::getSpriteSize(){
    return spriteSize;
}

void Player::incSpriteSourceX(){
    ++spriteSource.x;
    sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
}

void Player::setSpriteSourceY(int y){
    spriteSource.y = y;
    sprite.setTextureRect(sf::IntRect(spriteSource.x*SPRITE_WIDTH,
        spriteSource.y*SPRITE_HEIGHT, spriteSize.x, spriteSize.y));
}

void Player::tornaInici(){
    position = positionInicial;
    sprite.setPosition(position);
}