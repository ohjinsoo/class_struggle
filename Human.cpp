#include <iostream>
#include <vector>
#include "Human.h"
#include "Player.h"
#include "Card.h"
#include "Roles.h"
#include "TextInterface.h"

Human::Human() : Player() {
}

Human::Human(Roles role) : Player(role) {
}

Human::Human(std::vector<Card> cards, Roles role) : Player(cards, role) {
}

std::string Human::name() {
	return "Human";
}

Card Human::pickCard(Card lastCard, int cardStack) {
	displayAllCards(_hand);
	displayPass(_hand.size() + 1);
	displayLastCard(lastCard, cardStack);
	int valueOfChosenCard = 0;
	bool firstCard = true;
	int choicesAmount = _hand.size() + 1;
	while (true) {
		int cardChoice = askForChoice(choicesAmount) - 1;

		//If the choice is equal to hand size, that means they chose to pass.
		//Only applies to if they havent chosen a card yet. If they did choose a card and now have to choose cards that stack, cannot pass.
		if (cardChoice == _hand.size() && firstCard) {
			Card emptyCard;
			return emptyCard;
		}

		Card humanCard = _hand[cardChoice];
		int value = humanCard.getValue();
		
		/*
			MUST FULFILL 3 REQS:
				1. humnacard is better than lastcard
				2. the amount of human cards in the deck is bigger or equal to cardstack amount
				3. the value of humancard is the same as 'chosen card' aka the value of the cards chosen before (this is for stacking purposes).
				   (this rule does not apply if valueofchosencard is 0, meaning the chosen card hasn't been chosen yet).
		*/

		if (humanCard >= lastCard && _amountOfValue[value - 1] >= cardStack && ( valueOfChosenCard == value || valueOfChosenCard == 0 )) {

			removeCardFromHand(humanCard);

			if (cardStack == 1) {
				return humanCard;
			}
			else {
				//-= 2 to eliminate passing.
				//-- as you only need to eliminate passing once.
				if (firstCard) {
					choicesAmount -= 2;
				}
				else {
					choicesAmount--;
				}
				firstCard = false;
				displayAllCards(_hand);
				valueOfChosenCard = value;
				cardStack--;
				displayRequireCards(cardStack);
			}
		}
		else {
			displayBadCard();
		}
	}
}

int Human::chooseCardStack() {
	int stackOptions = getStackOptions(_hand);
	if (stackOptions == 1) {
		return 1;
	}
	displayStackOptions(stackOptions);
	int cardStack = askForChoice(stackOptions);
	displayCardStack(cardStack);

	return cardStack;
}