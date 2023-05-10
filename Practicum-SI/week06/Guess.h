#pragma once
class Guess {
public:
	int guesses[4]{-1};
	Guess(int isEven, int isPrime, int isPowerOfTwo, int guessedNum);
};