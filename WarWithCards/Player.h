#pragma once
#include "Deck.h"
class Player
{
public:
	Player();

	std::vector<Card>& getPlayerDeck();
	size_t cntPlayerDeck();

	short getPoints() const;
	void setPoints(short pp);
	Card pullCard();
	void dealCards(Deck& deck);
	void printCards() const;
	void incrementPoint();
	void decrementPoint();
private:
	short points;
	std::vector<Card> playerDeck;
};

