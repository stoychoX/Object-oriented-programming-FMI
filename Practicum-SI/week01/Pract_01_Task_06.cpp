#include <iostream>
const size_t BUFFER = 100;

enum class Genre
{
    Comedy,
    Action,
    Horror,
    Romantic,
    unknown
};

struct Movie
{
    char name[BUFFER] = "";
    int minutes = 0;
    double rating = 0.0;
    Genre genre = Genre::unknown;
};

Movie createMovie(const char *name, int minutes, double rating, Genre genre)
{
    Movie movie;
    strcpy_s(movie.name, name);
    movie.minutes = minutes;
    movie.rating = rating;
    movie.genre = genre;
    return movie;
}

void printGenre(Genre genre)
{
    switch (genre)
    {
    case Genre::Action:
        std::cout << "Genre :Action" << std::endl;
        break;
    case Genre::Comedy:
        std::cout << "Genre :Comedy" << std::endl;
        break;
    case Genre::Horror:
        std::cout << "Genre :Horror" << std::endl;
        break;
    case Genre::Romantic:
        std::cout << "Genre :Romantic" << std::endl;
        break;
    default:
        std::cout << "Unknown genre" << std::endl;
        break;
    }
}

void printMovie(const Movie &movie)
{
    std::cout << "Movie name:" << movie.name << std::endl
              << "Duration:" << movie.minutes << std::endl;
    printGenre(movie.genre);
    std::cout << "Rating: " << movie.rating << std::endl;
}

Movie getTopRatedMovie(const Movie *movies, size_t countMovies)
{
    double currentTopRating = movies[0].rating;
    Movie topMovie = movies[0];
    for (size_t i = 1; i < countMovies; i++)
    {
        if (movies[i].rating > currentTopRating)
        {
            currentTopRating = movies[i].rating;
            topMovie = movies[i];
        }
    }
    return topMovie;
}

int main()
{
    const size_t countMovies = 3;
    Movie movies[countMovies];

    movies[0] = createMovie("Star wars", 120, 10, Genre::Action);
    movies[1] = createMovie("End game", 120, 9.5, Genre::Action);
    movies[2] = createMovie("After", 90, 6.5, Genre::Romantic);

    for (size_t i = 0; i < countMovies; i++)
    {
        printMovie(movies[i]);
    }

    printMovie(getTopRatedMovie(movies, countMovies));

    return 0;
}