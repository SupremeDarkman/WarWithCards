#ifndef MANAGER_H
#define MANAGER_H
#include "Player.h"

class Manager
{
	friend bool operator>(const Card& card1, const Card& card2);
	friend bool operator<(const Card& card1, const Card& card2);
	friend bool operator==(const Card& card1, const Card& card2);

public:
	Manager(Player& player1, Player& player2, Player& player3);

	unsigned short getRound() const;
	unsigned short getSession() const;
	std::vector<Player>& getPlayers();
	void printPlayer(unsigned i);

	void startMatch();
	void playRound();
	bool isGameOver();

	void printDeck(std::vector<Card>& deck) const;

private:
	std::vector<Player> players;
	unsigned short session;
	unsigned short round;

	Card getBiggestPlayerCard();
	int calcTiePlayers(Card);
	unsigned findPlayerWithCard(Card);
	void playNormalRound();
	void playWarRound();

	bool hasWar();
	unsigned getWinner();
	bool registerWinner(std::vector<Card>& deskDeck, unsigned winner);
};
#endif
