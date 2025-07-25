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

	vector<string> p1 = {"\033[1;31m+---+---+\033[0m", "\033[1;34m+---+---+\033[0m", "\033[1;32m+---+---+\033[0m", "\033[1;33m+---+---+\033[0m" };
	vector<string> p2 = {"\033[1;31m+---+\033[0m", "\033[1;34m+---+\033[0m", "\033[1;32m+---+\033[0m", "\033[1;33m+---+\033[0m" };
	string p3 = "\033[1;33m---+---+---+---+\033[0m";
	string p4 = "\033[1;32m+---+---+---+---\033[0m";

	
	bool isRedOut = false, isBlueOut = false;

	string currentPlayer = "Red";

    string hor1 = "+---+---+---+---+---+---+---+---+---+---+---+";

	vector<pair<int, int>> homeRed = {{8, 1}, {8, 2}, {9, 1}, {9, 2}};
	vector<pair<int, int>> pathRed = {
		{9, 4}, {8, 4}, {7, 4}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {5, 0}, {4, 0},
		{4, 1}, {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 5}, {0, 6},
		{1, 6}, {2, 6}, {3, 6}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10}, {5, 10}, {6, 10},
		{6, 9}, {6, 8}, {6, 7}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {10, 5}, {9, 5}, {8, 5}, {7, 5}, {6, 5}, {5, 5}
	};
	vector<pair<int, int>> tokenOutPosRed = {pathRed.at(0)};
	int currentPosRed = 0;

	vector<pair<int, int>> homeBlue = {{1, 8}, {1, 9}, {2, 8}, {2, 9}};
	vector<pair<int, int>> pathBlue = {
		{1, 6}, {2, 6}, {3, 6}, {4, 6}, {4, 7}, {4, 8}, {4, 9}, {4, 10}, {5, 10}, {6, 10},
		{6, 9}, {6, 8}, {6, 7}, {6, 6}, {7, 6}, {8, 6}, {9, 6}, {10, 6}, {10, 5}, {10, 4},
		{9, 4}, {8, 4}, {7, 4}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {5, 0}, {4, 0},
		{4, 1}, {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}
	};
	vector<pair<int, int>> tokenOutPosBlue = {pathBlue.at(0)};
	int currentPosBlue = 0;


	string arr[11][11] = {
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", "W", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "},
		{" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}
	};

    void printBoard(){
        cout << hor1 << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[0][4], arr[0][5], arr[0][6], arr[0][7], arr[0][8], arr[0][9], arr[0][10]);
		cout << "+   "<<p1[2]<<"   +---"<<p1[1]<<"   "<<p1[1]<<	"   +" << endl;
		cout <<fmt::format("| {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} | {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} |\n",arr[1][0], arr[1][1], arr[1][2], arr[1][3], arr[1][4], arr[1][5], arr[1][6], arr[1][7], arr[1][8], arr[1][9], arr[1][10]);
		cout << "+   "<<p1[2]<<"   +---"<<p1[1]<<"   "<<p1[1]<<	"   +" << endl;
		cout <<fmt::format("| {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} | {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} | {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} |\n",arr[2][0], arr[2][1], arr[2][2], arr[2][3], arr[2][4], arr[2][5], arr[2][6], arr[2][7], arr[2][8], arr[2][9], arr[2][10]);
		cout << "+   "<<p1[2]<<"   +---"<<p2[1]<<"---+   "<<p1[1]<<	"   +" << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} | {}   {}   {}   {} |\n",arr[3][0], arr[3][1], arr[3][2], arr[3][3], arr[3][4], arr[3][5], arr[3][6], arr[3][7], arr[3][8], arr[3][9], arr[3][10]);
		cout << "+---"<<p2[2]<<"---+---+---"<<p2[1]<<"---+---+---+---+---+" << endl;
		cout <<fmt::format("| {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} | {} | {} \033[1;34m|\033[0m {} \033[1;34m|\033[0m {} | {} | {} | {} | {} |\n",arr[4][0], arr[4][1], arr[4][2], arr[4][3], arr[4][4], arr[4][5], arr[4][6], arr[4][7], arr[4][8], arr[4][9], arr[4][10]);
		cout << "+---"<<p4<<"+   +"<<p3<<"---+" << endl;
		cout <<fmt::format("| {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {} \033[1;32m|\033[0m {}   {}   {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} |\n",arr[5][0], arr[5][1], arr[5][2], arr[5][3], arr[5][4], arr[5][5], arr[5][6], arr[5][7], arr[5][8], arr[5][9], arr[5][10]);
		cout << "+---"<<p4<<"+   +"<<p3<<"---+" << endl;
		cout <<fmt::format("| {} | {} | {} | {} | {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} | {} | {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} |\n",arr[6][0], arr[6][1], arr[6][2], arr[6][3], arr[6][4], arr[6][5], arr[6][6], arr[6][7], arr[6][8], arr[6][9], arr[6][10]);
		cout << "+---+---+---+---+---"<<p2[0]<<"---+---+---"<<p2[3]<<"---+" << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} | {}   {}   {}   {} |\n",arr[7][0], arr[7][1], arr[7][2], arr[7][3], arr[7][4], arr[7][5], arr[7][6], arr[7][7], arr[7][8], arr[7][9], arr[7][10]);
		cout << "+   "<<p1[0]<<"   +---"<<p2[0]<<"---+   "<<p1[3]<<	"   +" << endl;
		cout <<fmt::format("| {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} | {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} | {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} |\n",arr[8][0], arr[8][1], arr[8][2], arr[8][3], arr[8][4], arr[8][5], arr[8][6], arr[8][7], arr[8][8], arr[8][9], arr[8][10]);
		cout << "+   "<<p1[0]<<"   "<<p1[0]<<"---+   "<<p1[3]<<	"   +" << endl;
		cout <<fmt::format("| {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} \033[1;31m|\033[0m {} | {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} \033[1;33m|\033[0m {} |\n",arr[9][0], arr[9][1], arr[9][2], arr[9][3], arr[9][4], arr[9][5], arr[9][6], arr[9][7], arr[9][8], arr[9][9], arr[9][10]);
		cout << "+   "<<p1[0]<<"   "<<p1[0]<<"---+   "<<p1[3]<<	"   +" << endl;
		cout <<fmt::format("| {}   {}   {}   {} | {} | {} | {} | {}   {}   {}   {} |\n",arr[10][0], arr[10][1], arr[10][2], arr[10][3], arr[10][4], arr[10][5], arr[10][6], arr[10][7], arr[10][8], arr[10][9], arr[10][10]);
		cout << hor1 << endl;
	}

	int tokenOut(){
		int i, j;

		cout<<"Roll the Die Player "<<currentPlayer<<"(Press Enter)";
		cin.ignore();

		int num = dice();
		cout<<"Your die rolled: "<<num<<endl;
		
		if (currentPlayer == "Red"){
			if (num == 1){
				isRedOut = true;
				i = tokenOutPosRed[0].first;
				j = tokenOutPosRed[0].second;
				arr[i][j] = red;
				return 1;
			}
			else if (num == 6){	
				isRedOut = true;
				i = tokenOutPosRed[0].first;
				j = tokenOutPosRed[0].second;
				arr[i][j] = red;
				return 6;
			}
			else {
				isRedOut = false;
				cout << "You need to roll a 1 or 6 to get your token out!" << endl;
				return -1;
			}
		}
		else if (currentPlayer == "Blue"){
			if (num == 1){
				isBlueOut =  true;
				i = tokenOutPosBlue[0].first;
				j = tokenOutPosBlue[0].second;
				arr[i][j] = blue;
				return 1;
			}
			else if (num == 6){	
				isBlueOut =  true;
				i = tokenOutPosBlue[0].first;
				j = tokenOutPosBlue[0].second;
				arr[i][j] = blue;
				return 6;
			}
			else {
				isBlueOut = false;
				cout << "You need to roll a 1 or 6 to get your token out!" << endl;
				return -1;
			}
		}

		return -1;
	}

	void tokenMove(){
		int i, j;
		cout<<"Roll the Die to move it Player "<<currentPlayer<<": (Press Enter)";
		cin.ignore();

		int num = dice(); //For generating a random number between 1 and 6
		
		cout<<"Your Die rolled: "<<num<<endl;

		if (currentPlayer == "Red"){
			int pathSizeRed = pathRed.size(); // sum of all the squares where the red tokens will move
			
			i = pathRed[currentPosRed].first;
			j = pathRed[currentPosRed].second;
			arr[i][j] = " "; // Removing the token from the last position
			
			currentPosRed += num;
			// New position
			if (currentPosRed >= pathSizeRed){
				currentPosRed -= num;
				cout<<"You need to roll "<<pathSizeRed-currentPosRed-1<<" to win\n";
				arr[i][j] = red; // again making the cell red so the space isnt cleared.
			}
			else{
				i = pathRed[currentPosRed].first;
				j = pathRed[currentPosRed].second;

				arr[i][j] = red; // Printing the red token in the new position according to the dice
			}
		}
		else if (currentPlayer == "Blue"){
			int pathSizeBlue = pathBlue.size(); 
			
			i = pathBlue[currentPosBlue].first;
			j = pathBlue[currentPosBlue].second;
			arr[i][j] = " ";
			
			currentPosBlue += num;
			// New position
			if (currentPosBlue >= pathSizeBlue){
				currentPosBlue -= num;
				cout<<"You need to roll "<<pathSizeBlue-currentPosBlue-1<<" to win\n";
				arr[i][j] = blue; 
			}
			else{
				i = pathBlue[currentPosBlue].first;
				j = pathBlue[currentPosBlue].second;

				arr[i][j] = blue; 
			}
		}
	}

	bool tokenCut(){
		int i, j;
	
		if (pathRed[currentPosRed] == pathBlue[currentPosBlue]){
			i = pathRed[currentPosRed].first;
			j = pathRed[currentPosRed].second;

			if (currentPlayer == "Red"){
				currentPosBlue = 0;
				isBlueOut = false;
				arr[i][j] = red;
				cout<<"Sorry Blue you have to go!\n";
			}

			else if (currentPlayer == "Blue"){
				currentPosRed = 0;
				isRedOut = false;
				arr[i][j] = blue;
				cout<<"Sorry Red you have to go!\n";
			}
			return true;
		}
		return false;
	}

	bool winCondition(){
		if (pathRed.size() == currentPosRed+1){
			return true;
		}
		else if (pathBlue.size() == currentPosBlue+1){
			return true;
		}
		else{
			return false;
		}
		return false;
	}

	void switchPlayer(){
		currentPlayer = (currentPlayer == "Red") ? "Blue" : "Red";
	}
	
	void clearScreen(){
		system("clear");
	}
};

int main() {
    LUDO game;
	game.printBoard();
    while(true){

		if (game.currentPlayer == "Red" && game.isRedOut){
			game.tokenMove();
			game.printBoard();
			if (game.tokenCut()){
				continue;
			}
			if (game.winCondition()){
				cout<<"You win Player Red!\n";
				break;
			}
			game.switchPlayer();
		}

		else if (game.currentPlayer == "Blue" && game.isBlueOut){
			game.tokenMove();
			game.printBoard();
			if (game.tokenCut()){
				continue;
			}
			if (game.winCondition()){
				cout<<"You win Player Blue!\n";
				break;
			}
			game.switchPlayer();
		}
		else{
			int result = game.tokenOut();
			if (result == 1){
				game.printBoard();
				game.switchPlayer();
			}
			else if (result == 6){
				game.printBoard();
				game.tokenMove();
				game.printBoard();
				game.switchPlayer();
			}
			else if (result == -1){
				game.switchPlayer();
			}
		}	
	}
    return 0;
}	