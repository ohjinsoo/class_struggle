#ifndef CARD_HEADER
#define CARD_HEADER

#include <iostream>

class Card {
private:
	int _value;
	int _suit;
	bool _flipped;
	bool _greaterThanOrEqual(Card c) const;

public:
	Card();
	Card(int value, int suit, bool flipped);
	int getValue() const;
	int getSuit() const;
	bool isFlipped() const;
	void flip();
	std::string toString();
	bool operator>=(const Card & c) const;
	bool operator<=(const Card & c) const;
	bool operator==(const Card & c) const;
	bool operator!=(const Card & c) const;
};


#endif