#include <iostream>
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

void askHumanAmount() {
	cout << "How many humans would you like? ";
}

void askRobotAmount() {
	cout << "How many Robots would you like? ";
}

void passOutput(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " decides to pass." << endl;
}

void playerUsesCard(string playerType, int index, Card card) {
	cout << playerType << " #" << index + 1 << " used a " << card.toString() << "." << endl;
}

void playerClearsHand(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " has cleared their hand." << endl;
}

void playerWonTurnSet(string playerType, int index, Card lastCard) {
	cout << playerType << " #" << index + 1 << " has won this set of turns with a " << lastCard.toString() << "." << endl;
}

void playerWonAlready(string playerType, int index) {
	cout << playerType << " #" << index + 1 << " has emptied their hand already." << endl;
}

void playerGainedRole(string playerType, int index, Roles role) {

}

void displayNoPossibleCards() {

}

int passOrGo() {
	return 0;
}
