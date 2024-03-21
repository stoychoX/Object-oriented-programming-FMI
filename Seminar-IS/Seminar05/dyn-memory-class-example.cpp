#include <iostream>
#include <cstring>

class Entity
{
private:
    char* label;

    void free()
    {
        delete[] label;
    }
public:
    Entity() : label(nullptr) {}

    Entity(const char* c) 
    {
        size_t len = strlen(c);
        label = new char[len + 1];
        strncpy(label, c, len);
        label[len] = '\0';
    }

    const char* getLabel() const
    {
        return label;
    }

    ~Entity()
    {
        free();
    }
};

int main()
{
    Entity e("label value");
    std::cout << e.getLabel();
}