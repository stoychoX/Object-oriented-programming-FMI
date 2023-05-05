#include"SetByCriteria.h"
#include<iostream>

int main() {
    SetByCriteria s(
        50, // Range: [0...50]
        SetByCriteria::makeCriteria(    // Specify criteria
            [](unsigned number) {return number % 3 == 0; }, // include criteria
            [](unsigned number) {return number % 2 == 0; }  // exclude criteria 
        )
    );
    // We have all the numbers which are divisible by 3
    // but are not even.
    s.print();

    
    [/*Capture*/] (/* Here we have the arguments of the function */) {
        // this is the function body
    };
}