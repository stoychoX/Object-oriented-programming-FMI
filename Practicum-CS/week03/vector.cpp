#ifndef VECTOR_HEADER
#define VECTOR_HEADER

/// @brief Клас, който представлява
/// динамичен масив
class vector {
public:
    /// @brief Създава празен контейнер с capacity 8.
    vector();

    vector(const vector &);
    vector(vector &&);

    vector &operator=(const vector &);

    /// @brief Създава контейнер.
    /// @param argCap големината на контейнера.
    vector(int argCap);

    /// @brief Създава контейнер.
    /// @param argCap Големината на контейнера.
    /// @param argDef Началната стойност на всички елементи.
    vector(int argCap, int argDef); // Създава контейнер с argCap големина като всеки елемент е равен на argDef.

    /// @brief Връща число на дадена позиция.
    /// @param  Позицията от която искаме да четем.
    int operator[](size_t) const; 

    /// @brief Връща число на подадена позиция и позволява промяната му.
    /// @param  Позицията от която да четем или в която да пишем
    int &operator[](size_t);

    /// @brief Добавя елемент в колекцията.
    /// @param  Елемента, който добавяме.
    void push_back(int);

    /// @brief Премахва последния елемент от колекцията
    /// @return Последния елемент от колекцията
    int pop_back();

    ~vector();
private:
    int *data;       // < Паметта, в която държим информацията
    size_t size;     // < Броя елементи в колекцията
    size_t capacity; // < Максималния брой елементи, които колекцията поддържа

    /// @brief Изтрива паметта
    void free();

    /// @brief Копира обект
    void copy(const vector &);

    /// @brief Удвоява размера на обекта. 
    void resize();
};

#endif