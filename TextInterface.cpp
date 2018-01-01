#include <iostream>
#include <sstream>
#include "Player.h"
#include "Robot.h"
#include "Human.h"
#include "Roles.h"
#include "Card.h"

using namespace std;

void introToGame() {
	cout << "Welcome to Class Struggle!" << endl;
	cout << "There must be a minimum of 5 players if you want roles to be enabled." << endl << endl;
}

void displayGameStart() {
	cout << endl << "-------------------------------GAME START---------------------------------------------" << endl << endl;
}

void askHumanAmount() {
	cout << "How many humans would you like? ";
}

void askRobotAmount() {
	cout << "How many Robots would you like? ";
}

void passOutput(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " decides to pass." << endl;
}

void playerUsesCard(string playerType, int index, Card card, int cardStack) {
	cout << playerType << " #" << index + 1 << " used " << cardStack << " " << card.toString() << "." << endl;
}

void playerClearsHand(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " has cleared their hand." << endl;
}

void playerWonTurnSet(string playerType, int index, Card lastCard) {
	cout << playerType << " #" << index + 1 << " has won this set of turns with a " << lastCard.toString() << "." << endl << endl;
	cout << "-------------------------------NEW TURN SET-------------------------------------------" << endl << endl;
}

void playerWonAlready(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " has emptied their hand already." << endl;
}



int getStackOptions(vector<Card> hand) {
	//13 because that is the amount of values possible. All starting at 0 values.
	vector<int> cardStackValues(13, 0);
	int highestInteger = 0;
	for (int i = 0; i < hand.size(); i++) {
		int value = hand[i].getValue();
		cardStackValues[value - 1]++;
		int amountOfValues = cardStackValues[value - 1];

		if (amountOfValues > highestInteger) {
			highestInteger = amountOfValues;
		}
	}

	return highestInteger;
}

void displayStackOptions(int options) {
	cout << "You may have: ";
	for (int i = 1; i <= options - 1; i++) {
		cout << i << ", ";
	}
	cout << options << " stacked cards for this turn. ";
}

void displayCardStack(int cardStack) {
	cout << "The card stack amount is set to " << cardStack << "!" << endl;
}

void playerGainedRole(string playerType, int index, Roles role) {
	string roleType = "";
	switch (role) {
	case Roles::KING:
		roleType = "KING";
		break;

	case Roles::QUEEN:
		roleType = "QUEEN";
		break;

	case Roles::NEUTRAL:
		roleType = "NEUTRAL";
		break;

	case Roles::SLAVE:
		roleType = "SLAVE";
		break;

	case Roles::SUPER_SLAVE:
		roleType = "SUPER SLAVE";
		break;
	}
	cout << playerType << " #" << index + 1 << " has gained the role of " << roleType << "!" << endl;
}

void gameOver(vector<Player*> _players) {
	string king = "";
	string queen = "";
	vector<string> neutrals;
	string slave = "";
	string superSlave = "";

	for (int i = 0; i < _players.size(); i++) {
		int index = i + 1;
		if (_players[i]->getRole() == Roles::KING) {
			king = _players[i]->name() + " #" + to_string(index);
		}
		else if (_players[i]->getRole() == Roles::QUEEN) {
			queen = _players[i]->name() + " #" + to_string(index);
		}
		else if (_players[i]->getRole() == Roles::NEUTRAL) {
			neutrals.push_back(_players[i]->name() + " #" + to_string(index));
		}
		else if (_players[i]->getRole() == Roles::SLAVE) {
			slave = _players[i]->name() + " #" + to_string(index);
		}
		else if (_players[i]->getRole() == Roles::SUPER_SLAVE) {
			superSlave = _players[i]->name() + " #" + to_string(index);
		}
	}

	cout << endl << "Game over!" << endl;
	cout << "KING: " << king << endl;
	cout << "QUEEN: " << queen << endl;

	for (int k = 0; k < neutrals.size(); k++) {
		cout << "NEUTRALS: " << neutrals[k] << endl;
	}

	cout << "SLAVE: " << slave << endl;
	cout << "SUPER SLAVE: " << superSlave << endl;
}

bool askToContinue() {
	string reply = "";
	cout << "Would you like to play another? (y/n) ";
	cin >> reply;
	
	return reply.find("y") != string::npos;
}

void displayAllCards(std::vector<Card> hand) {
	cout << endl << "Your turn. You have: " << endl;
	for (int i = 1; i < hand.size(); i++) {
		cout << i << ". " << hand[i - 1].toString() << endl;
	}
	cout << hand.size() << ". " << hand.back().toString() << endl;
	cout << hand.size() + 1 << ". Pass" << endl << endl;
}

int askForChoice(int max) {
	string choice = "";
	int choiceNum = -1;
	while (true) {

		cout << "Which option would you like to choose? ";
		cin >> choice;

		std::stringstream choiceToInt(choice);
		choiceToInt >> choiceNum;

		if (choiceNum < 0 || choiceNum > max) {
			cout << "Please choose a valid option." << endl;
		}
		else {
			break;
		}
	}

	return choiceNum;
}

void displayBadCard() {
	cout << "This card is not valid." << endl;
}

void displayRequireCards(int cards) {
	cout << "Please put in " << cards << " more cards." << endl;
}

void displayLastCard(Card lastCard, int cardStack) {
	cout << endl << "LAST CARD PLAYED: ";
	Card emptyCard;
	if (lastCard == emptyCard) {
		cout << "NONE" << endl;
	}
	else {
		cout << cardStack << " " << lastCard.toString() << "." << endl;
	}
}