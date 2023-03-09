#include <iostream>
#pragma warning(disable : 4996)

enum class Genre {
	Comedy,
	Action,
	Horror,
	Romantic
};

struct Movie {
	char name[20];
	int duration = 0;
	Genre genre;
	double rating = 0;
};

Movie createMovie(char name[20], int duration, Genre genre, double rating)
{
	Movie movie;
	strcpy(movie.name, name);
	movie.duration = duration;
	movie.genre = genre;
	movie.rating = rating;
	return movie;
}

const int moviesCount = 3;

void addMovie(const Movie& movieToAdd, Movie movies[moviesCount], int indexLastMovie)
{//how to get the empty one, without using indexLastMovie???
	movies[indexLastMovie] = movieToAdd;
}

char* getGenre(const Movie& movie)
{
	char* genre = new char[20];
	//why not char* genre;
	switch (movie.genre)
	{
	case Genre::Horror:
		strcpy(genre, "Horror");
		break;
	case Genre::Action:
		strcpy(genre, "Action");
		break;
	case Genre::Comedy:
		strcpy(genre, "Comedy");
		break;
	case Genre::Romantic:
		strcpy(genre, "Romantic");
		break;
	default:
		break;
	}
	return genre;
}

void printAllMovies(const Movie movies[moviesCount])
{
	for (size_t i = 0; i < moviesCount; i++)
	{
		std::cout << "---------------------------------------" << std::endl;
		std::cout << " Movie: " << movies[i].name << std::endl;
		std::cout << " Duration: " << movies[i].duration << std::endl;
		std::cout << " Genre: " << getGenre(movies[i]) << std::endl;
		std::cout << " Rating: " << movies[i].rating << std::endl;
		std::cout << "---------------------------------------" << std::endl;
	}
}

Movie getMaxMovieRating(const Movie movies[moviesCount], int countMovies)
{
	Movie bestMovie;
	double currRating = 0;
	for (size_t i = 0; i < countMovies; i++)
	{
		if (currRating < movies[i].rating)
		{
			currRating = movies[i].rating;
			bestMovie = movies[i];
		}
	}
	return bestMovie;
}

int main()
{
	const int lengthName = 20;
	char nameA[lengthName];
	strcpy(nameA, "Titanik");
	Movie a = createMovie(nameA, 120, Genre::Romantic, 7.5);
	char nameB[lengthName];
	strcpy(nameB, "Two man and a half");
	Movie b = createMovie(nameB, 40, Genre::Comedy, 6.7);
	char nameC[lengthName];
	strcpy(nameC, "Godzila");
	Movie c = createMovie(nameC, 150, Genre::Horror, 7);

	Movie movies[moviesCount];
	addMovie(a, movies, 0);
	addMovie(b, movies, 1);
	addMovie(c, movies, 2);

	printAllMovies(movies);

	Movie bestMovie = getMaxMovieRating(movies, moviesCount);
	std::cout << "The most rated movie is " << bestMovie.name <<" with rating " << bestMovie.rating;
}