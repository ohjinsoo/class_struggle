#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <iostream>
#include "Card.h"

class Robot : public Player {
	private:
		void _removeBufferFromHand(Card card);

	public:
		Robot();
		Robot(Roles role);
		Robot(std::vector<Card> cards, Roles role);
		Card pickCard(Card lastCard);
		std::string name();
		bool possibleMove(Card lastCard);
};


#endif