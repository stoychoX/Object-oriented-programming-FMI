#pragma once

// unique pointer
// working only with integers

class unique_pointer {
private:
    int* mPointer = nullptr;

    void moveFrom(unique_pointer&&);
public:
    unique_pointer() = default;
    unique_pointer(int*);

    // unique things have no copy
    unique_pointer(const unique_pointer&) = delete; 
    unique_pointer& operator=(const unique_pointer&) = delete;

    void destroy();

    bool operator!() const;
    
    // cast to bool operator - this one is additional
    operator bool() const;

    int& operator*();
    int operator*() const;

    unique_pointer(unique_pointer&&); 
    unique_pointer& operator=(unique_pointer&&); 

    ~unique_pointer();
};