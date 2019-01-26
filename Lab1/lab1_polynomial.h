// Jonathan Chen 20722167 && Aman Mathur 20710307
// January 28th, 2019
// SYDE 223 Lab #1

#ifndef LAB1_LAB1_POLYNOMIAL_H
#define LAB1_LAB1_POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Polynomial {

private:
    vector <int> data;

public:
    friend class PolynomialTest;
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

class PolynomialTest {
public:
    PolynomialTest();
    bool test_constructor1();
    bool test_constructor2();
    bool test_equals();
    bool test_addition();
    bool test_subtraction();
    bool test_multiplication();
    bool test_derivative();
    bool test_print();
    void run();

    ~PolynomialTest();
};


#endif //LAB1_LAB1_POLYNOMIAL_H