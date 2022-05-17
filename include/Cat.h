#pragma once
#include <SFML/Graphics.hpp>

#include "Graph.h"


class Cat
{
public:
	Cat();
	
	int move(const Graph& graph);
	void move(int x, int y, const Graph& graph);

	bool isTrapped(const Graph& graph) const;
	bool isLoose();
	bool isIn(int y , int x);
	void draw(sf::RenderWindow& window);

private:
	int m_x = 5;
	int m_y = 5;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void randMove(const Graph& graph);

	int findShortWay(const Graph& graph);
};
