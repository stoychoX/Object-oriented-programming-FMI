#include <iostream>
#include "Game.h"
#pragma warning (disable:4996)

Game::Game() : Game::Game("no title", 0.0)
{}

Game::Game(const char* title, double price)
{
	this->setTitle(title);
	this->setPrice(price);
	this->isAvailable = true;
}

double Game::getPrice() const
{
	return this->price;
}

const char* Game::getTitle() const
{
	return this->title;
}

void Game::setPrice(double price)
{
	if (price >= 0.0)
	{
		this->price = price;
	}
}

void Game::setTitle(const char* title)
{
	if (strlen(title) > 0 && strlen(title) <= 64)
	{
		strcpy(this->title, title);
	}
}

bool Game::isGameAvailable() const
{
	return this->isAvailable;
}

bool Game::isFree() const
{
	return !(this->getPrice() > 0);
}

void Game::print() const
{
	std::cout << "Game: " << this->getTitle() << std::endl;
	std::cout << "Price: " << this->getPrice() << " lv."<<std::endl;
	std::cout << "Is available: " << (this->isGameAvailable() ? "Yes" : "No") << std::endl;
	std::cout << "------------------------------------" << std::endl;
}
