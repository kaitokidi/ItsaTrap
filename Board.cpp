#include "Board.hpp"
#include <iostream>
#include "Dir.hpp"

Board::Board(std::istream& in, int player_id) {
    std::string filetexture;
    in >> filetexture;
    sf::Image image;
    image.loadFromFile(filetexture);
    texture.loadFromImage(image);
    bg = new sf::Sprite();
    bg->setTexture(texture);
    int x, y, w, h;
    in >> x >> y >> w >> h;
    bg->setTextureRect(sf::IntRect(x, y, w, h));
box = sf::RectangleShape(sf::Vector2f(2,2));
    tilesize = sf::Vector2f(w, h);

    wall = new sf::Sprite();
    wall->setTexture(texture);
    in >> x >> y >> w >> h;
    wall->setTextureRect(sf::IntRect(x, y, w, h));
    wall->setOrigin(0, h);

    in >> _nb_players;
    players = std::vector<Player*>(_nb_players);
    for (int i = 0; i < _nb_players; ++i) {
        std::string texname; int pw, ph, px, py;
        in >> texname >> pw >> ph >> px >> py;
        ptilesize.x = pw;
        ptilesize.y = ph;
        players[i] = new Player(texname, pw, ph, sf::Vector2f(tilesize.x*px, tilesize.y*(py+1)));
    }

    traps = std::vector<sf::Sprite*>(_nb_players);
    for (int i = 0; i < _nb_players; ++i) {
        traps[i] =  new sf::Sprite();
        traps[i]->setTexture(texture);
        in >> x >> y >> w >> h;
        traps[i]->setTextureRect(sf::IntRect(x, y, w, h));
        traps[i]->setOrigin(0, h);
    }
    in >> _width >> _height;

    tilemap = std::vector< std::vector<int> >(_height, std::vector<int>(_width));
    for (int i = 0; i < _height; ++i) for (int j = 0; j < _width; ++j) in >> tilemap[i][j];

    this_player = player_id;
}

Dir invers(Dir d){
    switch (d) {
        case None : return None;
        case Up : return Down;
        case Down : return Up;
        case Left : return Right;
        case Right : return Left;
    }
    return None;
}

int Board::update(std::vector<Dir> movements, float dTime) {
		std::cout << "strt update" << std::endl;
    //                  0,0             0,-1           1,0              1,-1 
//     float delayY[] = { 0,           1*ptilesize.y/3,     0,         1*ptilesize.y/3};
//     float delayX[] = { ptilesize.x/3, ptilesize.x/3, 2*ptilesize.x/3, 2*ptilesize.x/3};

// 	float delayY[] = { 0,           1*ptilesize.y/2,     0,         1*ptilesize.y/2};
//     float delayX[] = { 0, ptilesize.x/2, 2*ptilesize.x/2, 2*ptilesize.x/2};

	sf::Vector2f size ((float)(players[1]->getSpriteSize()).x, (float)(players[1]->getSpriteSize()).y);
    float delayX[] = { size.x/3, 2*size.x/3, size.x/3,     2*size.x/3 };
    float delayY[] = { 0*size.y/4, 0*size.y/4, -1*size.y/4, -1*size.y/4 };

    for(int i = 0; i < _nb_players; ++i) players[i]->move(movements[i], dTime);
 
    for(int i = 0; i < _nb_players; ++i) {
        sf::Vector2f pos = players[i]->getPosition();
        bool diepotato = false;
		std::cout << "equis" << delayX[2]<<" nd "<< delayY[3]<< std::endl;
// 		box = sf::RectangleShape(sf::Vector2f(-1*delayX[2], delayY[3]));
				box = sf::RectangleShape(sf::Vector2f(10,10));
		box.setPosition(sf::Vector2f(pos.x, pos.y));
		box.setFillColor(sf::Color::Red);
		std::cout << "cu" << std::endl;

		
		for(int y = 0; y < tilemap.size(); ++y){
			for(int x = 0; x < tilemap[0].size(); ++x){
				std::cout << tilemap[y][x];
			}
			std::cout << std::endl;
		}

		
        for (int k = 0; k < 4; ++k) {
//  			std::cout << k << "[" << (int)((pos.y+delayY[k])/tilesize.y) << ","<< (int)((pos.x+delayX[k])/tilesize.x) << "]" << std::endl;
            int  tiletype = tilemap[(int)((pos.y+delayY[k])/tilesize.y)][((int)((pos.x+delayX[k])/tilesize.x))];
            if(tiletype == -2) {
                players[i]->move(invers(movements[i]), dTime);
                players[i]->move(invers(movements[i]), dTime);
                diepotato = false;
                break;
            }
            if( tiletype >= 0) diepotato = true;
        }

        if (diepotato) players[i]->tornaInici();

        if(i == 0 and pos.x >= 17*tilesize.x) {
            players[0]->incwins();
            players[0]->tornaInici();
            players[1]->tornaInici();
        }
        if(i == 1 and pos.x == tilesize.x ) {
            players[1]->incwins();
            players[0]->tornaInici();
            players[1]->tornaInici();
        }
    }
    std::cout << "end update" << std::endl;
}


void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    	std::cout << "start drawing" << std::endl;
	sf::Vector2f realtilesize = sf::Vector2f(target.getSize().x /1./_width, target.getSize().y /1./_height);
    states.transform.scale(realtilesize.x/tilesize.x, realtilesize.y/tilesize.y);

    for(int i = 0; i < _width; ++i) for (int j = 0; j < _height; ++j) {
        bg->setPosition(tilesize.x*i, tilesize.y*j);
        target.draw(*bg, states);
    }

    for(int i = 0; i < _height; ++i) for (int j = 0; j < _width; ++j) {
        sf::Sprite* todraw;
        if (tilemap[i][j] == -2) todraw = wall;
        else if (tilemap[i][j] == this_player) todraw = traps[this_player];
        else continue;
        todraw->setPosition(tilesize.x*j, tilesize.y*(i+1));
        target.draw(*todraw, states);
    }

    for (int i = 0; i < _nb_players; ++i) {
        target.draw(*players[i], states);
    }

    for(int i = 0; i < _nb_players; ++i){
            if(players[i]->getwins() >= 3){
                sf::Sprite s;
                sf::Texture t;
                if(i == 0)t.loadFromFile("png/noiwin.png");
                if(i == 1)t.loadFromFile("png/noiawin.png");
                s.setTexture(t);
                s.setScale(0.6,0.6);
                target.draw(s);
            }
	}
	
	target.draw(box);
	std::cout << "enddraw" << std::endl;
}
