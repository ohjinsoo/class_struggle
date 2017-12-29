#ifndef TEXT_INTERFACE_HEADER
#define TEXT_INTERFACE_HEADER

#include <iostream>
#include <vector>
#include "Player.h"
#include "Card.h"

void introToGame();

void askHumanAmount();
void askRobotAmount();

void playerUsesCard(std::string playerType, int index, Card card);
void playerClearsHand(std::string playerType, int index);
void playerGainedRole(std::string playerType, int index, Roles role);
void passOutput(std::string playerType, int index);
void playerWonTurnSet(std::string playerType, int index, Card lastCard);
void displayNoPossibleCards();
void playerWonAlready(std::string playerType, int index);
int passOrGo();
void gameOver(std::vector<Player*> _players);

bool askToContinue();

#endif