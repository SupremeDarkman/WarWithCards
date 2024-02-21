#include "Deck.h"
#include <iostream>
Deck::Deck()
{
	const char* const arrSuit[4] = {"Spades", "Hearths", "Diamonds", "Clubs"};
	const char* const arrFace[13] = { "2", "3", "4", "5", "6" , "7" , "8" , "9" , "T" , "J" , "Q" , "K", "A" };
	const char* const arrColor[2] = { "Black", "Red" };
	deck.resize(DECK_CAPACITY);
	for (unsigned i = 0; i < DECK_CAPACITY; i++)
	{
		deck[i].suit = arrSuit[i % 4];
		deck[i].face = arrFace[i % 13];
		deck[i].color = arrColor[i / 26];
	}
}

void Deck::print() const
{
	for (unsigned i = 0; i < DECK_CAPACITY; i++)
	{
		std::cout << "Face: " << deck[i].face << " Suit: " << deck[i].suit << " Color: " << deck[i].color << std::endl;
	}
}

void Deck::riffleShuffle()
{
	const unsigned halfDeckSize = DECK_CAPACITY / 2;

	Card deckFirstHalf[halfDeckSize] = {}, deckSecondHalf[halfDeckSize] = {};


	for (unsigned i = 0; i < halfDeckSize; i++)
	{
		deckFirstHalf[i] = deck[i];
	}
	//for (unsigned i = 0, k = 0; i < halfDeckSize || k < DECK_CAPACITY; i++, k += 2)
	//{
	//	deckFirstHalf[i] = deck[k];
	//}
	//for (unsigned i = 0; i < halfDeckSize; i++)
	//{
	//	std::cout << deckFirstHalf[i];
	//}

	for (unsigned i = halfDeckSize, k = 0; i < DECK_CAPACITY || k < halfDeckSize; i++, k++)
	{
		deckSecondHalf[k] = deck[i];
	}
	//for (unsigned k = 0, j = 1; k < halfDeckSize || j < DECK_CAPACITY; k++, j+=2)
	//{
	//	deckSecondHalf[k] = deck[j];
	//}
	//for (unsigned j = 0; j < halfDeckSize; j++)
	//{
	//	std::cout << deckSecondHalf[j];
	//}

	for (unsigned i = 0, j = 0; j < halfDeckSize || i < DECK_CAPACITY; i += 2, j++)
	{
		deck[i] = deckSecondHalf[j];
	}
	//for (unsigned i = 0; i < DECK_CAPACITY; i++)
	//{
	//	std::cout << deck[i];
	//}

	for (unsigned i = 1, j = 0; j < halfDeckSize || i < DECK_CAPACITY; i += 2, j++)
	{
		deck[i] = deckFirstHalf[j];
	}

}

std::vector<Card> Deck::getDeck() const
{
	return deck;
}
