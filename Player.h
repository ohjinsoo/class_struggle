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
	std::vector<Card> _hand;
	Roles _role;

public:
	Player() :_hand(std::vector<Card>(0)), _role(Roles::NEUTRAL) {
	}

	Player(Roles role) : _hand(std::vector<Card>(0)), _role(role) {
	}

	Player(std::vector<Card> cards, Roles role) :_hand(cards), _role(role) {
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
	}

	void printAll() {
		for (int i = 0; i < _hand.size(); i++) {
			std::cout << _hand[i].toString() << std::endl;
		}
	}
	
	virtual std::string name() = 0;
	virtual Card pickCard(Card lastCard) = 0;
};


#endif