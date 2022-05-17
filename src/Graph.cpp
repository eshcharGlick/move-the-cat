#include "Graph.h"
#include <list>

Graph::Graph()
{
    for (int row = 0; row < SIZE_OF_TABLE; row++)
        for (int col = 0; col < SIZE_OF_TABLE; col++)
            createVertex(row, col,false);
}

void Graph::addEdge(int rowA , int colA ,int rowB, int colB, bool recreate)
{
    if (rowA < 0 || colA < 0 || rowA >= SIZE_OF_TABLE || colA >= SIZE_OF_TABLE || rowB < 0 || colB < 0 || rowB >= SIZE_OF_TABLE || colB >= SIZE_OF_TABLE)
        return;
    int a = rowA * SIZE_OF_TABLE + colA, b = rowB * SIZE_OF_TABLE + colB;
    if (recreate && m_adge[b].size() == 0)
        return;
    m_adge[a].push_back(b);
    m_adge[b].push_back(a);
}

void Graph::removeEdge(int rowA, int colA, int rowB, int colB)
{
    if (rowA < 0 || colA < 0 || rowA >= SIZE_OF_TABLE || colA >= SIZE_OF_TABLE || rowB < 0 || colB < 0 || rowB >= SIZE_OF_TABLE || colB >= SIZE_OF_TABLE)
        return;

    int a = rowA * SIZE_OF_TABLE + colA, b = rowB * SIZE_OF_TABLE + colB;

    m_adge[b].erase(std::remove(m_adge[b].begin(), m_adge[b].end(), a), m_adge[b].end());

}

void Graph::createVertex(int row, int col, bool recreate)
{
    addEdge(row, col, row, col + 1,recreate);
    addEdge(row, col, row, col - 1,recreate);
    addEdge(row, col, row + 1, col,recreate);
    addEdge(row, col, row - 1, col,recreate);

    if (row % 2 == 0)
    {
        addEdge(row, col, row + 1, col - 1,recreate);
        addEdge(row, col, row - 1, col - 1,recreate);
    }
    else
    {
        addEdge(row, col, row + 1, col + 1,recreate);
        addEdge(row, col, row - 1, col + 1,recreate);
    }
}

void Graph::removeVertex(int row, int col)
{
    removeEdge(row, col, row, col + 1);
    removeEdge(row, col, row, col - 1);
    removeEdge(row, col, row + 1, col);
    removeEdge(row, col, row - 1, col);

    if (row % 2 == 0)
    {
        removeEdge(row, col, row + 1, col - 1);
        removeEdge(row, col, row - 1, col - 1);
    }
    else
    {
        removeEdge(row, col, row + 1, col + 1);
        removeEdge(row, col, row - 1, col + 1);
    }

    m_adge[row * SIZE_OF_TABLE + col].clear();
}

bool Graph::isEmpty(int row, int col) const
{
    int num = row * SIZE_OF_TABLE + col;
    int size = m_adge[num].size();
    if (size == 0)
        return true;
    return false;
}

bool Graph::bfs(int src, int dest, int v, int pred[], int dist[]) const
{
    std::list<int> queue;

    bool visited[SIZE_OF_TABLE * SIZE_OF_TABLE];

    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < m_adge[u].size(); i++) {
            if (visited[m_adge[u][i]] == false) {
                visited[m_adge[u][i]] = true;
                dist[m_adge[u][i]] = dist[u] + 1;
                pred[m_adge[u][i]] = u;
                queue.push_back(m_adge[u][i]);

                if (m_adge[u][i] == dest)
                    return true;
            }
        }
    }
    return false;
}

int Graph::randNeighbor(int row, int col) const
{
    int num = row * SIZE_OF_TABLE + col;
    int size = m_adge[num].size();
    int neighbor = rand() % size;
    return m_adge[num][neighbor];
}
