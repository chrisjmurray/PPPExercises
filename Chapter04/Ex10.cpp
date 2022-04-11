/*
Write a program that plays the game Rock, Paper, Scissors. If you are not
familiar with the game do some research (e.g., on the web using Google).
Research is a common task for programmers. Use a switch-statement to
solve this exercise. Also, the machine should give random answers (i.e.,
select the next rock, paper, or scissors randomly). Real randomness is too
hard to provide just now, so just build a vector with a sequence of values
to be used as the next value. If you build the vector into the program,
it will always play the same game, so maybe you should let the user enter 
some values. Try variations to make it less easy for the user to guess
which move the machine will make next.
*/

#include "../std_lib_facilities.h"

void printTurnSummary(string userMove, string compMove) {
	cout << "You threw " << userMove << ", your opponent threw " << compMove << '\n';
}

int main() {
	vector<string> strMoves = { "rock", "paper", "scissors" };
	vector<char> charMoves = { 'r', 'p', 's' };
	vector<int> intWinMoves = { 1, 2, 0 }; 
	int threshold = 3;
	int userWins = 0;
	int oppoWins = 0;

	//the logic here is that the user will input r/p/s, we assign to the user the value
    //of the index of the input in charMoves. The values in intWinMoves represent the winning
    //move against the value of that index.
	cout << "First to " << threshold << " points wins. \n";
	while (userWins < threshold && oppoWins < threshold) {
		char input;
		int intUserMove = -1;
		int intCompMove = rand() % 3;

		cout << "\nMake your move (r/p/s): ";
		cin >> input;
		for (int i = 0; i < 3; ++i) {
			if (input == charMoves[i]) {
				intUserMove = i;
			}
		}
		if (intUserMove == -1) continue;
		printTurnSummary(strMoves[intUserMove], strMoves[intCompMove]);
		if (intUserMove == intCompMove) {
			cout << "This turn is a draw \n";
		}
		else if (intCompMove == intWinMoves[intUserMove]) {
			oppoWins += 1;
			cout << "You lost this round!  Your opponent gets a point.\n";
		}
		else {
			userWins += 1;
			cout << "You won this round! You get a point.\n";
		}
	}
	if (userWins > oppoWins) cout << "Congrats! You won the game!\n";
	else cout << "Don't quit your dayjob. You're just not cut out for rock, paper, scissors.\n";
}