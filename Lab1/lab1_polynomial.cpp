// Jonathan Chen 20722167 && Aman Mathur 20710307
// January 28th, 2019
// SYDE 223 Lab #1

#include "lab1_polynomial.h"

int main() {
    srand(time(NULL));
    PolynomialTest my_test;
    my_test.run();

    return 0;
}

//Default Constructor, with random exponents and random coefficients
Polynomial::Polynomial() {
    int random_size = 0;
    int random_coefficient = 0;
    random_size = rand() % 1001;
    data.resize(random_size);
    for (int i = 0; i < data.size(); i++) {
        random_coefficient = rand() % 2001 - 1000;
        data[i] = random_coefficient;
    }
}

//Constructor taking in an array and the size of the array
Polynomial::Polynomial(int A[], int size) {
    data.resize(size);
    for (int i = 0; i < data.size(); i++) {
        data[i] = A[i];
    }
}

//Constructor reading in a polynomial from a file
Polynomial::Polynomial(string fileName) {
    int data_size_from_file = 0;
    int i = 0;
    bool size_is_valid = true;

    ifstream my_file;
    my_file.open(fileName);

    //Error check for the file
    if (my_file.fail()) {
        cout << "Error opening input file";
        exit(1);
    }

    //read in the first value, which is always the size of the polynomial
    my_file >> data_size_from_file;

    //takes the absolute value of the size, allowing for some user error
    data_size_from_file = abs(data_size_from_file);
    data.resize(data_size_from_file);

    //reading in the values from the file only for the size specified in the first line of the file
    while (!my_file.eof() && size_is_valid) {
        if (i != data_size_from_file) {
            my_file >> data[i];
            i++;
        }  else {
            size_is_valid = false;
        }
    }
    my_file.close();
}

//print function
void Polynomial::print() {
    //formats the print statement from highest degree to lowest degree with a plus between the values
    //does not print coefficients with 0s
    for (int i = data.size()-1; i >= 0; i--) {

        if (data[i]!= 0) {
            cout << data[i] << "x^" << i;
        }

        if (i != 0 && data[i]!= 0 && data[i-1] != 0) {
            cout << " + ";
        }
    }
    cout << endl;
}

//calculate derivative function
Polynomial Polynomial::derivative(){
    Polynomial derivative;
    for (int i = 1; i < data.size(); i++){
        data[i - 1] = data[i] * i;
    }

    //setting the coefficient of the highest exponent to 0 and resizing the vector
    data[data.size()-1] = 0;
    data.resize(data.size()-1);
    return derivative;
}

//overloaded equal operator
bool Polynomial::operator==(const Polynomial &target)  {
    return (data == target.data);
}

//overloaded addition operator
Polynomial Polynomial:: operator+(const Polynomial &target) {
    //determining the bigger range and the bigger vector
    int long smaller_range = target.data.size();
    int long bigger_range = data.size();
    vector <int> bigger_vector = data;

    if (target.data.size() > data.size()){
        bigger_range = target.data.size();
        smaller_range = data.size();
        bigger_vector = target.data;
    }

    //setting the size of the sum polynomial to the bigger range
    Polynomial sum;
    sum.data.resize(bigger_range);

    for (int i = 0; i < smaller_range; i++) {
        sum.data[i] = data[i] + target.data[i];
    }

    //the remaining values after the sum to the smaller range is whatever is left in the bigger vector
    for (int i = smaller_range; i < bigger_range; i++) {
        sum.data[i] = bigger_vector[i];
    }
    return sum;
}

//overloaded subtraction operator
Polynomial Polynomial:: operator-(const Polynomial &target) {
    //determining the bigger range and the bigger vector
    int long smaller_range = target.data.size();
    int long bigger_range = data.size();
    vector <int> bigger_vector = data;

    if (target.data.size() > data.size()){
        bigger_range = target.data.size();
        smaller_range = data.size();
        bigger_vector = target.data;
    }

    //setting the size of the difference polynomial to the bigger range
    Polynomial difference;
    difference.data.resize(bigger_range);

    for (int i = 0; i < smaller_range; i++) {
        difference.data[i] = data[i] - target.data[i];
    }

    //the remaining values after the sum to the smaller range is the +/- of whatever is left in the bigger vector
    //depending on the order of the subtraction (a-b vs b-a)
    for (int i = smaller_range; i < bigger_range; i++) {
        if (bigger_vector == target.data)
            difference.data[i] = bigger_vector[i] * -1;
        else
            difference.data[i] = bigger_vector[i];
    }
    return difference;
}

//overloaded multiplication operator
Polynomial Polynomial:: operator*(const Polynomial &target) {
    Polynomial product;

    //resizing the product vector to the maximum value possible
    product.data.resize((target.data.size()-1) + (data.size()-1) + 1);

    //initializing the product vector to zero
    for (int i = 0; i < product.data.size(); i++){
        product.data[i] = 0;
    }

    //calculating the product
    for (int j = 0; j < data.size(); j++){
        for (int i = 0; i < target.data.size(); i++) {
            product.data[i + j] += data[j] * target.data[i];
        }
    }

    return product;
}

//testing the constructor that passes in an array and a size
bool PolynomialTest::test_constructor1() {
    int size = 5;
    int comparison_array[5] = {1,2,3,4,5};
    int bigger_size = 0;
    Polynomial test_polynomial(comparison_array, size);
    bool isEqual = true;
    int size_of_array = (sizeof(comparison_array)/ sizeof(comparison_array[0]));

    //determining the bigger size between the array and the polynomial
    if (size_of_array >= test_polynomial.data.size()) {
        bigger_size = size_of_array;
    } else {
        bigger_size = test_polynomial.data.size();
    }

    //compares every value between the array and the vector
    for (int i = 0; i < bigger_size && isEqual; i++) {
        if (comparison_array[i] != test_polynomial.data[i]) {
            isEqual = false;
        }
    }

    return isEqual;
}

//test the constructor that reads in from a file
bool PolynomialTest::test_constructor2() {
    int comparison_array[7] = {11,22,33,-3,54,55,-100};
    Polynomial test_polynomial("/Users/jonathanchen/Documents/2A/223/Lab1/coefficients.txt");
    bool isEqual = true;
    int bigger_size = 0;
    int size_of_array = (sizeof(comparison_array)/ sizeof(comparison_array[0]));

    //determining the bigger size between the file array and the polynomial
    if (size_of_array >= test_polynomial.data.size()) {
        bigger_size = size_of_array;
    } else {
        bigger_size = test_polynomial.data.size();
    }

    //compares every value between the hardcoded array and the data from the file
    for (int i = 0; i < bigger_size && isEqual; i++) {
        if (comparison_array[i] != test_polynomial.data[i]) {
            isEqual = false;
        }
    }

    return isEqual;
}

bool PolynomialTest::test_default_constructor() {
    Polynomial default1;
    bool inBounds = true;

    //checks if the exponent is between 0 and 1000
    if (default1.data.size() < 0 || default1.data.size() > 1000) {
        inBounds = false;
    }

    //checks if the coefficients are between -1000 and 1000
    for (int i = 0; i < default1.data.size() && inBounds; i++) {
        if (default1.data[i] < -1000 || default1.data[i] > 1000) {
            inBounds = false;
        }
    }

    return inBounds;
}

bool PolynomialTest::test_equals() {
    int array[5] = {100,-55,102,45,-2};
    int array2[5] = {1,-55,102,45,-2};
    int size = 5;
    Polynomial equal_polynomial1(array,size);
    Polynomial equal_polynomial2(array,size);
    Polynomial not_equal_polynomial(array2, size);

    //should fail because array and array2 are not equal but program will pass if array2 is removed
    if ((equal_polynomial1 == equal_polynomial2) && (equal_polynomial1 == not_equal_polynomial)) {
        return true;
    } else {
        return false;
    }
}

bool PolynomialTest::test_addition() {
    //creating arrays to populate the polynomials
    int array1[6] = {1,2,3,4,5,6};
    int array2[6] = {6,5,4,3,2,1};
    int array3[6] = {-3,6,-1,-100};
    int array4[6] = {3};
    int array5[6] = {};
    int size = 6;
    //creating arrays with the expected answers
    int result1[6] = {7,7,7,7,7,7};
    int result2[6] = {-2,8,2,-96,5,6};
    int result3[6] = {4,2,3,4,5,6};
    int result4[6] = {1,2,3,4,5,6};
    //creating Polynomial objects that contain the arrays to be summed
    Polynomial polynomial1(array1, size);
    Polynomial polynomial2(array2, size);
    Polynomial polynomial3(array3, size);
    Polynomial polynomial4(array4, size);
    Polynomial polynomial5(array5, size);
    //Polynomial objects to contain the values of the summations
    Polynomial sum1;
    Polynomial sum2;
    Polynomial sum3;
    Polynomial sum4;
    //Polynomial objects that contain the hard coded, expected results
    Polynomial output1(result1, size);
    Polynomial output2(result2, size);
    Polynomial output3(result3, size);
    Polynomial output4(result4, size);

    sum1 = polynomial1 + polynomial2;
    sum2 = polynomial1 + polynomial3;
    sum3 = polynomial1 + polynomial4;
    sum4 = polynomial1 + polynomial5;

    if ((sum1 == output1) && (sum2 == output2) && (sum3 == output3) && (sum4 == output4)) {
        return true;
    } else {
        return false;
    }
}

bool PolynomialTest::test_subtraction() {
    //creating arrays to populate the polynomials
    int array1[6] = {1,2,3,4,5,6};
    int array2[6] = {6,5,4,3,2,1};
    int array3[6] = {-3,6,-1,-100};
    int array4[6] = {3};
    int array5[6] = {};
    int size = 6;
    //creating arrays with the expected answers
    int result1[6] = {-5,-3,-1,1,3,5};
    int result2[6] = {4,-4,4,104,5,6};
    int result3[6] = {2,-2,-3,-4,-5,-6};
    int result4[6] = {1,2,3,4,5,6};
    //creating Polynomial objects that contain the arrays to be subtracted
    Polynomial polynomial1(array1, size);
    Polynomial polynomial2(array2, size);
    Polynomial polynomial3(array3, size);
    Polynomial polynomial4(array4, size);
    Polynomial polynomial5(array5, size);
    //Polynomial objects to contain the values of the differences
    Polynomial diff1;
    Polynomial diff2;
    Polynomial diff3;
    Polynomial diff4;
    //Polynomial objects that contain the hard coded, expected results
    Polynomial output1(result1, size);
    Polynomial output2(result2, size);
    Polynomial output3(result3, size);
    Polynomial output4(result4, size);

    diff1 = polynomial1 - polynomial2;
    diff2 = polynomial1 - polynomial3;
    diff3 = polynomial4 - polynomial1;
    diff4 = polynomial1 - polynomial5;

    if ((diff1 == output1) && (diff2 == output2) && (diff3 == output3) && (diff4 == output4)) {
        return true;
    } else {
        return false;
    }
}

bool PolynomialTest::test_multiplication() {
    //creating arrays to populate the polynomials
    int array1[6] = {1,2,3,4,5,6};
    int array2[6] = {6,5,4,3,2,1};
    int array3[4] = {-3,6,-1,-100};
    int array4[1] = {3};
    int array5[6] = {0,0,0,0,0,0};
    int size = 6;
    //creating arrays with the expected answers
    int result1[11] = {6,17,32,50,70,91,70,50,32,17,6};
    int result2[9] = {-3,0,2,-96,-194,-292,-369,-506,-600};
    int result3[9] = {3,6,9,12,15,18};
    int result4[11] = {0,0,0,0,0,0,0,0,0,0,0};
    //creating Polynomial objects that contain the arrays to be multiplied
    Polynomial polynomial1(array1, size);
    Polynomial polynomial2(array2, size);
    Polynomial polynomial3(array3, 4);
    Polynomial polynomial4(array4, 1);
    Polynomial polynomial5(array5, 6);
    //Polynomial objects to contain the values of the products
    Polynomial product1;
    Polynomial product2;
    Polynomial product3;
    Polynomial product4;
    //Polynomial objects that contain the hard coded, expected results
    Polynomial output1(result1, 11);
    Polynomial output2(result2, 9);
    Polynomial output3(result3, size);
    Polynomial output4(result4, 11);

    product1 = polynomial1 * polynomial2;
    product2 = polynomial1 * polynomial3;
    product3 = polynomial1 * polynomial4;
    product4 = polynomial1 * polynomial5;

    if ((product1 == output1) && (product2 == output2 )  && (product3 == output3) && (product4 == output4)) {
        return true;
    } else {
        return false;
    }
}

bool PolynomialTest::test_derivative() {
    //creating arrays to populate the polynomials
    int array1[6] = {1,2,3,4,5,6};
    int array2[4] = {-3,6,-1,-100};
    int array3[1] = {3};
    int array4[6] = {0,0,0,0,0,5};
    int size = 6;
    //creating arrays with the expected answers
    int result1[5] = {2,6,12,20,30};
    int result2[3] = {6,-2,-300};
    int result3[1] = {0};
    int result4[5] = {0,0,0,0,25};
    //creating Polynomial objects that contain the arrays to be differentiated
    Polynomial polynomial1(array1, size);
    Polynomial polynomial2(array2, 4);
    Polynomial polynomial3(array3, 1);
    Polynomial polynomial4(array4, size);
    //Polynomial objects that contain the hard coded, expected results
    Polynomial output1(result1, 5);
    Polynomial output2(result2, 3);
    Polynomial output3(result3, 0);
    Polynomial output4(result4, 5);

    //computing the derivative
    polynomial1.derivative();
    polynomial2.derivative();
    polynomial3.derivative();
    polynomial4.derivative();

    if ((polynomial1 == output1) && (polynomial2 == output2 ) && (polynomial3 == output3) && (polynomial4 == output4)) {
        return true;
    } else {
        return false;
    }
}

bool PolynomialTest::test_print() {
    string isSame = "";
    int array1[6] = {1,2,3,4,5,6};
    int array2[4] = {-3,6,-1,-100};
    int array3[1] = {3};
    int array4[6] = {0,0,0,0,0,5};
    int size = 6;
    Polynomial polynomial1(array1, size);
    Polynomial polynomial2(array2, 4);
    Polynomial polynomial3(array3, 1);
    Polynomial polynomial4(array4, size);

    //User input to determine if the arrays are the same
    cout << endl << "Testing the print function:" << endl << endl;
    polynomial1.print();
    polynomial2.print();
    polynomial3.print();
    polynomial4.print();
    cout << endl << "Are the printed statements the same as the expected polynomial? (Y/N) ";

    cin >> isSame;

    if (isSame == "n" || isSame == "N") {
        return false;
    } else {
        return true;
    }
}

void PolynomialTest:: run() {
    if (test_constructor1()) {
        cout << "Test Constructor 1 Passed! " << endl;
    } else {
        cout << "Test Constructor 1 Failed! " << endl;
    }

    if (test_constructor2()) {
        cout << "Test Constructor 2 Passed! " << endl;
    } else {
        cout << "Test Constructor 2 Failed! " << endl;
    }

    if (test_default_constructor()) {
        cout << "Test Default Constructor Passed! " << endl;
    } else {
        cout << "Test Default Constructor Failed! " << endl;
    }

    if (test_equals()) {
        cout << "Test Equals Passed! " << endl;
    } else {
        cout << "Test Equals Failed! " << endl;
    }

    if (test_addition()) {
        cout << "Test Addition Passed! " << endl;
    } else {
        cout << "Test Addition Failed! " << endl;
    }

    if (test_subtraction()) {
        cout << "Test Subtraction Passed! " << endl;
    } else {
        cout << "Test Subtraction Failed! " << endl;
    }

    if (test_multiplication()) {
        cout << "Test Multiplication Passed! " << endl;
    } else {
        cout << "Test Multiplication Failed! " << endl;
    }

    if (test_derivative()) {
        cout << "Test Derivative Passed! " << endl;
    } else {
        cout << "Test Derivative Failed! " << endl;
    }

    if (test_print()) {
        cout << "Test Print Function Passed! " << endl;
    } else {
        cout << "Test Print Function Failed! " << endl;
    }
}

//PolynomialTest default constructor
PolynomialTest::PolynomialTest() {}

Polynomial::~Polynomial(){}

PolynomialTest:: ~PolynomialTest(){}