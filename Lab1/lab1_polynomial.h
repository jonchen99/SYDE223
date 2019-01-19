//
// Created by Jonathan Chen on 2019-01-18.
//

#ifndef LAB1_LAB1_POLYNOMIAL_H
#define LAB1_LAB1_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;


class Polynomial {

private:
    vector <int> data;

public:
    Polynomial(int A[], int size);
    Polynomial();
    Polynomial(string fileName);
    void print();
    bool operator==(const Polynomial &target);
    Polynomial operator+(const Polynomial &target);
    Polynomial operator-(const Polynomial &target);
    Polynomial operator*(const Polynomial &target);
    Polynomial derivative();

    ~Polynomial();

};


#endif //LAB1_LAB1_POLYNOMIAL_H