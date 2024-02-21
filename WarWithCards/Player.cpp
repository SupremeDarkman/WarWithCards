#include "Player.h"
#include <iostream>
Player::Player()
{
    setPoints(0);
}

Card* Player::pullCard()
{
    return nullptr;
}

short Player::getPoints() const
{
    return this->points;
}

std::vector<Card> Player::getPlayerDeck() const
{
    return playerDeck;
}

void Player::setPoints(short pp)
{

}

void Player::start(const Deck& deck)
{
    playerDeck.clear();

    std::vector<Card> wholeDeck = deck.getDeck();

    for (unsigned i = 0, count = 0; count < 10; i++/*i+=3*/)
    {
        playerDeck.push_back(wholeDeck[i]);
        count++;
    }
}

void Player::printCards()
{
    for (unsigned i = 0; i < getPlayerDeck().size(); i++)
    {
        std::cout << "Face: " << playerDeck.at(i).face << " Suit: " << playerDeck.at(i).suit << " Color: " << playerDeck.at(i).color << std::endl;
    }
}
