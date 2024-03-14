#include "Manager.h"
#include <iostream>
#include <random>

Manager::Manager(Player& player1, Player& player2, Player& player3)
	:round(0), session(0)
{
	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
}

bool operator>(const Card& card1, const Card& card2)
{
	return card1.value > card2.value;
}

bool operator<(const Card& card1, const Card& card2)
{
	return card1.value < card2.value;
}

bool operator==(const Card& card1, const Card& card2)
{
	return (card1.value == card2.value);
}

unsigned short Manager::getRound() const
{
	return this->round;
}

unsigned short Manager::getSession() const
{
	return this->session;
}

std::vector<Player>& Manager::getPlayers()
{
	return this->players;
}

void Manager::printPlayer(unsigned i)
{
	std::cout << "Player " << (i + 1) << ", Cards number: " << players[i].cntPlayerDeck() << std::endl;
	std::cout << "Cards:" << std::endl;
	players[i].printCards();
}

void Manager::printDeck(std::vector<Card>& deck) const
{
	for (unsigned i = 0; i < deck.size(); i++)
	{
		std::cout << "Face: ";
		switch (deck[i].face)
		{
		case Face::Two: std::cout << "2"; break;
		case Face::Three: std::cout << "3"; break;
		case Face::Four: std::cout << "4"; break;
		case Face::Five: std::cout << "5"; break;
		case Face::Six: std::cout << "6"; break;
		case Face::Seven: std::cout << "7"; break;
		case Face::Eight: std::cout << "8"; break;
		case Face::Nine: std::cout << "9"; break;
		case Face::Ten: std::cout << "T"; break;
		case Face::Jack: std::cout << "J"; break;
		case Face::Queen: std::cout << "Q"; break;
		case Face::King: std::cout << "K"; break;
		case Face::Ace: std::cout << "A"; break;
		default:
			break;
		}
		std::cout << " Suit: ";
		switch (deck[i].suit)
		{
		case Suit::Clubs: std::cout << "Clubs"; break;
		case Suit::Diamonds: std::cout << "Diamonds"; break;
		case Suit::Hearts: std::cout << "Hearths"; break;
		case Suit::Spades: std::cout << "Spades"; break;
		default:
			break;
		}
		std::cout << std::endl;
	}
}

void Manager::startMatch()
{
	std::cout << "Starting new match !" << std::endl;
	std::cout << "Good luck!" << std::endl;
	for (int i = 0; i < players.size(); i++)
	{
		printPlayer(i);
	}
}

void Manager::playRound()
{
	if (isGameOver())
	{
		return;
	}
	round++;

	if (hasWar())
	{
		playWarRound();
	}
	else
	{
		playNormalRound();
	}
}

bool Manager::isGameOver()
{
	Player& player1 = players[0];
	Player& player2 = players[1];
	Player& player3 = players[2];
	if (player1.cntPlayerDeck() == 0 && player2.cntPlayerDeck() == 0 && player3.cntPlayerDeck() == 0)
	{
		std::cout << "Tie!";
		return true;

	}
	else if (player1.cntPlayerDeck() == 0 && player2.cntPlayerDeck() == 0)
	{
		std::cout << "Player 3 wins!";
		return true;
	}
	else if (player1.cntPlayerDeck() == 0 && player3.cntPlayerDeck() == 0)
	{
		std::cout << "Player 2 wins!";
		return true;
	}
	else if (player2.cntPlayerDeck() == 0 && player3.cntPlayerDeck() == 0)
	{
		std::cout << "Player 1 wins!";
		return true;
	}
	return false;
}

Card Manager::getBiggestPlayerCard()
{
	Player& player1 = players[0];
	Player& player2 = players[1];
	Player& player3 = players[2];

	Card biggest = {};
	biggest.value = 2;
	if (!player1.getPlayerDeck().empty())
	{
		biggest = player1.getPlayerDeck().front();
	}
	if (!player2.getPlayerDeck().empty() && player2.getPlayerDeck().front() > biggest)
	{
		biggest = player2.getPlayerDeck().front();
	}
	if (!player3.getPlayerDeck().empty() && player3.getPlayerDeck().front() > biggest)
	{
		biggest = player3.getPlayerDeck().front();
	}

	return biggest;
}

int Manager::calcTiePlayers(Card c)
{
	int count = 0;
	for (unsigned i = 0; i < players.size(); i++)
	{
		if (!players[i].getPlayerDeck().empty() && players[i].getPlayerDeck().front() == c)
		{
			count++;
		}
	}
	return count;
}
unsigned Manager::findPlayerWithCard(Card c)
{
	for (unsigned i = 0; i < players.size(); i++)
	{
		if (!players[i].getPlayerDeck().empty() && players[i].getPlayerDeck().front() == c)
		{
			return i;
		}
	}
	return (unsigned)players.size();
}

void Manager::playNormalRound()
{
	unsigned winner = getWinner();

	std::vector<Card> deskDeck;
	for (unsigned i = 0; i < players.size(); i++)
	{
		if (players[i].cntPlayerDeck() > 0)
		{
			Card c = players[i].pullCard();
			deskDeck.push_back(c);
		}
	}
	std::cout << "Desk deck: " << std::endl;
	printDeck(deskDeck);

	// play the game

	registerWinner(deskDeck, winner);

	for (int i = 0; i < players.size(); i++)
	{
		printPlayer(i);
	}
}

void Manager::playWarRound()
{
	std::cout << "WAR: " << std::endl;
	std::vector<bool> isActive;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].cntPlayerDeck() > 0)
		{
			isActive.push_back(true);
		}
		else
		{
			isActive.push_back(false);
		}
	}

	std::vector<Card> deskDeck;

	while (true)
	{
		// calculate winner
		Card strongest = {};
		strongest.value = 2;
		for (int i = 0; i < players.size(); i++)
		{
			if (isActive[i] && players[i].getPlayerDeck().front() > strongest)
			{
				strongest = players[i].getPlayerDeck().front();
			}
		}

		// take cards from player
		int playersWithStrongest = 0;
		for (int i = 0; i < players.size(); i++)
		{
			if (isActive[i])
			{
				Card c = players[i].pullCard();
				deskDeck.push_back(c);
				if (c == strongest)
				{
					playersWithStrongest++;
				}
				else
				{
					isActive[i] = false;
				}
			}
		}

		if (playersWithStrongest == 1)
		{
			for (int i = 0; i < players.size(); i++)
			{
				if (isActive[i] && players[i].getPlayerDeck().front() == strongest)
				{
					// Winner
					registerWinner(deskDeck, i);
					for (int i = 0; i < players.size(); i++)
					{
						printPlayer(i);
					}
					return;
				}
			}
		}

		// is game over
		bool hasActivePlayers = false;
		for (unsigned i = 0; i < players.size(); i++)
		{
			if (isActive[i] && players[i].cntPlayerDeck() > 0)
			{
				hasActivePlayers = true;
			}
			else
			{
				isActive[i] = false;
			}
		}

		if (!hasActivePlayers)
		{
			// not specified what to do when cards over during war
			unsigned p = 0;
			while (!deskDeck.empty())
			{
				Card c = deskDeck.back();
				deskDeck.pop_back();
				players[p].getPlayerDeck().push_back(c);
				p++;
				if (p == players.size())
				{
					p = 0;
				}
			}
		}
	}
}

bool Manager::hasWar()
{
	Card c = getBiggestPlayerCard();
	if (calcTiePlayers(c) > 1)
	{
		return true;
	}
	return false;
}

unsigned Manager::getWinner()
{
	if (hasWar())
	{
		return (unsigned)players.size(); // invalid player
	}
	Card c = getBiggestPlayerCard();
	return findPlayerWithCard(c);
}

bool Manager::registerWinner(std::vector<Card>& deskDeck, unsigned winner)
{
	std::cout << "Winner is: " << winner + 1 << std::endl;
	for (unsigned i = 0; i < deskDeck.size(); i++)
	{
		players[winner].getPlayerDeck().push_back(deskDeck[i]);
	}
	return true;
}
