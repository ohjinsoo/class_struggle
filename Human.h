#ifndef HUMAN_HEADER
#define HUMAN_HEADER

#include <iostream>
#include "Player.h"
#include "Card.h"

class Human : public Player {
	public:
		Human();
		Human(Roles role);
		Human(std::vector<Card> cards, Roles role);
		std::string name();
		Card pickCard(Card lastCard);
};


#endif