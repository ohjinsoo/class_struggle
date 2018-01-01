#ifndef TEXT_INTERFACE_HEADER
#define TEXT_INTERFACE_HEADER

#include <iostream>
#include <vector>
#include "Player.h"
#include "Card.h"


// ----------GAMESTATE FUNCTIONS-------------------------
void introToGame();
void displayGameStart();

void askHumanAmount();
void askRobotAmount();

void playerUsesCard(std::string playerType, int index, Card card, int cardStack);
void playerClearsHand(std::string playerType, int index);
void playerGainedRole(std::string playerType, int index, Roles role);
void passOutput(std::string playerType, int index);
void playerWonTurnSet(std::string playerType, int index, Card lastCard);
void playerWonAlready(std::string playerType, int index);
void gameOver(std::vector<Player*> _players);

int getStackOptions(std::vector<Card> hand);
void displayStackOptions(int options);
void displayCardStack(int cardStack);

bool askToContinue();

// ----------HUMAN FUNCTIONS-------------------------

void displayLastCard(Card lastCard, int cardStack);
void displayRequireCards(int cards);
void displayAllCards(std::vector<Card> hand);
int askForChoice(int max);
void displayBadCard();








#endif