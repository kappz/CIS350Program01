/*
Author: Peter O'Donohue
Creation Date: 09/18/17
Modification Date: 09/23/17
Description: FILL IN
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <class Object>
class Matrix
{
public:
	Matrix(int rows = 0, int cols = 0) : array(rows)
	{
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	void resize(int rows, int cols)
	{
		array.resize(rows);
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	const vector<Object> & operator[](int row) const
	{
		return array[row];
	}
	vector<Object> & operator[](int row)
	{
		return array[row];
	}
	int numrows() const
	{
		return array.size();
	}
	int numcols() const
	{
		return numrows() ? array[0].size() : 0;
	}
private:
	vector< vector<Object> > array;
};

class Graph
{
public:
	Graph(int size); // creates an empty graph with size vertices
	void fillGraph(); // fills in the graph from cin
	void fillVector(vector<char>& order);
	void printGraph(); // prints the graph (for debugging only)
	int maxCover(vector<char> order); // returns the maxCover for the
									  // ordering order
	int cover(char vertex, vector<char> order); // returns the cover size for vertex
private:
	Matrix<char> adj;
};

Graph::Graph(int size)
{
	adj.resize(size, size);
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
		{
			adj[i][j] = ' ';
		}
}
void Graph::fillGraph()
{
	int row = 0;
	int numAdj = 0;
	int numVertice = 0;
	char vertex = ' ';
	string adjacent = " ";
//	cout << "Num Vertices: ";
	cin >> numVertice;
	adj.resize(numVertice, numVertice);
	for (int i = 0; i < numVertice; ++i)
	{
//		cout << "Enter vertex, num of adj vertices, and adj vertices: ";
		cin >> vertex >> numAdj >> adjacent;
		vertex = toupper(vertex);
		transform(adjacent.begin(), adjacent.end(), adjacent.begin(), ::toupper);
		adj[row][0] = vertex;
		adj[row].resize(numAdj + 1);
		for (int i = 1; i <= numAdj; ++i)
		{
			adj[row][i] = adjacent.at(i - 1);
		}
		++row;
	}
}

void Graph::fillVector(vector<char>& order)
{
	for (int i = 0; i < adj.numrows(); ++i)
	{
		order.push_back(adj[i][0]);
	}
}
void Graph::printGraph()
{
	for (int i = 0; i < adj.numrows(); ++i)
	{
		for (int j = 0; j < adj[i].size(); ++j)
		{
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}

int Graph::maxCover(vector<char> order)
{
	int max = 0;
	int tempMax = 0;
	for (int i = 0; i < order.size(); ++i)
	{
		tempMax = cover(order[i], order);
		if (tempMax > max)
			max = tempMax;
	}
	return max;
}
int Graph::cover(char vertex, vector<char> order)
{
	int cover = 0;
	int tempCover = 0;
	int adjRow = 0;
	int orderIndexOne = 0;
	int orderIndexTwo = 0;
	while (adj[adjRow][0] != vertex)
	{
		++adjRow;
	}
	for (int i = 1; i < adj[adjRow].size(); ++i)
	{
		while (order[orderIndexOne] != vertex)
			++orderIndexOne;
		while (order[orderIndexTwo] != adj[adjRow][i])
			++orderIndexTwo;
		tempCover = abs(orderIndexTwo - orderIndexOne);
		if (tempCover > cover)
			cover = tempCover;
		orderIndexOne = 0;
		orderIndexTwo = 0;
	}
	return cover;
}
int main()
{
	int maxCover = 0;
	int minMaxCover = 27;
	int numGraphs = 0;
	vector<char> perm;
	vector<char> order;
	Graph foo(0);
//	cout << "Input number of graphs: ";
	cin >> numGraphs;
	for (int i = 0; i < numGraphs; ++i)
	{
		foo.fillGraph();
		foo.fillVector(perm);
		sort(perm.begin(), perm.end());
		do
		{
			maxCover = foo.maxCover(perm);
			if (maxCover < minMaxCover)
			{
				minMaxCover = maxCover;
				order = perm;
			}
			else if (maxCover = minMaxCover)
			{
				if (perm < order)
					order = perm;
			}

		} while (next_permutation(perm.begin(), perm.end()));

		for (int i = 0; i < order.size(); ++i)
			cout << order[i] << " ";
		cout << minMaxCover << endl;
		maxCover = 0;
		minMaxCover = 27;
		order.clear();
		perm.clear();
	}
	system("pause");
	return 0;
}
