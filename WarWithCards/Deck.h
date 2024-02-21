#pragma once
#include "App.h"
#include <vector>
#include <SDL.h>
const unsigned short DECK_CAPACITY = 52;

enum Suit
{
	Clubs,
	Diamonds,
	Hearts,
	Spades,
	Test
};

enum Face
{
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

struct Card
{
	Suit suit;
	Face face;
	short value;

};

class Deck
{
public:
	Deck();
	void print() const;
	Card DealCard();
	void riffleShuffle();
	void shuffle();
private:
	std::vector<Card> deck;
};