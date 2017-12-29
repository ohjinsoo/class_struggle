#ifndef DECK_HEADER
#define DECK_HEADER

#include <iostream>
#include <vector>
#include "Card.h"

class Deck {
private:
	const int VALUE_SIZE = 13;
	const int SUIT_SIZE = 4;
	const int CARD_SIZE = 52;
	std::vector<Card> _cards;

public:
	Deck();
	void shuffle();
	Card takeTopCard();	
	void newDeck();
	int getSize() const;
	std::vector<Card> getCards() const;

};


#endif