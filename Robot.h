#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <iostream>
#include "Card.h"

class Robot : public Player {

	public:
		Robot();
		Robot(Roles role);
		Robot(std::vector<Card> cards, Roles role);
		Card pickCard(Card lastCard, int cardStack);
		std::string name();
		int chooseCardStack();
};


#endif