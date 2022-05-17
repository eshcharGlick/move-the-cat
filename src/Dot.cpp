#include "Dot.h"

Dot::Dot(int y , int x)
{
	m_dot = sf::CircleShape(30);
	m_dot.setFillColor(sf::Color(204, 255, 0, 255));
	if (y %2 == 1)
		m_dot.setPosition(x * 70 + GAP + 30 , y * 70 + GAP);
	else
		m_dot.setPosition(x * 70 + GAP, y * 70 + GAP);
}

bool Dot::contains(const sf::Vector2f& location)
{
	return m_dot.getGlobalBounds().contains(location);
}

void Dot::push()
{
	m_dot.setFillColor(sf::Color (114 ,133 ,1,255 ));
	m_blocked = true;
}

void Dot::undo()
{
	m_dot.setFillColor(sf::Color(204, 255, 0, 255));
	m_blocked = false;
}

void Dot::draw(sf::RenderWindow& window)
{
	window.draw(m_dot);
}

bool Dot::isBlocked() const
{
	return m_blocked;
}
