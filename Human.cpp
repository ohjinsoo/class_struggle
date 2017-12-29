#include <iostream>
#include <vector>
#include "Human.h"
#include "Player.h"
#include "Card.h"
#include "Roles.h"

Human::Human() : Player() {
}

Human::Human(Roles role) : Player(role) {
}

Human::Human(std::vector<Card> cards, Roles role) : Player(cards, role) {
}

std::string Human::name() {
	return "Human";
}

Card Human::pickCard(Card lastCard) {

}