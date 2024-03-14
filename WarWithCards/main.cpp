#include "Manager.h"
#include <SDL.h>
#include "App.h"
#include <iostream>

App* app = nullptr;
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;

int main(int argc, char** argv)
{
	Deck deck;
	Player player1, player2, player3;
    std::vector<Player> players;
    
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);

	deck.shuffle();
	deck.riffleShuffle();

    Manager manager(player1, player2, player3);
    
    app = new App(players);
    bool init = app->init("WarWithCards",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    app->loadTextureOnDeck(deck);

	if (!init)
	{
		return -1;
	}

	app->ttf_init();
	while (app->isRunning())
	{
		app->handleEvents(deck);
		app->update();
		app->render();
	}
    app->DestroySDL();


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
