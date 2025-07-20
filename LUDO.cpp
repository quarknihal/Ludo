#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fmt/core.h>
#include <cstdlib>

using namespace std;

int dice() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 6);
	return dist(gen);
}

class LUDO {
public:
	string red = "\033[1;31mR\033[0m";
	string blue = "\033[1;34mB\033[0m";

    string hor1 = "+---+---+---+---+---+---+---+---+---+---+---+";
	string hor2 = "+   +---+---+   +---+---+---+   +---+---+   +";
	string hor3 = "+---+---+---+---+---+   +---+---+---+---+---+";

	vector<pair<int, int>> pathRed = {
		{9, 4}, {8, 4}, {7, 4}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {5, 0}, {4, 0},
		{4, 1}, {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 5}, {0, 6},
		{1, 6}, {2, 6}, {3, 6}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10}, {5, 10}, {6, 10},
		{6, 9}, {6, 8}, {6, 7}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {10, 5}, {9, 5}, {8, 5}, {7, 5}, {6, 5}
	};
	vector<pair<int, int>> win_pts = {{10, 5}};
	vector<pair<int, int>> tokenOutPosRed = {{9, 4}};
	int currentPos = 0;

	string arr[11][11] = {
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0" ,"0" ,"1" ,"1" ,"1" ,"0" ,"0" ,"0" ,"0"},
		{"1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1"},
		{"1", "1", "1", "1", "1", "0", "1", "1", "1", "1", "1"},
		{"1", "1", "1", "1", "1", "1", "1", "1", "1", "1", "1"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"},
		{"0", "0", "0", "0", "1", "1", "1", "0", "0", "0", "0"}
	};

    void printBoard(){
        cout << hor1 << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[0][4], arr[0][5], arr[0][6], arr[0][7], arr[0][8], arr[0][9], arr[0][10]);
        cout << hor2 << endl;
        cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[1][0], arr[1][1], arr[1][2], arr[1][3], arr[1][4], arr[1][5], arr[1][6], arr[1][7], arr[1][8], arr[1][9], arr[1][10]);
        cout << hor2 << endl;
        cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[2][0], arr[2][1], arr[2][2], arr[2][3], arr[2][4], arr[2][5], arr[2][6], arr[2][7], arr[2][8], arr[2][9], arr[2][10]);
        cout << hor2 << endl;
        cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[3][0], arr[3][1], arr[3][2], arr[3][3], arr[3][4], arr[3][5], arr[3][6], arr[3][7], arr[3][8], arr[3][9], arr[3][10]);
		cout << hor1 << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[4][0], arr[4][1], arr[4][2], arr[4][3], arr[4][4], arr[4][5], arr[4][6], arr[4][7], arr[4][8], arr[4][9], arr[4][10]);
		cout << hor3 << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {}   {}   {} | {} | {} | {} | {} |\n",arr[5][0], arr[5][1], arr[5][2], arr[5][3], arr[5][4], arr[5][5], arr[5][6], arr[5][7], arr[5][8], arr[5][9], arr[5][10]);
		cout << hor3 << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[6][0], arr[6][1], arr[6][2], arr[6][3], arr[6][4], arr[6][5], arr[6][6], arr[6][7], arr[6][8], arr[6][9], arr[6][10]);
		cout << hor1 << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[7][0], arr[7][1], arr[7][2], arr[7][3], arr[7][4], arr[7][5], arr[7][6], arr[7][7], arr[7][8], arr[7][9], arr[7][10]);
		cout << hor2 << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[8][0], arr[8][1], arr[8][2], arr[8][3], arr[8][4], arr[8][5], arr[8][6], arr[8][7], arr[8][8], arr[8][9], arr[8][10]);
		cout << hor2 << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {} | {} | {} | {} | {} | {} | {} |\n",arr[9][0], arr[9][1], arr[9][2], arr[9][3], arr[9][4], arr[9][5], arr[9][6], arr[9][7], arr[9][8], arr[9][9], arr[9][10]);
		cout << hor2 << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[10][0], arr[10][1], arr[10][2], arr[10][3], arr[10][4], arr[10][5], arr[10][6], arr[10][7], arr[10][8], arr[10][9], arr[10][10]);
		cout << hor1 << endl;
	}

	bool tokenOut(){
		int i, j;
		
		cout<<"Roll the Die: (Press Enter)";
		char enter;
		cin.get(enter);

		int num = dice();
		if (enter == '\n'){
			cout<<num<<endl;
		}

		if (num == 1 || num == 6){
			i = tokenOutPosRed[0].first;
			j = tokenOutPosRed[0].second;
			arr[i][j] = red;
			return true;
		}
		else {
			cout << "You need to roll a 1 or 6 to get your token out!" << endl;
			return false;
		}
		return false;
	}

	void tokenMove(){
		int i, j;
		cout<<"Roll the Die: (Press Enter)";
		char enter;
		cin.get(enter);

		int num = dice();
		
		if (enter == '\n'){
			cout<<"Your Die rolled: "<<num<<endl;
		}
		int pathSizeRed = pathRed.size();

		i = pathRed[currentPos].first;
		j = pathRed[currentPos].second;
		arr[i][j] = " ";
		// New position
		currentPos += num;
		i = pathRed[currentPos].first;
		j = pathRed[currentPos].second;

		arr[i][j] = red;
		
	}
	
	void clearScreen(){
		system("clear");
	}
};

int main() {
    LUDO game;
    while(true){
		game.printBoard();
		if (game.tokenOut()){
			while(true){
				game.printBoard();
				game.tokenMove();
			}
		}

	}

    return 0;
}