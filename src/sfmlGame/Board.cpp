#include "Board.h"

Board::Board(sf::RenderTarget& m_target)
: m_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), m_echequier(sf::Quads,4 * 64)
{
	this->target = &m_target;
	deduceTableFromFen();
	piece.loadFromFile("assets/piece.png");
	piece.setSmooth(true);
	sprite.setTexture(piece);
	sprite.scale(target->getSize().x/1600.f, target->getSize().y/1600.f); // 1600 = 200 * 8 (taille de l'image * nombre de cases)

	

	// on dessine le plateau une bonne fois pour toute => réduction du nombre d'appel à draw pdt exécution
	bool black = false;
	for(short i=0; i<8; i++) {
		for(short j=0; j<8; j++)
		{
			m_echequier[(i*8 + j)*4].position = sf::Vector2f(j * target->getSize().x/8.f, i * target->getSize().y/8.f);
			m_echequier[(i*8 + j)*4+1].position = sf::Vector2f((j+1) * target->getSize().x/8.f, i * target->getSize().y/8.f);
			m_echequier[(i*8 + j)*4+2].position = sf::Vector2f((j+1) * target->getSize().x/8.f, (i+1) * target->getSize().y/8.f);
			m_echequier[(i*8 + j)*4+3].position = sf::Vector2f(j * target->getSize().x/8.f, (i+1) * target->getSize().y/8.f);

			m_echequier[(i*8 + j)*4].color = black ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181);
			m_echequier[(i*8 + j)*4+1].color = black ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181);
			m_echequier[(i*8 + j)*4+2].color = black ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181);
			m_echequier[(i*8 + j)*4+3].color = black ? sf::Color(181, 136, 99) : sf::Color(240, 217, 181);

			black = !black;
		}
		black = !black;
	}
}

void Board::deduceTableFromFen()
{
	for(std::size_t i = 0; i < 8; ++i)
	{
		for(std::size_t j = 0; j < 8; ++j)
		{
			m_table[i][j] = '0';
		}
	}
	
	std::size_t row = 0;
	std::size_t col = 0;
	std::size_t s = m_fen.size();
	std::string num = "12345678";
	
	for(std::size_t i = 0; i < s; ++i)
	{
		char cell = m_fen[i];
		if(cell == ' ')
			break;
		else if(cell == '/')
		{
			++row;
			col = 0;
		}
		else if(num.find_first_of(cell) < s)
			col += cell - '0';
		else
		{
			m_table[row][col] = cell;
			++col;
		}
	}
}

void Board::draw()
{
	target->draw(m_echequier);	

	for (short i = 0; i < 8; ++i)
	{
		for (short j = 0; j < 8; ++j)
		{
			std::string pieces = "rnbqkpRNBQKP";
			char cursor = m_table[j][i];

			if(pieces.find_first_of(cursor) < pieces.size())
			{
				int indice_piece = pieces.find_first_of(cursor);

				int colonne = 0;
				if(indice_piece > 5) { 
					indice_piece -= 6; 
					colonne = 1;
				}

				sprite.setTextureRect(sf::IntRect(sf::Vector2i( indice_piece* 200.f, colonne *200.f),sf::Vector2i(200.f,200.f))); 

				sprite.setPosition((i*target->getSize().x+1.f)/8, (j*target->getSize().y+1.f)/8);
				target->draw(sprite);
			}
		}
	}
}

void Board::print() const
{
	std::cout << std::endl;
	std::cout << "\t+---+---+---+---+---+---+---+---+" << std::endl;
	for(std::size_t i = 0; i < 8; ++i)
	{
		std::cout << "\t| ";
		for(std::size_t j = 0; j < 8; ++j)
		{
			std::cout << m_table[i][j] << " | ";
		}
		std::cout << std::endl;
		std::cout << "\t+---+---+---+---+---+---+---+---+" << std::endl;
	}
	std::cout << std::endl;
}

void Board::setBoard(const int x, const int y, const char piece) // x, y en pixels
{
	m_table[y][x] = piece;
}

char Board::getBoard( int x,  int y) const
{
	return m_table[y*8/target->getSize().y][x*8/target->getSize().x];
}