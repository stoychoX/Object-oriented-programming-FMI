#include<iostream>

struct transition {
    size_t to;
    char c;
};

struct state {
    transition trans[4];
    size_t size = 0;
};

struct stateInfo {
    state data[50];
};

bool validChar(char c) {
    return c >= 'a' && c <= 'z';
}

bool validIndex(size_t idx) {
    return idx < 50;
}

bool hasTransition(const stateInfo& arg, size_t from, char c) {
    // current state
    const state& cState = arg.data[from];

    for (size_t i = 0; i < cState.size; i++)
        if(cState.trans[i].c == c)
            return true;
    
    return false;
}

bool tryUpdate(state& cState, char c, size_t nVal) {
    if(!validChar(c) || !validIndex(nVal))
        return false;

    for (size_t i = 0; i < cState.size; i++) {
        if(cState.trans[i].c == c) {
            cState.trans[i].to = nVal;
            return true;
        }
    }
    return false;
}

bool addTransition(stateInfo& arg, size_t from, char c, size_t to) {
    if(!validChar(c) || !validIndex(from) || !validIndex(to))
        return false;

    state& cState = arg.data[from];

    if(cState.size == 4) 
        return false;

    if(tryUpdate(cState, c, to))
        return true;

    cState.trans[cState.size] = {to, c};
    cState.size++;
    return true;
}

int getTransition(const stateInfo& arg, size_t from, char c) {
    const state& cState = arg.data[from];

    for (size_t i = 0; i < cState.size; i++)
        if(cState.trans[i].c == c)
            return cState.trans[i].to;
    
    return -1;
}

bool canRead(const stateInfo& arg, const char* word, size_t from) {
    int startStateIndex = from;

    while(*word != '\0') {
        startStateIndex = getTransition(arg, startStateIndex, *word);

        if(startStateIndex == -1)
            return false;
        
        ++word;
    }
    return true;
}

bool removeTransition(stateInfo& arg, size_t from, char c) {
    state& cState = arg.data[from];

    for (size_t i = 0; i < cState.size; i++) {
        if(cState.trans[i].c == c) {
            std::swap(cState.trans[i], cState.trans[cState.size]);
            cState.size--;
            return true;
        }
    }
    return false;
}

int main() {
    stateInfo entity;

    addTransition(entity, 0, 'h', 1);
    addTransition(entity, 1, 'e', 2);
    addTransition(entity, 2, 'l', 3);
    addTransition(entity, 3, 'l', 4);
    addTransition(entity, 4, 'o', 5);

    std::cout << canRead(entity, "hello", 1);
    std::cout << canRead(entity, "hello", 0);
}