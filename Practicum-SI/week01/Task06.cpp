#include <iostream>
const int NAME_FILM_MAX_LEN = 30;
const int MAX_MIN = 300;
const int MIN_MIN = 60;
const int MAX_RATING = 5;
const int MIN_RATING = 1;
const int GENRE_MAX_LEN = 10;
enum class Genre {
	Comedy,
	Action,
	Horror,
	Romantic,
	Unknown
};
struct Movie {
	char name[NAME_FILM_MAX_LEN] = "unknown";
	int minutes = MIN_MIN;
	Genre genre = Genre::Unknown;
	int rating = MIN_RATING;//1 to 5 stars
};
void initMovie(Movie& movie, char name[NAME_FILM_MAX_LEN], 
	int mins, Genre genre, int rating) {
	if (std::strlen(name) < NAME_FILM_MAX_LEN &&
		mins < MAX_MIN && rating >= MIN_RATING &&
		rating <= MAX_RATING) {
		strcpy_s(movie.name, name);
		movie.minutes = mins;
		movie.genre = genre;
		movie.rating = rating;
	}
	else {
		std::cout << "Incorrect input" << std::endl;
	}
}
void readMovie(Movie& movie) {
	char name[NAME_FILM_MAX_LEN];
	int mins; 
	Genre genre = Genre::Unknown;
	int rating;
	char g[GENRE_MAX_LEN];
	std::cout << std::endl;
	std::cout << "Input name: ";
	std::cin.getline(name, NAME_FILM_MAX_LEN);
	std::cout << "\nInput mins: ";
	std::cin >> mins;
	std::cout << "\nInput genre: ";
	std::cin.ignore();
	std::cin.getline(g, GENRE_MAX_LEN);
	if (std::strcmp(g, "Comedy") == 0) {
		genre = Genre::Comedy;
	}
	else if (std::strcmp(g, "Action") == 0) {
		genre = Genre::Action;
	}
	else if (std::strcmp(g, "Romantic") == 0) {
		genre = Genre::Romantic;
	}
	else if (std::strcmp(g, "Horror") == 0) {
		genre = Genre::Horror;
	}
	std::cout << "\nInput rating: ";
	std::cin >> rating;
	initMovie(movie, name, mins, genre, rating);
	std::cin.ignore();
}
void printMovie(const Movie& movie) {
	std::cout << "........." << std::endl;
	std::cout << "Name: " << movie.name << std::endl;
	std::cout << "Minutes: " << movie.minutes << std::endl;
	std::cout << "Genre: ";
	switch (movie.genre) {
	case Genre::Action:
		std::cout << "Action\n";
		break;
	case Genre::Comedy:
		std::cout << "Comedy\n";
		break;
	case Genre::Horror:
		std::cout << "Horror\n";
		break;
	case Genre::Romantic:
		std::cout << "Romantic\n";
		break;
	case Genre::Unknown:
		std::cout << "Unknown\n";
		break;
	}
	std::cout << "Rating: " << movie.rating << std::endl;
	std::cout << std::endl;
}
void printMaxRatedMovie(const Movie * movies, int len) {
	int maxRate = movies[0].rating;
	for (int i = 1; i < len; i++) {
		if (movies[i].rating > maxRate) {
			maxRate = movies[i].rating;
		}
	}
	for (int i = 1; i < len; i++) {
		if (movies[i].rating == maxRate) {
			printMovie(movies[i]);
			return;
		}
	}
	
}
int main() {
	Movie m1, m2, m3;
	Movie movies[] = { m1, m2, m3 };
	for (int i = 0; i < 3; i++) {
		readMovie(movies[i]);
	}
	for (int i = 0; i < 3; i++) {
		printMovie(movies[i]);
	}
	std::cout << "Max-rated movie: ";
	printMaxRatedMovie(movies, 3);
}