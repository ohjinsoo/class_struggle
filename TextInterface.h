#ifndef TEXT_INTERFACE_HEADER
#define TEXT_INTERFACE_HEADER

#include <iostream>
#include <vector>
#include "Player.h"
#include "Card.h"


// ----------GAMESTATE FUNCTIONS-------------------------
void introToGame();

void askHumanAmount();
void askRobotAmount();

void playerUsesCard(std::string playerType, int index, Card card);
void playerClearsHand(std::string playerType, int index);
void playerGainedRole(std::string playerType, int index, Roles role);
void passOutput(std::string playerType, int index);
void playerWonTurnSet(std::string playerType, int index, Card lastCard);
void playerWonAlready(std::string playerType, int index);
void gameOver(std::vector<Player*> _players);

bool askToContinue();

// ----------HUMAN FUNCTIONS-------------------------

void displayAllCards(std::vector<Card> hand);
int askForCardChoice(int max);
void displayBadCard();








#endif