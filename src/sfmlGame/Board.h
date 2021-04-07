#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


class Board : public sf::Drawable
{
public :
	
	Board();
	void print() const;

	void setBoard(const int x, const int y, const char piece);
	char getBoard( int x,  int y) const;
	
private :
	
	void deduceTableFromFen();
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	
private :
	std::string m_fen;
	char m_table[8][8];
};

#endif //BOARD_H
