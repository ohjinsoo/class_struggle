#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <iostream>
#include <vector>
#include "Roles.h"
#include <iostream>
#include <vector>
#include "Card.h"

class Player {
protected:
	std::vector<int> _amountOfValue;
	std::vector<Card> _hand;
	Roles _role;

public:
	//13 because that is the amount of values possible. All starting at 0 values.
	Player() :_amountOfValue(std::vector<int>(13, 0)), _hand(std::vector<Card>(0)), _role(Roles::NEUTRAL)  {
	}

	Player(Roles role) : _amountOfValue(std::vector<int>(13, 0)), _hand(std::vector<Card>(0)), _role(role) {
	}

	Player(std::vector<Card> cards, Roles role) : _amountOfValue(std::vector<int>(13, 0)), _hand(cards), _role(role) {
		updateAmountOfValue();
	}
	void setRole(Roles role) {
		_role = role;
	}

	Roles getRole() {
		return _role;
	}

	std::vector<Card> getHand() {
		return _hand;
	}

	void setHand(std::vector<Card> hand) {
		_hand = hand;
		updateAmountOfValue();
	}


	void printAll() {
		for (int i = 0; i < _hand.size(); i++) {
			std::cout << _hand[i].toString() << std::endl;
		}
	}

	void updateAmountOfValue() {
		_amountOfValue = std::vector<int>(13, 0);
		for (int i = 0; i < _hand.size(); i++) {
			int value = _hand[i].getValue();
			_amountOfValue[value - 1]++;
		}
	}

	void removeCardFromHand(Card card) {
		for (int i = 0; i < _hand.size(); i++) {
			if (card == _hand[i]) {
				_hand.erase(_hand.begin() + i);
				return;
			}
		}
	}

	void addCardToHand(Card card) {
		_hand.push_back(card);
	}
	
	virtual int chooseCardStack() = 0;
	virtual std::string name() = 0;
	virtual Card pickCard(Card lastCard, int cardStack) = 0;
};


#endif