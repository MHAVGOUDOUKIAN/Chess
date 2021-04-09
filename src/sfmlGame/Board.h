#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Parametre.h"


class Board
{
public :
	
	Board(sf::RenderTarget&);
	void print() const;

	void setBoard(const int x, const int y, const char piece);
	char getBoard( int x,  int y) const;
	void draw();
	
private :
	void deduceTableFromFen();
	
private :
	std::string m_fen;
	char m_table[8][8];
	sf::Sprite sprite;
	sf::VertexArray m_echequier;
	sf::Texture piece;
	sf::RenderTarget* target;
};

#endif //BOARD_H
