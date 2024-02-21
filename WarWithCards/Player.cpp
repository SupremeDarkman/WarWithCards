#include "Player.h"
#include <iostream>
Player::Player()
{
	setPoints(0);
}

Card Player::pullCard()
{
	if (!playerDeck.empty())
	{
		Card card = playerDeck.front();
		playerDeck.erase(playerDeck.begin());
		return card;
	}
	std::cout << "No more cards!\n";
	return {};
}

short Player::getPoints() const
{
	return this->points;
}

std::vector<Card>& Player::getPlayerDeck()
{
	return playerDeck;
}

size_t Player::cntPlayerDeck()
{
	return playerDeck.size();
}

void Player::setPoints(short pp)
{
	this->points = pp;
}

void Player::dealCards(Deck& deck)
{
	playerDeck.clear();

	for (unsigned i = 0, count = 0; count < 10; i += 3)
	{
		playerDeck.push_back(deck.DealCard());
		count++;
	}
}

void Player::printCards() const
{
	for (unsigned i = 0; i < playerDeck.size(); i++)
	{
		std::cout << "Face: ";
		switch (playerDeck[i].face)
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
		switch (playerDeck[i].suit)
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

void Player::incrementPoint()
{
	this->points++;
}

void Player::decrementPoint()
{
	this->points--;
}

