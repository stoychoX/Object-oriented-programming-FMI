#include<iostream>
#include<cmath>

struct point {
    int x;
    int y;
};

void readPoint(point& arg) {
    std::cin >> arg.x >> arg.y;
}

struct triangle {
    point p1;
    point p2;
    point p3;
};

void readTriangle(triangle& arg) {
    readPoint(arg.p1);
    readPoint(arg.p2);
    readPoint(arg.p3);
}

double distance(const point& p1, const point& p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

double area(const triangle& arg) {
    double firstLength = distance(arg.p1, arg.p2);
    double secondLength = distance(arg.p2, arg.p3);
    double thirdLength = distance(arg.p1, arg.p3);

    double half = (firstLength + secondLength + thirdLength) / 2;

    return sqrt( half * (half - firstLength) * (half - secondLength) * (half - thirdLength) );
}

double* getAreas(triangle* arr, size_t length) {
    double* toReturn = new double[length];

    for (size_t i = 0; i < length; i++) {
        toReturn[i] = area(arr[i]);
    }

    return toReturn;
}

void swapTrianggles(triangle& fst, triangle& snd) {
    triangle buff = fst;
    fst = snd;
    snd = buff;
}

void sort(triangle* data, double* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        size_t minElementIndex = i;

        for (size_t j = i + 1; j < size; j++) {
            if(arr[j] < arr[minElementIndex]) {
                minElementIndex = j;
            }
        }
        
        if(i != minElementIndex) {
            std::swap(arr[i], arr[minElementIndex]);
            swapTrianggles(data[i], data[minElementIndex]);
        }
    }
    
}

void printPoint(const point& arg) {
    std::cout << arg.x << " " << arg.y << std::endl;
}

void printTriangle(const triangle& arg) {
    printPoint(arg.p1);
    printPoint(arg.p2);
    printPoint(arg.p3);
}

int main() {
    size_t n = 0;
    std::cin >> n;

    triangle* arr = new triangle[n];

    for (size_t i = 0; i < n; i++)
        readTriangle(arr[i]);    

    double* areas = getAreas(arr, n);

    sort(arr, areas, n);

    for (size_t i = 0; i < n; i++) {
        std::cout << areas[i] << ": " << std::endl;

        printTriangle(arr[i]);

        std::cout << std::endl << std::endl;
    }
    
    delete[] areas, arr;
}