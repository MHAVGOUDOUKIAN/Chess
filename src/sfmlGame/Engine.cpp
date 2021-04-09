#include "Engine.h"

const sf::Time Engine::m_timePerFrame = sf::seconds(1.f/120.f);

Engine::Engine()
: m_window(sf::VideoMode(TAILLE_FENETRE_X, TAILLE_FENETRE_Y), "Chess", sf::Style::Close), m_pieceChoisie('0'), m_coordPieceChoisie(0,0)
, m_board(m_window)
{
	texture.loadFromFile("assets/piece.png");
	texture.setSmooth(true);
	ma_piece.setTexture(texture);
	ma_piece.scale(m_window.getSize().x/1600.f, m_window.getSize().y/1600.f);
}

void Engine::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			update();
		}

		render();
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch(event.type)
        {
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

			case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;

            case sf::Event::Closed:
                m_window.close();
                break;
        }
	}
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed;
		if(!isPressed) { this->MouseLPressed=false; }
	}
    if(mouse == sf::Mouse::Right) { this-> MouseR = isPressed;
		if(!isPressed) { this->MouseRPressed=false; }
	}
}

bool Engine::isInside() const
{
	if(sf::Mouse::getPosition(m_window).x>0 && sf::Mouse::getPosition(m_window).x < int(m_window.getSize().x) && sf::Mouse::getPosition(m_window).y>0 && sf::Mouse::getPosition(m_window).y< int(m_window.getSize().y)) {
		return true;
	}
	else { return false; }
}


void Engine::update()
{


	if(isInside())
	{
		if(MouseL && !MouseLPressed){
			m_pieceChoisie = m_board.getBoard(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
			m_coordPieceChoisie = sf::Vector2i(sf::Mouse::getPosition(m_window).x*8/m_window.getSize().x, sf::Mouse::getPosition(m_window).y*8/m_window.getSize().y);
			m_board.setBoard(m_coordPieceChoisie.x, m_coordPieceChoisie.y, '0');
			this->MouseLPressed=true;

			m_window.setMouseCursorVisible(false);
			std::string pieces = "rnbqkpRNBQKP";

			int indice_piece = pieces.find_first_of(m_pieceChoisie);
			int colonne = 0;
			if(indice_piece > 5) { 
				indice_piece -= 6; 
				colonne = 1;
			}
			
			ma_piece.setTextureRect(sf::IntRect(sf::Vector2i( indice_piece* 200.f, colonne *200.f),sf::Vector2i(200.f,200.f)));
		}

		if(!MouseL)
		{
			if(m_pieceChoisie != '0') {
				m_board.setBoard(sf::Mouse::getPosition(m_window).x*8/m_window.getSize().x, sf::Mouse::getPosition(m_window).y*8/m_window.getSize().y, m_pieceChoisie);
			}
			m_pieceChoisie = '0';
		}
	}

	if(m_pieceChoisie != '0') {
		ma_piece.setPosition(sf::Mouse::getPosition(m_window).x - ma_piece.getGlobalBounds().width/2 ,sf::Mouse::getPosition(m_window).y - ma_piece.getGlobalBounds().height/2);
	}
	else{ m_window.setMouseCursorVisible(true); }
}

void Engine::render()
{
	m_window.clear();
	m_board.draw();
	if(m_pieceChoisie != '0'){m_window.draw(ma_piece);}
	m_window.display();
}
