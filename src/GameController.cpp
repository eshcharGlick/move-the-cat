#include "GameController.h"

GameController::GameController()
{
	for (int i = 0; i < SIZE_OF_TABLE; i++)
		for (int j = 0; j < SIZE_OF_TABLE; j++)
			m_dots[i][j] = Dot(i, j);

	if (!m_font.loadFromFile("CASTELAR.TTF"))
		exit(EXIT_FAILURE);

	m_level.setFont(m_font);
	m_level.setCharacterSize(40);
	m_level.setFillColor(sf::Color::Black);
	m_level.setPosition(400,10);

	m_texture[0].loadFromFile("levelSucsses.PNG");
	m_texture[1].loadFromFile("levelFail.PNG");
	m_texture[UNDO].loadFromFile("undo.PNG");

	m_sprites.push_back(sf::Sprite(m_texture[0]));
	m_sprites.push_back(sf::Sprite(m_texture[1]));
	m_sprites.push_back(sf::Sprite(m_texture[UNDO]));

	m_sprites[2].setPosition(50, 15);
	m_sprites[2].setScale(0.2f, 0.2f);

	srand(time(NULL));
}

void GameController::run()
{
	readNumOfLevel();

	for (int level = 1; level <= m_numOfLevels; level++)
	{
		bool win = runLevel(level);
		if (!m_window.isOpen())
			break;
		if (!win)
			level--;
		finishLevel(win);
	}
	//finishGame();
}

bool GameController::runLevel(int level)
{
	InitializeLevel(level);
	draw();
	while (m_window.isOpen())
	{
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				return false;
			case sf::Event::MouseButtonReleased:
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });

				if (checkButtonClicked(location))
				{
					draw();
					if (m_cat.isTrapped(m_map))
						return true;
				 	m_catMoves.push(m_cat.move(m_map));
					draw();
					if (m_cat.isLoose())
						return false;
				}
				break;
			}
		}
		draw();
	}
}

void GameController::InitializeLevel(int level)
{
	m_map = Graph();
	for (int row = 0; row < SIZE_OF_TABLE; row++)
		for (int col = 0; col < SIZE_OF_TABLE; col++)
			m_dots[row][col] = Dot(row, col);

	m_cat.move(5, 5,m_map);
	m_catMoves = {};
	m_catMoves.push(5*SIZE_OF_TABLE +5);
	m_dotPress = {};

	m_level.setString("level " + std::to_string(level));
	int numOfBlocked =std::min( std::max(4, int ((m_numOfLevels - level)*5)), 14);

	for (int i = 0; i < numOfBlocked; i++)
	{
		int a = rand() % SIZE_OF_TABLE, b = rand() % SIZE_OF_TABLE;
		if ((a == 5 && b == 5 )|| m_dots[a][b].isBlocked())
		{
			i--;
			continue;
		}
		m_map.removeVertex(a, b);
		m_dots[a][b].push();
	}
}

bool GameController::checkButtonClicked(const sf::Vector2f& location)
{
	if (m_sprites[UNDO].getGlobalBounds().contains(location))
	{
		undo();
		return false;
	}

	for (int i = 0 ;i <SIZE_OF_TABLE; i++)
		for (int j = 0; j < SIZE_OF_TABLE; j++)
			if (m_dots[i][j].contains(location) && !m_dots[i][j].isBlocked() && !m_cat.isIn(i,j))
			{
				m_dots[i][j].push();
				m_map.removeVertex(i,j);
				m_dotPress.push(i * SIZE_OF_TABLE + j);
				return true;
			}
			
	return false;
}

void GameController::readNumOfLevel()
{
	auto lvl = "NumOfLevel.txt";

	std::ifstream level(lvl);
	std::string line = std::string();

	std::getline(level, line);
	m_numOfLevels =  std::stoi(line);
}

void GameController::undo()
{
	if (m_dotPress.empty())
		return;
	int cat = m_catMoves.top();
	m_catMoves.pop();
	int dot = m_dotPress.top();
	m_dotPress.pop();

	int catY = cat / SIZE_OF_TABLE, catX = cat % SIZE_OF_TABLE;
	int dotY = dot / SIZE_OF_TABLE, dotX = dot % SIZE_OF_TABLE;

	m_map.createVertex(dotY , dotX, true);
	m_dots[dotY][dotX].undo();
	m_cat.move(catX, catY, m_map);
}

void GameController::finishLevel(bool state)
{
	_sleep(1000);

	m_window.clear(sf::Color::White);

	if (state)
		m_window.draw(m_sprites[0]);
	else
		m_window.draw(m_sprites[1]);

	m_window.display();

	_sleep(1500);
}

void GameController::draw()
{
	m_window.clear(sf::Color::White);
	for (int i = 0; i < SIZE_OF_TABLE; i++)
		for (int j = 0; j < SIZE_OF_TABLE; j++)
			m_dots[i][j].draw(m_window);
	m_cat.draw(m_window);
	m_window.draw(m_level);
	m_window.draw(m_sprites[UNDO]);

	m_window.display();
}
