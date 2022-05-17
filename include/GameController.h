#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <stack>

#include "Macros.h"
#include "Cat.h"
#include "Dot.h"
#include "Graph.h"



class GameController
{
public:
	GameController();

	void run();
private:

	Cat m_cat;
	Dot m_dots[SIZE_OF_TABLE][SIZE_OF_TABLE] ;
	Graph m_map;
	int m_numOfLevels;
	std::stack<int> m_catMoves, m_dotPress;
 
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Catch the Cat", sf::Style::Close | sf::Style::Titlebar);
	sf::Texture m_texture[3];
	std::vector<sf::Sprite> m_sprites;
	
	sf::Font m_font;
	sf::Text m_level;

	void readNumOfLevel();

	bool runLevel(int level);
	void InitializeLevel(int level);
	bool checkButtonClicked(const sf::Vector2f& location);

	void undo();
	void finishLevel(bool state);

	void draw();

};