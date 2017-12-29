#include <iostream>
#include <vector>
#include "Gamestate.h"
#include "Player.h"
#include "Robot.h"
#include "Human.h"
#include "Deck.h"
#include "Card.h"
#include "Roles.h"
#include "TextInterface.h"

Gamestate::Gamestate() : _humans(0), _robots(0), _players(0), _wins(0) {
}

Gamestate::Gamestate(int humans, int robots) : _humans(humans), _robots(robots), _players(std::vector<Player*>(0)), _wins(0) {
}

void Gamestate::setPlayerAmount(int humans) {
	_humans = humans;
}

void Gamestate::setRobotAmount(int robots) {
	_robots = robots;
}

void Gamestate::init() {
	//Check if humans and robots is more than 1 combined.
	if (_humans + _robots < 1) {
		return;
	}

	//If players size isn't the same as amount of humans and robots, means new game, initialize _players with Humans and Robots.
	if (_players.size() != _humans + _robots) {
		_initPlayers();
	}

	//Shuffle deck of cards.
	Deck cards;
	cards.shuffle();

	//Find out how many cards should be in each hand + remainders.
	int amountOfPlayers = _humans + _robots;
	int cardsInEachHand = cards.getSize() / amountOfPlayers;
	int remainders = cards.getSize() % amountOfPlayers;

	//Creates a unique hand for the Human inside _players.
	for (int k = 0; k < _humans; k++) {
		std::vector<Card> humandHand = _createHands(cardsInEachHand, remainders, cards);
		_players[k]->setHand(humandHand);
	}
	//Creates a unique hand for the Robot inside _players.
	for (int k = _humans; k < amountOfPlayers; k++) {
		std::vector<Card> robotHand = _createHands(cardsInEachHand, remainders, cards);
		_players[k]->setHand(robotHand);
	}

	_wins = 0;
	_startGame();
}

void Gamestate::_initPlayers() {
	for (int k = 0; k < _humans; k++) {
		Human * human = new Human(Roles::NEUTRAL);
		_players.push_back(human);
	}

	for (int k = 0; k < _robots; k++) {
		Robot * robot = new Robot(Roles::NEUTRAL);
		_players.push_back(robot);
	}
}

std::vector<Card> Gamestate::_createHands(int & cardsInEachHand, int & remainders, Deck & cards) {
	std::vector<Card> hand(0);
	for (int i = 0; i < cardsInEachHand; i++) {
		hand.push_back(cards.takeTopCard());
	}

	if (remainders > 0) {
		hand.push_back(cards.takeTopCard());
		remainders--;
	}

	return hand;
}

void Gamestate::_startGame() {
	for (int i = 0; i < _players.size(); i++) {
		std::vector<Card> playerHand = _players[i]->getHand();

		for (int k = 0; k < playerHand.size(); k++) {
			if (playerHand[k].getValue() == 3 && playerHand[k].getSuit() == 1) {
				_turn(Card(3, 0, false), _players[i], i, 0);
				return;
			}
		}
	}
}

/*
	POSSIBLE SCENARIOS:
		1 No possible move. Then pass.
		2 Possible move:
			3 ->If Robot, choose the next highest card.
			4 ->If Human:
					5 -> Choose any card they want to use.
					6 -> Pass.

		7 Everyone passes:
					8 -> Game Ends, all players but one have cleared their hand.
					9 -> New turn for the next active player:
													10 -> Nobody cleared hand, continue playing.
													11 -> Someone cleared hand. Give them role of their appropriate status.

*/
void Gamestate::_turn(Card lastCard, Player * player, int index, int passes) {
	Robot * robotp = dynamic_cast<Robot*>(player);
	Human * humanp = dynamic_cast<Human*>(player);
	Card emptyCard;
	Card card;
	
	//Game is over, find the last person with cards in their hand and give them SUPER_SLAVE.
	//Keep going through _turn until you find the player.
	if (_wins == _players.size() - 1 && player->getHand().size() > 0) {
		_wins++;
		Roles role = _findRoleForWinner();
		player->setRole(role);

		gameOver(_players);
		if (askToContinue()) {
			init();
		}
		return;
	}

	//Player has already gotten rid of their hand for this game. Auto pass.
	if (player->getHand().size() == 0) {
		playerWonAlready(player->name(), index);
		passes++;
		index = _incrementOrGoBackToZero(index);
		_turn(lastCard, _players[index], index, passes);
		return;
	}

	if (humanp != NULL || ( robotp != NULL && robotp->possibleMove(lastCard)) ) {
		card = player->pickCard(lastCard);
		if (card != emptyCard) {
			playerUsesCard(player->name(), index, card);
		}
	}

	//After Player either passes or chooses card, check if hand is 0.
	//If hand is 0, give him a role and increase win.
	if (player->getHand().size() == 0) {
		_wins++;
		Roles role = _findRoleForWinner();
		player->setRole(role);
	}

	//If card isn't an empty card, Player chose a card to use. So use it and reset passes.
	if (card != emptyCard) {
		passes = 0;
		index = _incrementOrGoBackToZero(index);
		_turn(card, _players[index], index, passes);
		return;
	}

	//If the card is empty, that means they passed.
	//Either case, index will be incremented.
	passOutput(player->name(), index);
	passes++;
	index = _incrementOrGoBackToZero(index);

	//Everyone but original player passed, so make card the weakest and reset passes for the next turn.
	if (passes >= _humans + _robots - 1) {
		playerWonTurnSet(_players[index]->name(), index, lastCard);
		lastCard = Card(3, 1, false);
		passes = 0;
	}

	//If its just normal passing, send it to next player.
	_turn(lastCard, _players[index], index, passes);
}

int Gamestate::_incrementOrGoBackToZero(int index) {
	int i = index + 1;

	if (i >= _players.size()) {
		i = 0;
	}

	return i;
}

Roles Gamestate::_findRoleForWinner() {
	int size = _players.size();

	if (size < MIN_FOR_ROLES) {
		return Roles::NEUTRAL;
	}
	else if (_wins == 1) {
		return Roles::KING;
	}
	else if (_wins == 2) {
		return Roles::QUEEN;
	}
	else if (_wins == size - 1) {
		return Roles::SLAVE;
	}
	else if (_wins == size) {
		return Roles::SUPER_SLAVE;
	}
	else {
		return Roles::NEUTRAL;
	}
}