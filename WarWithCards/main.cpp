#include "Deck.h"
#include "Player.h"
#include <iostream>
int main()
{
	std::cout << "Creating deck:\n";
	Deck deck;
	std::cout << "Printing deck:\n";
	deck.print();
	std::cout << "\nCreating player1:\n";
	Player player1;
	player1.start(deck);

	if (player1.getPlayerDeck().size() != 0);
		player1.printCards();

	return 0;
}