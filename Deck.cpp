#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Deck.h"
#include "Card.h"


Deck::Deck() : _cards(0) {
	newDeck();
}

void Deck::shuffle() {
	srand((unsigned)time(NULL));

	for (int i = 0; i < CARD_SIZE; i++) {
		Card tmpCard = _cards[i];
		int randPlacement = rand() % CARD_SIZE;

		_cards[i] = _cards[randPlacement];
		_cards[randPlacement] = tmpCard;
	}
}
Card Deck::takeTopCard() {
	Card top = _cards.back();
	_cards.pop_back();
	return top;
}

void Deck::newDeck() {
	_cards = std::vector<Card>(0);

	for (int i = 0; i < VALUE_SIZE; i++) {
		for (int k = 0; k < SUIT_SIZE; k++) {
			Card tmpCard(i + 1, k + 1, false);
			_cards.push_back(tmpCard);
		}
	}
}

int Deck::getSize() const {
	return _cards.size();
}

std::vector<Card> Deck::getCards() const {
	return _cards;
}