#include <iostream>
#include "Card.h"

Card::Card() : _value(0), _suit(0), _flipped(false) {

}

Card::Card(int value, int suit, bool flipped) : _value(value), _suit(suit), _flipped(flipped) {

}

int Card::getValue() const {
	return _value;
}

int Card::getSuit() const {
	return _suit;
}

bool Card::isFlipped() const {
	return _flipped;
}

void Card::flip() {
	_flipped = !_flipped;
}

std::string Card::toString() {
	std::string suitType = "";
	const int suit = _suit;
	switch (suit) {
	case 1:
		suitType = "Club";
		break;

	case 2:
		suitType = "Diamond";
		break;

	case 3:
		suitType = "Heart";
		break;

	case 4:
		suitType = "Spade";
		break;
	}

	std::string toString = suitType + " of value " + std::to_string(_value);
	return toString;
}

bool Card::_greaterThanOrEqual(Card c) const {
	int valOne = this->_value;
	int valTwo = c._value;

	int suitOne = this->_suit;
	int suitTwo = c._suit;
	//SAME VALUE CONDITIONS
	//If both cards' vals are same, return true if suitOne is bigger, false if suitTwo is bigger.
	if (valOne == valTwo) {
		return suitOne >= suitTwo;
	}
	//VAL = 2 CONDITION
	//If valOne or valTwo are equaled to 2, return true if valOne is 2 or return false if valTwo is 2.
	else if (valOne == 2 || valTwo == 2) {
		return valOne == 2 && valTwo != 2;
	}
	//VAL = 1 CONDITION
	//If valOne or valTwo are equaled to 1, return true if valOne is 1 or return false if valTwo is 1.
	else if (valOne == 1 || valTwo == 1) {
		return valOne == 1 && valTwo != 1;
	}
	//VAL = ANY OTHER NUMBER CONDITION
	//If its any other number, return true if valOne is bigger, false if valTwo is bigger.
	else {
		return valOne >= valTwo;
	}
}

bool Card::operator>=(const Card & c) const {
	Card cardThis(*this);
	return cardThis._greaterThanOrEqual(c);
}

bool Card::operator<=(const Card & c) const {
	Card cardThis(*this);
	return c._greaterThanOrEqual(cardThis);
}

bool Card::operator==(const Card & c) const {
	return this->_value == c._value && this->_suit == c._suit;
}

bool Card::operator!=(const Card & c) const {
	return this->_value != c._value || this->_suit != c._suit;
}