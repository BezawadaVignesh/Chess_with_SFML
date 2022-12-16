//C:\Users\Lokanadh\Desktop\compiler\mingw64\bin\g++ -c C:\Users\Lokanadh\Desktop\compiler\mingw64\bin\main.cpp -IC:\Users\Lokanadh\Desktop\compiler\SFML-2.5.1\include -DSFML_STATIC
//C:\Users\Lokanadh\Desktop\compiler\mingw64\bin\g++ C:\Users\Lokanadh\Desktop\compiler\mingw64\bin\main.o -o C:\Users\Lokanadh\Desktop\compiler\mingw64\bin\main -LC:\Users\Lokanadh\Desktop\compiler\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <typeinfo>
#include <iostream>

#include "settings.h"
#include "chess.hpp"


class Game{
	private:
		sf::RenderWindow window;
		Chess* chess = new Chess();
	public:
	Game(){	
	}
	~Game(){	
    delete chess;
	}
	int run(){
		window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Window");
		window.setFramerateLimit(60);
        
		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			/*if (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				switch(event.type){
					case sf::Event::Closed :
					window.close();
					break;
				}
			}
            */
			// clear the window with black color
			//window.clear(sf::Color::Black);
			chess->run(window);
			// end the current frame
			window.display();
		}
		return 0;
	}
	
};


int main()
{
	Game game;

	return game.run();
}