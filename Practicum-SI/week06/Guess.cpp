#include "Guess.h"

namespace
{
	int getCurrGuess(int guess)
	{
		if (guess > 0)
		{
			return 1;
		}
		else if (guess < 0)
		{
			return -1;
		}
		return 0;
	}
}
Guess::Guess(int isEven, int isPrime, int isPowerOfTwo, int guessedNum)
{
	guesses[0] = getCurrGuess(isEven);
	guesses[1] = getCurrGuess(isPrime);
	guesses[2] = getCurrGuess(isPowerOfTwo);
	guesses[3] = guessedNum;
}