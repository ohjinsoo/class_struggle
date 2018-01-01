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

	displayGameStart();

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
				_turn(Card(0, 0, false), _players[i], i, 0, 1);
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

																		   //int cardStack = how many cards the turn set allows. 0 = new turn, player may choose.
void Gamestate::_turn(Card lastCard, Player * player, int index, int passes, int cardStack) {
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
		playerGainedRole(player->name(), index, role);
		gameOver(_players);
		if (askToContinue()) {
			init();
		}
		return;
	}

	//Everyone but original player passed, so make card the weakest and reset passes for the next turn.
	if (passes >= _humans + _robots - 1) {
		//In case player wins turn set with his last card, increment index for next player:
		if (player->getHand().size() == 0) {
			playerWonAlready(player->name(), index);
			index = _incrementOrGoBackToZero(index);
		}
		//Normal turn set win, keep the player in the same index with any card they want to use.
		else {
			playerWonTurnSet(player->name(), index, lastCard);
		}
		lastCard = Card(0, 0, false);
		_turn(lastCard, _players[index], index, 0, 0);
		return;
	}

	//Player has already gotten rid of their hand for this game. Auto pass.
	if (player->getHand().size() == 0) {
		playerWonAlready(player->name(), index);
		passes++;
		index = _incrementOrGoBackToZero(index);
		_turn(lastCard, _players[index], index, passes, cardStack);
		return;
	}

	if (humanp != NULL || robotp != NULL) {
		//If cardStack is at 0, new turnset and you may choose the card stack amount.
		//Else, make Player give the cardStack amount of cards to play.
		
		if (cardStack == 0) {
			cardStack = player->chooseCardStack();
		}

		card = player->pickCard(lastCard, cardStack);
		if (card != emptyCard) {
			playerUsesCard(player->name(), index, card, cardStack);

			//After Player chooses card, check if hand is 0.
			//If hand is 0, give him a role and increase win.
			if (player->getHand().size() == 0) {
				playerClearsHand(player->name(), index);
				_wins++;
				Roles role = _findRoleForWinner();
				player->setRole(role);
				playerGainedRole(player->name(), index, role);
			}

			passes = 0;
			index = _incrementOrGoBackToZero(index);
			_turn(card, _players[index], index, passes, cardStack);
			return;
		}
	}

	//If Player did not trigger any other if statements, means they pass.
	passOutput(player->name(), index);
	passes++;
	index = _incrementOrGoBackToZero(index);
	_turn(lastCard, _players[index], index, passes, cardStack);
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