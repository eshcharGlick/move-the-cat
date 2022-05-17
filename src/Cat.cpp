#include "Cat.h"
#include <iostream>

Cat::Cat()
{
	m_texture.loadFromFile("cat.PNG");
	m_sprite.setTexture(m_texture);

	m_sprite.scale(0.2f, 0.2f);
	m_sprite.setPosition(5 * 70 + GAP + 30, 5 * 70 + GAP);
}

int Cat::move(const Graph& graph)
{
	int currVer = m_y * SIZE_OF_TABLE + m_x;
	int nextVer = findShortWay(graph);
	if (nextVer >= 0)
	{
		int x = nextVer % SIZE_OF_TABLE, y = nextVer / SIZE_OF_TABLE;
		m_x = x;
		m_y = y;
	}
	else
	{
		randMove(graph);
	}
	if (m_y % 2 == 1)
		m_sprite.setPosition(m_x * 70 + GAP + 30, m_y * 70 + GAP);
	else
		m_sprite.setPosition(m_x * 70 + GAP , m_y * 70 + GAP);
	
	return currVer;
}

void Cat::move(int x, int y ,const Graph& graph)
{
	if (!graph.isEmpty(y,x))
	{
		m_x = x;
		m_y = y;
		if (m_y % 2 == 1)
			m_sprite.setPosition(m_x * 70 + GAP + 30, m_y * 70 + GAP);
		else
			m_sprite.setPosition(m_x * 70 + GAP, m_y * 70 + GAP);
	}
}

bool Cat::isTrapped(const Graph & graph) const
{
	return graph.isEmpty(m_y , m_x);
}

bool Cat::isLoose()
{
	return m_x == 0 || m_y == 0 || m_x == SIZE_OF_TABLE - 1 || m_y == SIZE_OF_TABLE - 1;
}

bool Cat::isIn(int y, int x)
{
	return m_x == x && m_y == y;
}

void Cat::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Cat::randMove(const Graph& graph)
{
	int neighbor = graph.randNeighbor(m_y, m_x);
	m_y = neighbor / SIZE_OF_TABLE;
	m_x = neighbor % SIZE_OF_TABLE;
}

int Cat::findShortWay(const Graph& graph)
{
	bool locked = true;
	int cat = m_y * SIZE_OF_TABLE + m_x;
	int minDest = SIZE_OF_TABLE * SIZE_OF_TABLE, currDest, nextVer = -1;
	int pred[SIZE_OF_TABLE * SIZE_OF_TABLE], dist[SIZE_OF_TABLE * SIZE_OF_TABLE];

	for (int i = 0; i < SIZE_OF_TABLE; i++)
	{
		int a = i, b = i * SIZE_OF_TABLE, c = ((i + 1) * SIZE_OF_TABLE) - 1, d = i + (SIZE_OF_TABLE * (SIZE_OF_TABLE - 1));
		if (graph.bfs(a, cat, SIZE_OF_TABLE * SIZE_OF_TABLE, pred, dist))
			if (dist[cat] < minDest)
			{
				minDest = dist[cat];
				nextVer = pred[cat];
				locked = false;
			}
		if (graph.bfs(b, cat, SIZE_OF_TABLE * SIZE_OF_TABLE, pred, dist))
			if (dist[cat] < minDest)
			{
				minDest = dist[cat];
				nextVer = pred[cat];
				locked = false;
			}
		if (graph.bfs(c, cat, SIZE_OF_TABLE * SIZE_OF_TABLE, pred, dist))
			if (dist[cat] < minDest)
			{
				minDest = dist[cat];
				nextVer = pred[cat];
				locked = false;
			}
		if (graph.bfs(d, cat, SIZE_OF_TABLE * SIZE_OF_TABLE, pred, dist))
			if (dist[cat] < minDest)
			{
				minDest = dist[cat];
				nextVer = pred[cat];
				locked = false;
			}
	}
	return nextVer;
}
