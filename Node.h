#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <time.h>       
#include <cmath>

using namespace std;

class State
{
private:
	int** board;
	State** children = nullptr;
	int totalChild = 0;
	int t = 0;
	int n = 0;
	bool isExpand = false;

public:
	State(int** initBoard);
	~State();
	void printBoard();
	vector<vector<int>> getValidMove();
	void printValidMove();
	bool isTerminal();
	bool getIsExpand();
	int getLeafValue();
	int getValueBaseOnWinner(int player, int current_move = 0);

	int getN();
	double UCB1(int iteration);
	double score();
	int** makeMove(vector<int> move, int player);
	int** makeRandomMove(int player);
	State* simulate(int player = 1);
	int backpropagation(int value);
	void expand(int player);
	int selectUCB1(int iteration);
	int roolout(int player, int iteration);
	void MCST(int player);
	vector<int> getBestMove();
};

int** initialBoard();
int** flipBoard(int** board);
int** copyBoard(int** board);
void deleteBoard(int** board);

//Use
vector<int> MCST(int **board);