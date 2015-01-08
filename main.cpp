#include <iostream>
#include <fstream>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>
#include "Board.hpp"
#include "Dir.hpp"
#include "Socket.hpp"


int main(int argc, char *argv[]){
	sf::RenderWindow window (sf::VideoMode(1300,700), "It's a Trap!");

    char s;
	if(argc >= 2){
		s = *(argv[1]);
	} else {
		std::cout << "Need argument for first or second player" << std::endl;
	}
	Socket sock(s);
	while(! sock.connect()){
		std::cout << " No em conecto : ( " << std::endl;
	}

	sf::Music music;
	if (!music.openFromFile("Edward_Shallow_-_02_-_Fractal_Crook.ogg")) std::cout << " no puc carregar la musica " << std::endl;
	music.play();
	music.setPitch(1);
    music.setVolume(50);
	music.setLoop(true);

	// examplemap.txt
	//map2.txt
	std::ifstream in("map7.txt");
	Board board(in, s != 'S');

	std::vector<Dir> directions(2);

	float deltatime = 0;
	board.update(directions, deltatime);
	sf::Clock deltaClock;

	sf::Keyboard::Key up, down, left, right;

	if (s == 'S') {
		up = sf::Keyboard::Up;
		down = sf::Keyboard::Down;
		left = sf::Keyboard::Left;
		right = sf::Keyboard::Right;
	} else {
		up = sf::Keyboard::W;
		down = sf::Keyboard::S;
		left = sf::Keyboard::A;
		right = sf::Keyboard::D;
	}

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			switch (event.type) {
				case sf::Event::Closed :
					window.close();
					break;
				default:
					break;
			}
		}
			char data[1];
		Dir direction = None;
		if(sf::Keyboard::isKeyPressed(up)){
			direction = Up;
		}
		else if(sf::Keyboard::isKeyPressed(down)){
			direction = Down;
		}
		else if(sf::Keyboard::isKeyPressed(right)){
			direction = Right;
		}
		else if(sf::Keyboard::isKeyPressed(left)){
			direction = Left;
		}

		std::vector<Dir> directions(2);
		if(s == 'S') {

			if(! sock.recieve(data, sizeof(char),0)){
				std::cout << "no rebo be : ( " << std::endl;
			}//else  std::cout << "soc server i rebo " << (int)(data[0]) << std::endl;
			directions[1] = Dir(data[0]);
			data[0] = direction;
			//std::cout << "soc server i envio " << (int)(data[0]) << std::endl;
			
			if(! sock.send(data, sizeof(char),0)){
				std::cout << "no envio be : ( " << std::endl;
			}/*sida*/
//			directions[1] = Dir(data[0]);
			directions[0] = direction;
		}else {	

			data[0] = direction;
			if(! sock.send(data, sizeof(char),1)){
				std::cout << "no envio be : ( " << std::endl;
			}//else std::cout << "soc client i he enviat " << (int)(data[0]) << std::endl;
			directions[1] = direction;
			
			if(! sock.recieve(data, sizeof(char),1)){
				std::cout << "no rebo be : ( " << std::endl;
			}//else std::cout << "soc el client he rebut " << (int)(data[0]) << std::endl;
			directions[0] = Dir (data[0]);
		} 
		deltatime = deltaClock.restart().asSeconds();
		//std::cout << "directions " << directions[0] << " " << directions[1] << std::endl;
		board.update(directions, deltatime);
// 	std::cout << "1" << std::endl;
		window.clear();
// 			std::cout << "2" << std::endl;
		window.draw(board);
// 			std::cout << "3" << std::endl;
		window.display();
// 			std::cout << "4" << std::endl;

	}
}
