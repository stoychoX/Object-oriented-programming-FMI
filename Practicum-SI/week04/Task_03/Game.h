#pragma once

class Game {
private:
	char title[64];
	double price;
	bool isAvailable;

public:

	Game();
	Game(const char* title, double price);
	const char* getTitle() const;
	double getPrice() const;
	bool isGameAvailable() const;
	void setTitle(const char* title);
	void setPrice(double price);
	bool isFree() const;
	void print() const;
};