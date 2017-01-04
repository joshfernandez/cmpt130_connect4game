/*	Assignment # 5: Connect 4
 *	By Josh Arik Miguel Fernandez | Student Number: 301246300
 *	CMPT 130 (Fall 2014) with Dr. Toby Donaldson
 *
 *  	CREDITS:
 *
 *  	I would like to thank the following for making my fourth program possible:
 *     	-	Dr. Toby Donaldson, for teaching us more ways C++ has benefited the world,
 *     	-	Dr. Donaldson's course notes website, from Chapters 1 through 10,
 *      -   The CMPT 130 course book "Problem Solving with C++"(7th Edition)" by Walter Savitch,
 *     	-	My friends - William Dang, Lawrence Yu, Faisal Al-Humaimidi, Ahnaf Aziz, 
 *			Andrew Magdurulan, Aaaqil Hassan, and Razvan Cretu.
 *
 * 		I have also included pre-conditions, post-conditions, and explanations on how the program works.
 * 		I hope you enjoy it!
 *      Note: If I had more time, I would have also done the hard level. I hope you understand.
 */	

// a5.cpp

#include <iostream>
#include "error.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

//-----------------------------------------------------------------------------
// VECTORS USED FOR THIS PROGRAM:

vector<char> label = 
	 {'A','B','C','D','E','F','G'};

vector<char> between =
	{' ', '|', '[', ']'};

vector<vector<int>> board = 
	{{0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0},
	 {0,0,0,0,0,0,0}};

//-----------------------------------------------------------------------------
// FUNCTIONS USED FOR THIS PROGRAM:

void display_board(){
	// This just displays the board every time the user or the computer makes its move.
	cout << "=============================\n";

	for(int i = 0; i < 7; ++i){
		cout << "| " << label[i] << " ";
	}
	cout << "|\n=============================\n";

	for(int i = 0; i < 6; ++i) {
        for(int j = 0; j < 7; ++j) {
        	// The order of rows are from top to bottom.
        	if(board[5-i][j] == 1 || board[5-i][j] == 2){
                cout << "| " << board[5-i][j] << " ";
            } else {
            	cout << "|   ";
            }
        }
        cout << "|\n-----------------------------\n";
    }

}

void reset_board(){
	// This resets the board after every round.

	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 7; j++){
			board[i][j] = 0;
		}
	}

}

void player_1_turn(){
	// This is player one's (your) turn.

	srand(time(NULL)); // This gives player 2 time to decide their column; "Segmentation fault" otherwise.
	char player1; // This represents the column player one chooses.
	int column1 = 0;
	int row1 = 0;

    cout << "Player 1's turn. Pick a column to drop your piece (from A to G):  ";
    cin >> player1;

    player1 = toupper(player1); // This will accept lowercase letters as well.

    if (player1 >= 'A' && player1 <= 'G'){
    	
    	column1 = static_cast<int>(player1) - 65; // This converts the column to an integer.
    	
    	for(int i = 0; i < 6; i++){
    		if(board[i][column1] != 0) row1++;// This solves the "gravity" row position.
    		if(row1 == 6) {
    			cout << "This column is already filled. Please try again.\n";
    			player_1_turn();
    			row1 = 0;
    			break;
    		}
    	}
    	
    	board[row1][column1] = 1;// This displays the "1" for the corresponding cell.
    	row1 = 0;// This resets the row back to the ground.
    } else {
    	// This happens if player one does not input any of the columns.
    	cout << "The column you chose was out of range. Please try again.\n";
    	player_1_turn();
    }

}

void player_2_turn_easy(){
	// This is player two's (computer's) turn.

	int player2_answer = rand() % 7; //This is player two's answer between 0 and 6.
	char player2;// This represents the column player two chooses.
	int column2 = 0;
	int row2 = 0;

	column2 = player2_answer;
	player2 = static_cast<char>(player2_answer + 'A');
    player2 = toupper(player2);

    if (player2 >= 'A' && player2 <= 'G'){
    	
    	for(int i = 0; i < 6; i++){
    		if(board[i][column2] != 0) row2++;
    		if(row2 == 6) {// This is what happens when a column is filled.
    			player_2_turn_easy();
    			row2 = 0;
    			break;
    		}
    	}

    	board[row2][column2] = 2; //This displays 2 for the corresponding cell.
    	row2 = 0;
    }

}

int player_1_check(int& score){
	// This checks four-in-a-rows for player one.

	score = 0;

	for(int i = 0; i < 6; i++) {
    	for(int j = 0; j < 4; j++) {
            if(board[i][j] == 1 && board[i][j+1] == 1 && board[i][j+2] == 1 && board[i][j+3] == 1){
            	cout << "Player 1 wins horizontally.\n";
            	score = 1;
            }
		}
	}

	for(int i = 0; i < 3; i++) {
    	for(int j = 0; j < 7; j++) {
            if(board[i][j] == 1 && board[i+1][j] == 1 && board[i+2][j] == 1 && board[i+3][j] == 1){
            	cout << "Player 1 wins vertically!\n";
            	score = 1;
            }
		}
	}

	for(int i = 5; i >= 3; i--) {
    	for(int j = 0; j < 4; j++) {
            if(board[i][j] == 1 && board[i-1][j+1] == 1 && board[i-2][j+2] == 1 && board[i-3][j+3] == 1){
            	cout << "Player 1 wins diagonally to the right!\n";
            	score = 1;
            }
		}
	}

	for(int i = 5; i >= 3; i--) {
    	for(int j = 6; j >= 3; j--) {
            if(board[i][j] == 1 && board[i-1][j-1] == 1 && board[i-2][j-2] == 1 && board[i-3][j-3] == 1){
            	cout << "Player 1 wins diagonally to the left!\n";
            	score = 1;
            }
		}
	}

	return score;

}

int player_2_check(int& score){
	// This checks the four-in-a-rows for player two.

	score = 0;

	for(int i = 0; i < 6; i++) {
    	for(int j = 0; j < 4; j++) {
            if(board[i][j] == 2 && board[i][j+1] == 2 && board[i][j+2] == 2 && board[i][j+3] == 2){
            	cout << "Player 2 wins horizontally!\n";
            	score = 1;
            }
		}
	}

	for(int i = 0; i < 3; i++) {
    	for(int j = 0; j < 7; j++) {
            if(board[i][j] == 2 && board[i+1][j] == 2 && board[i+2][j] == 2 && board[i+3][j] == 2){
            	cout << "Player 2 wins vertically!\n";
            	score = 1;
            }
		}
	}

	for(int i = 5; i >= 3; i--) {
    	for(int j = 0; j < 4; j++) {
            if(board[i][j] == 1 && board[i-1][j+1] == 1 && board[i-2][j+2] == 1 && board[i-3][j+3] == 1){
            	cout << "Player 2 wins diagonally to the right!\n";
            	score = 1;
            }
		}
	}

	for(int i = 5; i >= 3; i--) {
    	for(int j = 6; j >= 3; j--) {
            if(board[i][j] == 1 && board[i-1][j-1] == 1 && board[i-2][j-2] == 1 && board[i-3][j-3] == 1){
            	cout << "Player 2 wins diagonally to the left!\n";
            	score = 1;
            }
		}
	}

	return score;

}

//------------------------------------------------------------------------------

int main() {

	system("clear"); // This is to clear the console.
	// http://www.cplusplus.com/forum/beginner/3304/

	// PART A - Introduce the game and introduce your variables.

	cout << "==============================================================\n\n";
	cout << "Welcome to Connect 4!\n\n";

	int p1_prev = 0;
	int p2_prev = 0;
	int p1_score = 0;
	int p2_score = 0;
	int p1_count = 0;
	int p2_count = 0;
	int num_rounds = 0;
	int count_cells = 0;

	// PART B - Start each round.

	for(;;){

		string answer = "";
		cout << "Do you want to start a new game (Yes or No)?\n";
		cin >> answer;

		for (int i = 0; i < answer.size(); i++){
			answer[i] = tolower(answer[i]); // This includes uppercase and lowercase letters.
		}

		system("clear"); // This clears the system before starting a new round.

		if (answer == "yes"){

			// PART C - Start the round by displaying the blank board.

			display_board();

			for(;;){
				
				p1_count = 0;
				p2_count = 0;
				count_cells = 0;

				// PART D - This method alternates who starts first.

				// PART E - Each turn starts off by making the turn, clearing the console, and
				// displaying the board. The "count" integer is used to check the four in a rows. 
				// If there is one, set it to 1. There are situations, however, when it is five 
				// or more in a row. Force the score to become 1. This "count" decides whether a
				// round ends or not. If it's 1, it means the round ended. If not, continue.
				// At the end, "count_cells" decides if the board is filled with 1s and 2s. If so,
				// this ends the round with a draw and keeps the scores as is.

				if (num_rounds % 2 == 0){

					player_1_turn();
				   	system("clear");
				   	display_board();
				   	p1_count = player_1_check(p1_score);
				   	if(p1_count >= 1) p1_count = 1;
				   	if(p1_count != 0){
				   		reset_board();
				   		p1_prev++;
				   		num_rounds++;
				   		p1_count = 0;
				   		break;
				   	}
					count_cells++;

					player_2_turn_easy();
				   	system("clear");
				   	display_board();
				   	p2_count = player_2_check(p2_score);
				   	if(p2_count >= 1) p2_count = 1;
				   	if(p2_count != 0){
				   		reset_board();
				   		p2_prev++;
				   		num_rounds++;
				   		p2_count = 0;
				   		break;
				   	}
					count_cells++;

					if(count_cells == 42){
						cout << "This is a draw!\n";
						reset_board();
						break;
					}

				} else {
					
					player_2_turn_easy();
				   	system("clear");
				   	display_board();
				   	p2_count = player_2_check(p2_score);
				   	if(p2_count >= 1) p2_count = 1;
				   	if(p2_count != 0){
				   		reset_board();
				   		p2_prev++;
				   		num_rounds++;
				   		p2_count = 0;
				   		break;
				   	}
					count_cells++;

					player_1_turn();
				   	system("clear");
				   	display_board();
				   	p1_count = player_1_check(p1_score);
				   	if(p1_count >= 1) p1_count = 1;
				   	if(p1_count != 0){
				   		reset_board();
				   		p1_prev++;
				   		num_rounds++;
				   		p1_count = 0;
				   		break;
				   	}
					count_cells++;

					if(count_cells == 42){
						cout << "This is a draw!\n";
						count_cells = 0;
						reset_board();
						break;
					}
				}

		   	}

		   	// PART F - This displays the scores after each round.

				cout << "\n--------------------------------------------------------------\n";
				cout << "Player 1 (You): " << p1_prev << "\t\tPlayer 2 (Computer): " << p2_prev;
				cout << "\n--------------------------------------------------------------\n\n";

		} else if (answer == "no"){

			// PART G - This displays the scores after the game.

			cout << "\n-------------------------GAME OVER----------------------------\n";
			cout << "Player 1 (You): " << p1_prev << "\t\tPlayer 2 (Computer): " << p2_prev;
			cout << "\n--------------------------------------------------------------\n\n";
			cout << "Thanks for playing Connect 4. I hope you enjoyed it!\n";

			cout << "\n==============================================================\n";
			exit(EXIT_SUCCESS); // More formal substitution for return 0;
			// http://www.cplusplus.com/reference/cstdlib/exit/

			// PART H - This happens if the user's answer isn't yes or no.

		} else cout << "Sorry. Invalid answer. Please try again.\n\n";

	}
} // end of main