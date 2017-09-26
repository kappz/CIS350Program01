/*
Author: Peter O'Donohue
Creation Date: 09/18/17
Modification Date: 09/26/17
Description: FILL IN
*/

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

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
	if (size < 1)
		size = 1;
	else if (size > 26)
		size = 26;
	else
		adj.resize(size, size);
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
			{
				adj[i][j] = '?';
			}
}
void Graph::fillGraph()
{
	int numAdjacent = 0;
	char vertex = ' ';
	string adjacencies = "";

	switch (adj.numrows())
	{
	case 1:
		cin >> vertex >> numAdjacent;
		vertex = toupper(vertex);
		adj[0][0] = vertex;
		break;

	default:
		for (int i = 0; i < adj.numrows(); ++i)
		{
			cin >> vertex >> numAdjacent;
			getline(cin, adjacencies);
			if (numAdjacent >= adj.numrows())
				numAdjacent = adj.numrows() - 1;
			vertex = toupper(vertex);
			adjacencies.erase(remove_if(adjacencies.begin(), adjacencies.end(), isspace), adjacencies.end());
			transform(adjacencies.begin(), adjacencies.end(), adjacencies.begin(), ::toupper);
			adj[i].resize(numAdjacent + 1);
			adj[i][0] = vertex;
			for (int j = 0; j < numAdjacent; ++j)
			{
				adj[i][j + 1] = adjacencies.at(j);
			}
		}
		break;
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
	int adjRow = 0;
	int cover = 0;
	int tempCover = 0;
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
		if (cover < tempCover)
			cover = tempCover;
		orderIndexOne = 0;
		orderIndexTwo = 0;
	}
	return cover;
}

int main()
{
	int numGraphs = 0;
	int numVertices = 0;
	int maxCover = 0;
	int minMaxCover = 0;
	vector<char> permutation;
	vector<char> order;

//	ifstream inFile;
//	inFile.open("input.txt");

	cin >> numGraphs;
	for (int i = 0; i < numGraphs; ++i)
	{
		cin >> numVertices;
		Graph foo(numVertices);
		foo.fillGraph();
		foo.fillVector(permutation);
		minMaxCover = permutation.size() + 1;
		sort(permutation.begin(), permutation.end());
		do
		{
			maxCover = foo.maxCover(permutation);
			if (maxCover < minMaxCover)
			{
				minMaxCover = maxCover;
				order = permutation;
			}
			else if (maxCover == minMaxCover  && order > permutation)
			{
				order = permutation;
			}

		} while (next_permutation(permutation.begin(), permutation.end()));

		for (char temp : order)
		{
			cout << temp << " ";
		}
		cout << minMaxCover << endl;
		order.clear();
		permutation.clear();
	}
//	inFile.close();
// system("pause");
	return 0;
}