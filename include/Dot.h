#pragma once
#include "SFML/Graphics.hpp"

#include "Macros.h"

class Dot
{
public:
	Dot() {};
	Dot(int y , int x);

	bool contains(const sf::Vector2f& location);
	void push();
	void undo();
	void draw(sf::RenderWindow& window);

	bool isBlocked()const;
private:
	bool m_blocked = false;
	sf::CircleShape m_dot;
};
