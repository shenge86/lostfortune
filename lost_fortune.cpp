/******** lost_fortune.cpp
* author Shen Ge
* Last Updated:
* 2019.08.08
* Last updated Prior to Last Update: 
* 2019.08.05
* 
*************************/
// begin preprocessor directives
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

// CLASSES
// by convention, class names begin with UPPERCASE letter
// constructor prototype has no return type. It must have same name as class itself

class ITEM {
public:
	ITEM(int HP, int WEIGHT, int SIZE);
	int GetHP() const;
	int GetWEIGHT() const; // kg
	int GetSIZE() const; // cc
	void SetHP(int HP);
	void SetWEIGHT(int WEIGHT);
	void SetSIZE(int SIZE);
private:
	int m_HP;
	int m_WEIGHT;
	int m_SIZE;
};

ITEM::ITEM(int HP, int WEIGHT, int SIZE) {
	m_HP = HP;
	m_WEIGHT = WEIGHT;
	m_SIZE = SIZE;
}

int ITEM::GetHP() const {
	return m_HP;
}

int ITEM::GetWEIGHT() const {
	return m_WEIGHT;
}

int ITEM::GetSIZE() const {
	return m_SIZE;
}

void ITEM::SetHP(int HP) {
	m_HP = HP;
}

void ITEM::SetWEIGHT(int WEIGHT) {
	m_WEIGHT = WEIGHT;
}

void ITEM::SetSIZE(int SIZE) {
	m_SIZE = SIZE;
}

class HUMAN {
public:
	HUMAN(int HP, int ST, int AG, int IT, int LS, int LK);
	int GetHP() const;
	int GetST() const; // strength
	int GetAG() const; // agility
	int GetIT() const; // intelligence
	int GetLS() const; // psion
	int GetLK() const; // luck
	void setHP(int HP);
	void setST(int ST);
	void setAG(int AG);
	void setIT(int IT);
	void setLS(int LS);
	void setLK(int LK);
	void displayStats();
private:
	int m_HP;
	int m_ST;
	int m_AG;
	int m_IT;
	int m_LS;
	int m_LK;
};

HUMAN::HUMAN(int HP, int ST, int AG, int IT, int LS, int LK) { // constructor definition
	m_HP = HP;
	m_ST = ST;
	m_AG = AG;
	m_IT = IT;
	m_LS = LS;
	m_LK = LK;
}

// accessor member function allows indirect access to a data member
int HUMAN::GetHP() const {
	return m_HP;
}

int HUMAN::GetST() const {
	return m_ST;
}

int HUMAN::GetAG() const {
	return m_AG;
}

int HUMAN::GetIT() const {
	return m_IT;
}

int HUMAN::GetLS() const {
	return m_LS;
}

int HUMAN::GetLK() const {
	return m_LK;
}

void HUMAN::setHP(int HP) {
	m_HP = HP;
}

void HUMAN::setST(int ST) {
	m_ST = ST;
}

void HUMAN::setAG(int AG) {
	m_AG = AG;
}

void HUMAN::setIT(int IT)
{
	m_IT = IT;
}

void HUMAN::setLS(int LS)
{
	m_LS = LS;
}

void HUMAN::setLK(int LK) {
	m_LK = LK;
}

void HUMAN::displayStats() {
	cout << "CURRENT STATS:\n";
	cout << "Health: " << GetHP() << "\n";
	cout << "Agility: " << GetAG() << "\n";
	cout << "Intelligence: " << GetIT() << "\n";
	cout << "Leadership: " << GetLS() << "\n";
	cout << "Luck: " << GetLK() << "\n";
}

class Critter { 
public:
	Critter(int hunger = 0); // constructor prototype 
	int GetHunger() const;
	int GetHP() const;
	void SetHunger(int hunger);
	void setHP(int HP);
	void Greet(); // naming convention is that member function start with UPPERCASE letter
private:
	int m_Hunger; // naming convention to put m_ to denote data members
	int m_HP; 
};

// FUNCTIONS
vector<int> readFile(string filename);
void writeFile(string filename, string input);

bool checkDeath(int killed, int adventurers, const int& room, const int& money) {
	if (killed == adventurers) {
		cout << "Alas, you have perished on your journey." << endl;
		// calculate high score
		int highscore = money + room * 3;
		// save score in text file
		string highscoretxt = to_string(highscore);
		writeFile("highscores.txt", highscoretxt);
		
		// exit game
		system("pause");
		return 0;
	}
}

void displayInventory(vector<string> inventory) {
	if (inventory.empty()) {
		cout << "You have nothing at all except the clothes on your back and your boots. Hopefully, your sanity as well.\n";
	}
	else {
		for (unsigned int i = 0; i < inventory.size(); ++i) {
			cout << i << ". ";
			cout << inventory[i] << endl;
		}
	}
}

void showBoard(int ROWS, int COLUMNS, char board[][3]) {
	for (int i = 0; i < ROWS;++i) {
		for (int j = 0;j < COLUMNS;++j) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

void displayHighSchores() {
	vector<int>::const_iterator iter;
	vector<int> scores;
	scores = readFile("highscores.txt");

	scores.push_back(1500);
	scores.push_back(2500);
	scores.push_back(4500);

	cout << "\nHigh Scores:\n";
	for (iter = scores.begin(); iter != scores.end(); ++iter) {
		cout << *iter << endl;
	}

	int score;
	cout << "\nEnter a score to find: ";
	cin >> score;

	iter = find(scores.begin(), scores.end(), score);
	if (iter != scores.end()) {
		cout << "Scores found.\n";
	}
	else {
		cout << "Scores not found.\n";
	}

	cout << "\nRandomizing scores.";
	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(scores.begin(), scores.end());
	cout << "\nHigh Scores:\n";
	for (iter = scores.begin(); iter != scores.end(); ++iter) {
		cout << *iter << endl;
	}

	cout << "\nSorting scores.";
	sort(scores.begin(), scores.end());
	cout << "\nHigh Scores:\n";
	for (iter = scores.begin(); iter != scores.end(); ++iter) {
		cout << *iter << endl;
	}
}

//**************************************************************************************//
int main() {
	// CONSTANTS & VARIABLES
	int money, killed, survivors;
	unsigned int choicenum;
	string leader;
	const int GOLD_PIECES = 9000;
	int adventurers = 0;
	int adventurercost = 500;
	int room = 0;

	const int MAX_ITEMS = 10;

	// hero's inventory with starting items
	vector<string> inventory;
	inventory.push_back("steel short sword");
	inventory.push_back("fine leather armor");
	inventory.push_back("steel dagger");

	const int ROWS = 3;
	const int COLUMNS = 3;
	char board[ROWS][COLUMNS] = { {'0', 'X', '0'}, {' ', 'X', 'X'}, {'X','O','O'} };

	// if random number generator here is not used, it will output the same sequence of random numbers every time it is run.
	srand(static_cast<unsigned int>(time(0))); // seed random number generator
	int secretNumber = rand() % 100 + 1;
	int tries = 0;
	int guess;

	// SHOW HIGH SCORES
	cout << "Welcome to Lost Fortune " << string(3, '!') << " \n";
	cout << "Conceived from the mind of Shen Ge \n\n";
	
	// START GAME
	cout << "**********************************" << endl;
	cout << "1. NEW GAME\n";
	cout << "2. LOAD PREVIOUS GAME \n";
	cout << "3. HIGH SCORES \n";
	cout << "4. QUIT \n";
	choicenum = 0;
	do {
		cout << "Please choose an option: ";
		// cin returns false if an input operation fails, that is, if
		// something other than an int (the type of input_var) is entered.
		if (!(cin >> choicenum)) {
			cout << "Please enter numbers only." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
	} while (choicenum != 1 && choicenum != 2 && choicenum !=3 && choicenum != 4);

	switch (choicenum) {
	case 1:
		cout << "STARTING NEW GAME\n";
		cout << "They say that traveling to the outer reaches of the Sagitarrius arm of the Milky Way on a scouting ship is one of the least exciting things to do. One of these days, some genius will figure out faster than light travel but for now, even traveling at the breakneck speed of 0.2c, the journey will still take another 10 years to reach the next star system. That genius will not be me though I do consider myself fairly intelligent. \n\n Outside, there's just empty black space. No nebulas or other star systems in this empty but direct path to Alpha Centauri. Bored, what is there to do but play a game called Lost Fortune? The interesting thing about this according to other crew members that have played it is that it does not allow the player to save at all during the game but it does save automatically upon exiting the game or when you die. When you restart the game, you start from the beginning again with different choices each time depending on your current stats. In this way, it's both simple and yet dynamic. The developers is an engineering geek down the hall who is channeling his boredom in a productive manner. I, on the other hand, just happens to be a consumer rather than creator. Well, where one person creates, there always needs to be ten more that consumes. \n\n Without further ado, I'll boot up this thing.\n\n";
		break;
	case 2:
		cout << "No saved game found. Let's start with a new game!\n";
		break;
	case 3:
		displayHighSchores();
		system("pause");
		break;
	case 4:
		return 0;
	default:
		break;
	}

	// ===== START ACTUAL GAME ===== //
	cout << "What is your name?\n";
	cin >> leader;

	HUMAN player(10, 3, 4, 2, 3, 5);
	cout << "STATS \n";
	player.displayStats();
	
	cout << "Undertaking a new journey is never easy, especially one to a different star system. There is a lot more bad than good that can be said about Earth. The planet is polluted, crowded and severely lacking in job opportunities. With some hard-earned cash through almost a decade working for a giant conglomerate, you're finally ready to be an independent explorer to settle a planet within reach. Recent star charts have revealed numerous potential habitable planets within 20 light years. You plan to hire a small crew with your credits and start your journey. No doubt it'll be perilous but all gain requires some risk.\n\n";

	// randomize starting monetary amount
	money = GOLD_PIECES + (rand() % 10000);
	cout << "You check your account and see that you have " << money << " credits" << endl;

	cout << "From what you see, each crew member requires " << adventurercost << " credits to hire.";
	cout << "You have to hire at least a navigator and a pilot. You go ahead and do so.";
	adventurers += 2;

	cout << "You have some more money to spare and you're thinking that you want to hire a few more crew. You decide to hire how many additional crewmembers? \n";
	cin >> adventurers;

	// hire 3 at a minimum
	if (adventurers == 0) {
		cout << "Hiring no one else sounds very risky. You decide to hire three more people.";
		adventurers += 3;
	}

	// if more money than you can afford, then set to max number of people you bought and set money to 0
	if (adventurercost * adventurers > money) {
		cout << "You realize that you don't have enough money to hire this many people so you decide to hire as many as you can.";
		cout << " You hired " << money / adventurercost << " more people.";
		adventurers += money / adventurercost;
	}

	money -= adventurercost * adventurers;
	cout << "You have " << money << " credits left.";
	adventurers++; // include yourself here from now on

	cout << "\nYou are now ready to begin your journey. With a last look at Earth, you set off towards the distant world of " << "planet X" << " with your crew of " << adventurers << "."; // randomize planet

	// START ADVENTURE

	// displayInventory(inventory);

	
	// cin.get();
	// getchar();
	system("pause");
    return 0;
} 

//**************************************************************************************//

// SYSTEM FUNCTIONS
vector<int> readFile(string filename) {
	string line;
	vector<int> scores;
	int score;
	string::size_type sz;   // alias of size_t

	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
			// add to vector
			score = stoi(line, &sz);
			scores.push_back(score);
		}
		myfile.close();
	} else cout << "Unable to open file";

	return scores;
}

void writeFile(string filename, string input) {
	ofstream myfile(filename);
	if (myfile.is_open())
	{
		myfile << input;
		myfile.close();
	}
	else cout << "Unable to open file";
}