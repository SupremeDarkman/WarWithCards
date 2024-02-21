#include "Manager.h"
#include <SDL.h>

App* app = nullptr;
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
	app = new App;
	if (!app->init("WarWithCards",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE))
	{
		return -1;
	}
	Deck deck;
	deck.shuffle();
	Player player1, player2, player3;

	player1.dealCards(deck);
	player2.dealCards(deck);
	player3.dealCards(deck);
	
	app->ttf_init();
	while (app->isRunning())
	{
		app->handleEvents();
		app->update();
		app->render();
	}

	/*
	Deck deck;
	deck.shuffle();
	Player player1, player2, player3;

	player1.dealCards(deck);
	player2.dealCards(deck);
	player3.dealCards(deck);

	Manager manager(player1, player2, player3);

	manager.startMatch();

	while (false == manager.isGameOver())
	{
		// console mode
		std::cout << "Press Enter to play rund" << std::endl;
		std::cin.get();

		manager.playRound();
	}

	std::cout << std::endl;
	std::cout << "Game Exit" << std::endl;*/

	return 0;
}