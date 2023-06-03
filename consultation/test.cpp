#include <cstring>
#include <stdexcept>
#include <iostream>

#pragma warning (disable : 4996)

class Question
{
public:
    virtual void ask() = 0;
    virtual int grade() const = 0;
    virtual Question* clone() const = 0;
    virtual ~Question() = default;
};

enum class YesNoAnswer
{
    NO,
    YES
};

class YesNoQuestion : public Question
{
public:
    YesNoQuestion(const char* question_text, YesNoAnswer correct_answer, int points) : 
        correct_answer(correct_answer), points(points) {
        strcpy(this->question_text, question_text);
    }
    void ask() override
    {
        std::cout << question_text << std::endl;
        char answer[4];
        std::cin >> answer;
        if (strcmp(answer, "yes") == 0)
        {
            user_answer = YesNoAnswer::YES;
        }
        else if (strcmp(answer, "no") == 0)
        {
            user_answer = YesNoAnswer::NO;
        }
        else
            throw std::invalid_argument("unknown answer");
    }

    int grade() const override
    {
        return correct_answer == user_answer ? points : 0;
    }

    Question* clone() const override {
        return new YesNoQuestion(*this);
    }

private:
    char question_text[1024];
    int points;
    YesNoAnswer correct_answer;
    YesNoAnswer user_answer;
};

class MultipleChoice : public Question
{
public:
    MultipleChoice(const char* question_text, const char* answers, const char* correct_answers, 
        int points_by_correct_answer) : points_by_correct_answer(points_by_correct_answer)
    {
        strcpy(this->question_text, question_text);
        strcpy(this->answers, answers);
        strcpy(this->correct_answers, correct_answers);
        strcpy(this->question_text, question_text);
   
    }
    void ask()
    {
        std::cout << question_text << std::endl;
        for (int i = 0; i < answers[i] != '\0'; i++)
        {
            std::cout << answers[i] << std::endl;
        }
        char answer;
        std::cin >> answer;
        int i = 0;
        while (answer != 'q')
        {
            user_answers[i++] = answer;
            std::cin >> answer;
        }
        user_answers[i] = '\0';
    }

    int grade() const {
        int points = 0;
        for (int i = 0; user_answers[i] != '\0'; i++)
        {
            bool found = false;
            for (int j = 0; correct_answers[j] != '\0'; j++)
            {
                if (user_answers[i] == correct_answers[j])
                {
                    points += points_by_correct_answer;
                    found = true;
                    break;
                }
            }
            if (!found) {
                points -= points_by_correct_answer;
            }
        }
        return points;
    }

    Question* clone() const override {
        return new MultipleChoice(*this);
    }

private:

    char question_text[1024];
    char answers[6];
    char correct_answers[6];
    char user_answers[6];
    int points_by_correct_answer;
};

class OpenQuestion : public Question
{
public:
    OpenQuestion(const char* question_text, int points) : points(points) {
        strcpy(this->question_text, question_text);
    }
    void ask() override {
        std::cout << question_text << std::endl;
        std::cin.ignore();
        std::cin.getline(user_answer, 1024);
    }

    int grade() const override {
        std::cout << question_text << std::endl << user_answer << std::endl;
        int percentage;
        std::cin >> percentage;
        return (percentage) / (100.0) * points;
    }

    Question* clone() const override {
        return new OpenQuestion(*this);
    }
private:
    char question_text[1024];
    char user_answer[1024];
    int points;
};

class Test
{
public:
    Test() {
        size = 0;
        capacity = 8;
        questions = new Question * [capacity];
    }

    Test(const Test& other) {
        copyFrom(other);
    }

    Test(Test&& other) {
        moveFrom(std::move(other));
    }

    Test& operator=(const Test& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }
        return *this;
    }

    Test& operator=(Test&& other) {
        if (this != &other) {
            free();
            moveFrom(std::move(other));
        }
        return *this;
    }

    ~Test() {
        free();
    }

    void add_question(Question* question)
    {
        if (size == capacity) {
            resize(capacity * 2);
        }
        questions[size++] = question->clone();
    }
    void do_test()
    {
        for (int i = 0; i < size; i++)
        {
            questions[i]->ask();
        }
    }
    int grade_test() const
    {
        int points{ 0 };
        for (int i = 0; i < size; i++)
        {
            points += questions[i]->grade();
        }
        return points;
    }
private:
    Question** questions;
    size_t size;
    size_t capacity;

    void copyFrom(const Test& other) {
        size = other.size;
        capacity = other.capacity;

        questions = new Question * [capacity];

        for (size_t i = 0; i < size; i++)
        {
            questions[i] = other.questions[i]->clone();
        }
    }

    void moveFrom(Test&& other) {
        size = other.size;
        capacity = other.capacity;
        other.size = other.capacity = 0;

        questions = other.questions;
        other.questions = nullptr;
    }

    void free() {
        for (size_t i = 0; i < size; i++)
        {
            delete questions[i];
        }

        delete[] questions;
    }

    void resize(size_t newCapacity) {
        capacity = newCapacity;
        Question** temp = new Question * [newCapacity];

        for (size_t i = 0; i < size; i++)
        {
            temp[i] = questions[i];
        }

        delete[] questions;
        questions = temp;
    }
};

int main()
{
    Question* yes_no_question = new YesNoQuestion("yes no question", YesNoAnswer::YES, 5);

    char answers[] = "abcde";
    char corect_answers[] = "abc";
    Question* multiple_choice = new MultipleChoice("multiple choice question", answers, corect_answers, 1);

    Question* open_question = new OpenQuestion("open question", 10);

    Test test{};
    test.add_question(yes_no_question);
    test.add_question(multiple_choice);
    test.add_question(open_question);

    test.do_test();
    std::cout << test.grade_test() << std::endl;
    return 0;
}
Write to Stoycho Kyosev
