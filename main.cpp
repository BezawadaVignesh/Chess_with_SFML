#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <typeinfo>
#include <iostream>

#include "settings.hpp"
#include "chess.hpp"



class Game{
	private:
		sf::RenderWindow window;
		Chess* chess = new Chess();
		enum{
			HOME,
			PLAYING
		} state;
	public:
	Game(){	
		state = HOME;
	}
	~Game(){	
    delete chess;
	}
	int run(){
		window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chess");
		window.setFramerateLimit(60);
        sf::RectangleShape button = sf::RectangleShape({300.0f,75.0f});
		button.setFillColor(sf::Color(255,0,0));
		while (window.isOpen())
		{
			// clear the window with white color
			window.clear(sf::Color::White);
			// check all the window's events that were triggered since the last iteration of the loop
			if(state == HOME){
			sf::Event event;
			window.draw(button);
			if (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				switch(event.type){
					case sf::Event::Closed :
					window.close();
					break;
					case sf::Event::MouseButtonReleased:
						sf::Vector2i pos = sf::Mouse::getPosition(window);
						std::cout<<pos.x<<" "<<pos.y<<"\n";
						//if(button.getPosition())
						state = PLAYING;
						chess->resetBoard();
				}
			}
            
			
			}else if(state == PLAYING)
				if(chess->run(window)) state = HOME;
			// end the current frame
			window.display();
		}
		return EXIT_SUCCESS;
	}
	
};


int main()
{
	Game game;

	return game.run();
}
