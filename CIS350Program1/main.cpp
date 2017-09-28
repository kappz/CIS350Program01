/*
Author: Peter O'Donohue
Creation Date: 09/18/17
Modification Date: 09/28/17
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
	void fillGraph(ifstream& inputFile); // fills in the graph from cin
	void fillVector(vector<char>& order);
	void printGraph(); // prints the graph (for debugging only)
	string removeSpaces(string withSpaces);
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
void Graph::fillGraph(ifstream& inputFile)
{
	int numAdjacent = 0;
	char vertex = ' ';
	string adjacencies = "";

	if (adj.numrows() == 1)
	{
		inputFile >> vertex >> numAdjacent;
		vertex = toupper(vertex);
		adj[0][0] = vertex;
	}
	else
	{
		for (int i = 0; i < adj.numrows(); ++i)
		{
			inputFile >> vertex >> numAdjacent;
			getline(inputFile, adjacencies);
			adjacencies = removeSpaces(adjacencies);
			if (numAdjacent >= adj.numrows())
				numAdjacent = adj.numrows() - 1;
			vertex = toupper(vertex);
			adj[i].resize(numAdjacent + 1);
			adj[i][0] = vertex;
			for (int j = 0; j < numAdjacent; ++j)
			{
				adj[i][j + 1] = adjacencies.at(j);
			}
		}
	}
}
void Graph::fillVector(vector<char>& order)
{
	for (int i = 0; i < adj.numrows(); ++i)
	{
		order.push_back(adj[i][0]);
	}
}
string Graph::removeSpaces(string hasSpaces)
{
	char transfer = ' ';
	string noSpaces = "";
	for (int i = 0; i < hasSpaces.length(); ++i)
		if (hasSpaces.at(i) != ' ')
		{
			transfer = toupper(hasSpaces.at(i));
			noSpaces += transfer;
		}
	return noSpaces;
}
void Graph::printGraph()
{

	for (int i = 0; i < adj.numrows(); ++i)
		for (int j = 0; j < adj[i].size(); ++j)
		{
			cout << adj[i][j] << " ";
		}
	cout << endl;
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
	vector<char> order;
	vector<char> permutation;
	ifstream inFile;
	inFile.open("input.txt");
	inFile >> numGraphs;
	for (int i = 0; i < numGraphs; ++i)
	{
		inFile >> numVertices;
		Graph foo(numVertices);
		foo.fillGraph(inFile);
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
	system("pause");
	return 0;
}