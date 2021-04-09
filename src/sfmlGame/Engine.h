#ifndef ENGINE_H
#define ENGINE_H

#include "Board.h"
#include <iostream>
#include "Parametre.h"

class Engine
{
public :
	
	Engine();
	void run();
	void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);
	bool isInside(void) const;

private :
	
	void processEvents();
	void update();
	void render();
	
private :
	sf::RenderWindow m_window;
	static const sf::Time m_timePerFrame;
	bool MouseL=false, MouseR=false, Echap=false, MouseRPressed = false, MouseLPressed = true;
    bool Left=false, Right=false, Up=false, Space=false, Down=false;
    bool SpacePressed=false, UpPressed=false, DownPressed=false, LeftPressed=false, RightPressed=false;

	char m_pieceChoisie;
	sf::Vector2i m_coordPieceChoisie;
	Board m_board;
	sf::Texture texture;
	sf::Sprite ma_piece;
	std::string directory = "assets/";
	std::string color;
	std::string ext = ".png";
	std::string path;
};

#endif //ENGINE_H
