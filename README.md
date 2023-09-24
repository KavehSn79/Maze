# Maze
Solving Maze using B-Tree

This is a C++ program that solves a maze using Dijkstra's algorithm and prints the solution.

The program is structured into two main parts:

a B-Tree implementation for optimizing certain operations and a maze-solving algorithm using Dijkstra's shortest path algorithm.


B-Tree Implementation:

BTreeNode Class:

The BTreeNode class represents a node in a B-Tree.

It contains an array of keys, pointers to child nodes, the degree of the B-Tree, the number of keys currently in the node, and a flag indicating whether it's a leaf node.

Methods in this class include insertNonFull, split, and search.

BTree Class:

The BTree class represents the B-Tree itself and contains the root node.

It includes methods for searching and inserting elements into the tree.

Maze Solver:

path Struct

The path struct represents a cell in the maze and includes information about its row, column, number, difference, and possible ways to move from it.

Maze Class:

The Maze class is used to represent and solve a maze.

It includes methods for printing the maze, creating the maze, converting it into a graph, finding the minimum distance, finding the path, and solving the maze.

Main Function:

The main function reads the dimensions of the maze, constructs the maze, converts it into a graph, and uses Dijkstra's algorithm to find the shortest path through the maze.

The solution is then printed by marking the path on the maze grid.

Usage

To use this program, compile it with a C++ compiler and provide the maze dimensions and cell values as input. The program will then print the solved maze with the shortest path marked.
$ g++ maze_solver.cpp -o maze_solver
$ ./maze_solver


Please ensure that your maze is correctly formatted as input, with non-zero values representing walls and zero values representing open paths.
