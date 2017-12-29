#ifndef GAMESTATE_HEADER
#define GAMESTATE_HEADER

#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "Roles.h"

class Gamestate {
	private:
		const int MIN_FOR_ROLES = 5;
		int _humans;
		int _robots;
		int _wins;
		std::vector<Player*> _players;
		void _initPlayers();
		std::vector<Card> _createHands(int & cardsInEachHand, int & remainders, Deck & cards);
		void _startGame();
		void _turn(Card lastCard, Player * player, int index, int passes);
		int _incrementOrGoBackToZero(int index);
		Roles _findRoleForWinner();

	public: 
		Gamestate();
		Gamestate(int players, int robots);
		void setPlayerAmount(int players);
		void setRobotAmount(int robots);
		void init();
};


#endif