#include <iostream>
#include <vector>
#include "TextInterface.h"
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


std::string Robot::name() {
	return "Robot";
}

Card Robot::pickCard(Card lastCard, int cardStack) {
	Card emptyCard;
	Card buffer;
	int index = -1;
	for (int k = 0; k < cardStack; k++) {
		buffer = emptyCard;
		for (int i = 0; i < _hand.size(); i++) {
			Card card = _hand[i];
			if (card >= lastCard && _amountOfValue[card.getValue() - 1] >= cardStack && (buffer == emptyCard || card <= buffer)) {
				index = card.getValue() - 1;
				buffer = card;
			}
		}
		removeCardFromHand(buffer);
	}

	if (index > -1) {
		_amountOfValue[index] -= cardStack;
	}
		return buffer;
}

//Robot always chooses the highest stack option.
int Robot::chooseCardStack() {
	return getStackOptions(_hand);
}