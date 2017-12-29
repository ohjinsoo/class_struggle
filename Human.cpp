#include <iostream>
#include <vector>
#include "Human.h"
#include "Player.h"
#include "Card.h"
#include "Roles.h"
#include "TextInterface.h"

Human::Human() : Player() {
}

Human::Human(Roles role) : Player(role) {
}

Human::Human(std::vector<Card> cards, Roles role) : Player(cards, role) {
}

std::string Human::name() {
	return "Human";
}

Card Human::pickCard(Card lastCard) {
	displayAllCards(_hand);

	while (true) {
		int cardChoice = askForCardChoice(_hand.size() + 1) - 1;

		//If the choice is equal to hand size, that means they choice to pass.
		//emptyCard = pass.
		if (cardChoice == _hand.size()) {
			Card emptyCard;
			return emptyCard;
		}

		Card humanCard = _hand[cardChoice];
		if (humanCard >= lastCard) {
			_hand.erase(_hand.begin() + cardChoice);
			return humanCard;
		}
		else {
			displayBadCard();
		}
	}
}