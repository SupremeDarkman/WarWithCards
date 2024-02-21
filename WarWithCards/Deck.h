#pragma once
#include <vector>
const unsigned short DECK_CAPACITY = 52;
struct Card
{
	const char* suit;
	const char* color;
	const char* face;
};

class Deck
{
public:
	Deck();
	void print() const;
	std::vector<Card> getDeck() const;
	void riffleShuffle();
private:
	std::vector<Card> deck = {};
};

