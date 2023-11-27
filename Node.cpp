#include "Node.h"

//Board State
State::State(int** initBoard)
{
    this->board = new int* [9];
    for (int row = 0; row < 9; ++row) {
        this->board[row] = new int[9];

        for (int col = 0; col < 9; ++col) {
            this->board[row][col] = initBoard[row][col];
        }
    }

    this->children = nullptr;
}

State::~State()
{
    for (int index = 0; index < this->totalChild; ++index) {
        delete this->children[index];
        this->children[index] = nullptr;
    }
    delete this->children;
    this->children = nullptr;

    this->totalChild = 0;
    this->t = 0;
    this->n = 0;

    for (int row = 0; row < 9; ++row) {
        delete this->board[row];
        this->board[row] = nullptr;
    }
    this->board = nullptr;
}

void State::printBoard()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (this->board[row][col] == 0) {
                std::cout << "| ";
            }
            else if (this->board[row][col] == 1) {
                std::cout << "|X";
            }
            else if (this->board[row][col] == -1) {
                std::cout << "|O";
            }
        }
        std::cout << "|" << std::endl;
    }
}

vector<vector<int>> State::getValidMove()
{
    vector<vector<int>> result;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (this->board[row][col] == 0) {
                vector<int> newMove;
                newMove.push_back(row);
                newMove.push_back(col);
                result.push_back(newMove);
            }
        }
    }

    return result;
}

void State::printValidMove()
{
    vector<vector<int>> validMove = this->getValidMove();
    for (unsigned int index = 0; index < validMove.size(); ++index) {
        std::cout << "(" << validMove[index][0] << "," << validMove[index][1] << ")\n";
    }
    validMove.clear();
}

bool State::isTerminal()
{
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            if (this->board[row][col] == this->board[row][col + 1]
                && this->board[row][col] == this->board[row][col + 2]
                && this->board[row][col] == this->board[row][col + 3]
                && this->board[row][col] == this->board[row][col + 4]) {
                return true;
            }
        }
    }

    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 5; ++row) {
            if (this->board[row][col] == 0) {
                continue;
            }

            if (this->board[row][col] == this->board[row + 1][col]
                && this->board[row][col] == this->board[row + 2][col]
                && this->board[row][col] == this->board[row + 3][col]
                && this->board[row][col] == this->board[row + 4][col]) {
                return true;
            }
        }
    }

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            if (this->board[row][col] == this->board[row + 1][col + 1]
                && this->board[row][col] == this->board[row + 2][col + 2]
                && this->board[row][col] == this->board[row + 3][col + 3]
                && this->board[row][col] == this->board[row + 4][col + 4]) {
                return true;
            }
        }
    }

    for (int row = 0; row < 5; ++row) {
        for (int col = 4; col < 9; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            if (this->board[row][col] == this->board[row + 1][col - 1]
                && this->board[row][col] == this->board[row + 2][col - 2]
                && this->board[row][col] == this->board[row + 3][col - 3]
                && this->board[row][col] == this->board[row + 4][col - 4]) {
                return true;
            }
        }
    }

    if (this->getValidMove().size() == 0) {
        return true;
    }
    return false;
}

bool State::getIsExpand()
{
    return this->isExpand;
}

int State::getLeafValue()
{
    int current_move = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (this->board[row][col] != 0) {
                current_move += 1;
            }
        }
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            int player = this->board[row][col];
            if (this->board[row][col] == this->board[row][col + 1]
                && this->board[row][col] == this->board[row][col + 2]
                && this->board[row][col] == this->board[row][col + 3]
                && this->board[row][col] == this->board[row][col + 4]) {
                return this->getValueBaseOnWinner(player, current_move);
            }
        }
    }

    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 5; ++row) {
            if (this->board[row][col] == 0) {
                continue;
            }

            int player = this->board[row][col];
            if (this->board[row][col] == this->board[row + 1][col]
                && this->board[row][col] == this->board[row + 2][col]
                && this->board[row][col] == this->board[row + 3][col]
                && this->board[row][col] == this->board[row + 4][col]) {
                return this->getValueBaseOnWinner(player, current_move);
            }
        }
    }

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            int player = this->board[row][col];
            if (this->board[row][col] == this->board[row + 1][col + 1]
                && this->board[row][col] == this->board[row + 2][col + 2]
                && this->board[row][col] == this->board[row + 3][col + 3]
                && this->board[row][col] == this->board[row + 4][col + 4]) {
                return this->getValueBaseOnWinner(player, current_move);
            }
        }
    }

    for (int row = 0; row < 5; ++row) {
        for (int col = 4; col < 9; ++col) {
            if (this->board[row][col] == 0) {
                continue;
            }

            int player = this->board[row][col];
            if (this->board[row][col] == this->board[row + 1][col - 1]
                && this->board[row][col] == this->board[row + 2][col - 2]
                && this->board[row][col] == this->board[row + 3][col - 3]
                && this->board[row][col] == this->board[row + 4][col - 4]) {
                return this->getValueBaseOnWinner(player, current_move);
            }
        }
    }

    if (this->getValidMove().size() == 0) {
        return this->getValueBaseOnWinner(0, 0);
    }
    return this->getValueBaseOnWinner(0, 0);
}

int State::getValueBaseOnWinner(int player, int current_move)
{
    if (player == 1) {
        return pow(81, 3) - pow(current_move, 3);
    }
    if (player == -1) {
        return -1 * pow(81, 3) + pow(current_move, 3);
    }
    if (player == 0) {
        return 0;
    }
    return 0;
}

int State::getN()
{
    return this->n;
}

double State::UCB1(int iteration)
{
    if (this->n == 0) {
        return DBL_MAX;
    }

    double result = (this->t * 1.0 / this->n) + 2.0 * sqrt(log(iteration * 1.0) / this->n);
    return result;
}

double State::score()
{
    if (this->n == 0) {
        return DBL_MAX;
    }

    double result = (this->t * 1.0 / this->n);
    return result;
}

int** State::makeMove(vector<int> move, int player)
{
    int** nextState;
    nextState = new int* [9];
    for (int row = 0; row < 9; ++row) {
        nextState[row] = new int[9];

        for (int col = 0; col < 9; ++col) {
            nextState[row][col] = this->board[row][col];
        }
    }

    if (nextState[move[0]][move[1]] == 0) {
        nextState[move[0]][move[1]] = player;
    }

    return nextState;
}

int** State::makeRandomMove(int player)
{
    vector<vector<int>> validMove = this->getValidMove();

    srand(time(NULL));
    unsigned int move = rand() % validMove.size();

    return this->makeMove(validMove[move], player);
}

State* State::simulate(int player)
{
    State* current;
    current = new State(this->board);

    while (current->isTerminal() == false) {
        int** next = current->makeRandomMove(player);
        delete current;
        current = new State(next);
        player *= -1;

        delete next;
        next = nullptr;
    }

    //int value = current->getLeafValue();
    //this->backpropagation(value);
    return current;
}

int State::backpropagation(int value)
{
    this->n += 1;
    this->t += value;

    return value;
}

void State::expand(int player)
{
    if (this->isExpand == true) {
        return;
    }

    if (this->isTerminal() == true) {
        return;
    }

    vector<vector<int>> validMove = this->getValidMove();
    this->totalChild = validMove.size();
    this->children = new State * [this->totalChild];
    this->isExpand = true;

    for (int index = 0; index < this->totalChild; ++index) {
        int** next = this->makeMove(validMove[index], player);
        this->children[index] = new State(next);

        deleteBoard(next);
        next = nullptr;
    }
}

int State::selectUCB1(int iteration)
{
    double maxUCB1 = this->children[0]->UCB1(iteration);
    for (int index = 1; index < this->totalChild; ++index) {
        double childUCB1 = this->children[index]->UCB1(iteration);
        if (childUCB1 > maxUCB1) {
            maxUCB1 = childUCB1;
        }
    }

    vector<int> chosenNodes;
    for (int index = 0; index < this->totalChild; ++index) {
        double childUCB1 = this->children[index]->UCB1(iteration);
        if (childUCB1 == maxUCB1) {
            chosenNodes.push_back(index);
        }
    }

    int chosenNode = chosenNodes[0];
    if (chosenNodes.size() > 1) {
        chosenNode = chosenNodes[rand() % chosenNodes.size()];
    }

    return chosenNode;
}

int State::roolout(int player, int iteration)
{
    if (this->isExpand == false) {
        this->expand(player);
        State* roolout_result = this->simulate();
        int value = roolout_result->getLeafValue();

        delete roolout_result;
        roolout_result = nullptr;

        return this->backpropagation(value);
    }

    int chosenNode = this->selectUCB1(iteration);
    int roolout_result_value = this->children[chosenNode]->roolout(player, iteration);
    return this->backpropagation(roolout_result_value);
}

void State::MCST(int player)
{
    int iterator = 500;
    vector<vector<int>> valid_move = this->getValidMove();
    if (valid_move.size() >= 80) {
        iterator = 100;
    }
    if (valid_move.size() >= 70) {
        iterator = 300;
    }

    for (int index = 0; index < iterator; ++index) {
        this->roolout(player, index);
    }
}

vector<int> State::getBestMove()
{
    double maxN = this->children[0]->score();
    for (int index = 1; index < this->totalChild; ++index) {
        double childN = this->children[index]->score();
        if (childN > maxN) {
            maxN = childN;
        }
    }

    vector<int> chosenNodes;
    for (int index = 0; index < this->totalChild; ++index) {
        double childN = this->children[index]->score();
        if (childN == maxN) {
            chosenNodes.push_back(index);
        }
    }

    int chosenNode = chosenNodes[0];
    if (chosenNodes.size() > 1) {
        chosenNode = chosenNodes[rand() % chosenNodes.size()];
    }

    vector<vector<int>> validMove = this->getValidMove();
    return validMove[chosenNode];
}

//Other
int** initialBoard() {
    int** initialState;
    initialState = new int* [9];
    for (int row = 0; row < 9; ++row) {
        initialState[row] = new int[9];

        for (int col = 0; col < 9; ++col) {
            initialState[row][col] = 0;
        }
    }

    return initialState;
}

int** flipBoard(int** board) {
    int** initialState;
    initialState = new int* [9];
    for (int row = 0; row < 9; ++row) {
        initialState[row] = new int[9];

        for (int col = 0; col < 9; ++col) {
            initialState[row][col] = -1 * board[row][col];
        }
    }

    return initialState;
}

int** copyBoard(int** board) {
    int** initialState;
    initialState = new int* [9];
    for (int row = 0; row < 9; ++row) {
        initialState[row] = new int[9];

        for (int col = 0; col < 9; ++col) {
            initialState[row][col] = board[row][col];
        }
    }

    return initialState;
}

void deleteBoard(int** board) {
    for (int row = 0; row < 9; ++row) {
        delete board[row];
        board[row] = nullptr;
    }
    delete board;
    board = nullptr;
}

vector<int> MCST(int** board) {
    State* currentState = new State(board);
    currentState->expand(1);
    currentState->MCST(1);
    vector<int> bestMove = currentState->getBestMove();

    delete currentState;
    currentState = nullptr;
    return bestMove;
}