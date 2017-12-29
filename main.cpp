#include <iostream>
#include "Gamestate.h"
#include "Player.h"
#include "Human.h"
#include "Deck.h"
#include "Card.h"
#include "TextInterface.h"

using namespace std;


int main() {
	int humans = 0;
	int robots = 0;

	introToGame();
	askHumanAmount();
	cin >> humans;
	askRobotAmount();
	cin >> robots;

	Gamestate classStruggle(humans, robots);
	classStruggle.init();
}