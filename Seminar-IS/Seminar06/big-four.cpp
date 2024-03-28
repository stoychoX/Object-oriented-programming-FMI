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

    void copyFrom(const Entity& other)
    {
        label = new char[strlen(other.label) + 1] {};
        strcpy(label, other.label);
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

    Entity(const Entity& other)
    {
        copyFrom(other);
    }

    Entity& operator=(const Entity& other)
    {
        if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
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
    Entity e1(e);

    e = e1;
}