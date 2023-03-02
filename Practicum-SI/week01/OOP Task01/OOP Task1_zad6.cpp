#include <iostream>

const int MAX_MOVIES_IN_ARRAY = 3;

enum class Genre
{
    Com, 
    Ac,
    Hor, 
    Rom,
    Unknow
};

void PrintGenre(const Genre& genre)
{
    switch (genre)
    {
    case Genre::Com:
        std::cout << "Comedy";
        break;
    case Genre::Ac:
        std::cout << "Action";
        break;
    case Genre::Hor:
        std::cout << "Horror";
        break;
    case Genre::Rom:
        std::cout << "Romantic";
        break;
    default:
        std::cout << "Unknow";
        break;
    }
}

struct Movie
{
    char name[16] = "nonName";
    size_t time = 0;
    Genre genre = Genre::Unknow;
    double rating = 0;
};

int StringLenght(char* str, int index = 0)
{
    while (str[index] != '\0')
    {
        index++;
    }
    return index;
}

void CopyingString(char* strOne, char* strTwo, int index = 0)
{
    while (index < StringLenght(strTwo))
    {
        strOne[index] = strTwo[index];
        index++;
    }
    strOne[index] = '\0';
}

Movie CreateMovie(char* name, size_t time, Genre genre, double rating)
{
    Movie movie;
    CopyingString(movie.name, name);
    movie.time = time;
    movie.genre = genre;
    movie.rating = rating;
    return movie;
}

void PrintMovie(const Movie& movie)
{
    std::cout << movie.name << " (";
    PrintGenre(movie.genre);
    std::cout << ") ,Time: " << movie.time << " Rating: " << movie.rating << std::endl;
}

void PrintAllMoviesFromArray(Movie* movies)
{
    for (int i = 0; i < MAX_MOVIES_IN_ARRAY; i++)
    {
        PrintMovie(movies[i]);
    }
}

void ChekingForTopMovie(const Movie& checkMov, Movie& topMov)
{
    if (checkMov.rating > topMov.rating)
        topMov = checkMov;
}

void FindTopMovie(Movie* movies, Movie& topMov)
{
    for (int i = 1; i < MAX_MOVIES_IN_ARRAY; i++)
    {
        ChekingForTopMovie(movies[i], topMov);
    }
}

void PrintTopMovies(Movie* movies)
{
    Movie topMovie = movies[0];
    FindTopMovie(movies, topMovie);
    PrintMovie(topMovie);
}

int main()
{
    char name[16] = "Avengers";
    int time = 198;
    Genre genre = Genre::Ac;
    double rating = 4.9;
    Movie movie1 = CreateMovie(name, time, genre, rating);
    PrintMovie(movie1);
    Movie movie2 = { "Iron Man", 123, Genre::Ac, 4.7 };
    Movie movie3 = { "Ice Age", 94, Genre::Com, 4.8 };
    Movie movie4 = { "AntMan 3", 119, Genre::Ac, 2.1 };

    Movie movies[MAX_MOVIES_IN_ARRAY];
    movies[0] = movie2;
    movies[1] = movie3;
    movies[2] = movie4; 
    PrintTopMovies(movies);
}
