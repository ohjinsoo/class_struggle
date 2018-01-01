#ifndef HUMAN_HEADER
#define HUMAN_HEADER

#include <iostream>
#include "Player.h"
#include "Card.h"

class Human : public Player {
	private:
		void _removeCardFromHand(Card card);

	public:
		Human();
		Human(Roles role);
		Human(std::vector<Card> cards, Roles role);
		std::string name();
		Card pickCard(Card lastCard, int cardStack);
		int chooseCardStack();
};


#endif