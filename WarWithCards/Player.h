#pragma once
#include "Deck.h"
#include <vector>
class Player
{
public:
	Player();
	Card* pullCard();

	short getPoints() const;
	std::vector<Card> getPlayerDeck() const;

	void setPoints(short pp);
	void start(const Deck& deck);
	void printCards();
private:
	short points;
	std::vector<Card> playerDeck;


};

