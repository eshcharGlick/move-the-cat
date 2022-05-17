#pragma once
#include <vector>

#include "Macros.h"

//std::pair
class Graph
{
public:
	Graph();

	void addEdge(int rowA, int colA, int rowB, int colB, bool recreate);
	void removeEdge(int rowA, int colA, int rowB, int colB);
	void createVertex(int row, int col, bool recreate);
	void removeVertex(int row, int col);

	bool isEmpty(int row, int col)const;

	bool bfs(int src, int dest, int v, int pred[], int dist[]) const;

	int randNeighbor(int row , int col)const;
private:
	std::vector<int> m_adge[SIZE_OF_TABLE * SIZE_OF_TABLE];
};
