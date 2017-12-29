#include <iostream>
#include <vector>
#include "Human.h"
#include "Robot.h"
#include "Card.h"
#include "Roles.h"

Robot::Robot() : Player() {
}

Robot::Robot(Roles role) : Player(role) {
}

Robot::Robot(std::vector<Card> cards, Roles role) : Player(cards, role) {
}

bool Robot::possibleMove(Card lastCard) {
	for (int i = 0; i < _hand.size(); i++) {
		if (_hand[i] >= lastCard) {
			return true;
		}
	}

	return false;
}

std::string Robot::name() {
	return "Robot";
}

Card Robot::pickCard(Card lastCard) {
	Card emptyCard;
	Card buffer;
	for (int i = 0; i < _hand.size(); i++) {
		if (_hand[i] >= lastCard) {
			if (buffer == emptyCard || _hand[i] <= buffer) {
				buffer = _hand[i];
			}
		}
	}

	_removeBufferFromHand(buffer);
	return buffer;
}

void Robot::_removeBufferFromHand(Card card) {
	for (int i = 0; i < _hand.size(); i++) {
		if (card == _hand[i]) {
			_hand.erase(_hand.begin() + i);
			return;
		}
	}
}