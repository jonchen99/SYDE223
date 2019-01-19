
#include "lab1_polynomial.h"

int main() {
    srand(time(NULL));
    
    int sample[4] = {1,2,3,3};
    int sample2[6] = {6,5,4,3,2};
    Polynomial test(sample,4);
    Polynomial test2(sample2, 5);
    Polynomial inputFile("/Users/jonathanchen/Documents/2A/223/Lab1/coefficients.txt");
    Polynomial subtract;
    subtract = test - test2;
    subtract.print();

    return 0;
}

Polynomial::Polynomial(int A[], int size) {
    data.resize(size);
    for (int i = 0; i < data.size(); i++) {
        data[i] = A[i];
    }

}

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

Polynomial::Polynomial(string fileName) {
    int data_size_from_file = 0;
    int i = 0;

    ifstream my_file;
    my_file.open(fileName);

    if (my_file.fail()) {
        cout << "Error opening input file";
        exit(1);
    }

    my_file >> data_size_from_file;
    data.resize(data_size_from_file);
    while (!my_file.eof()) {
        my_file >> data[i];
        i++;
    }
    my_file.close();
}

bool Polynomial::operator==(const Polynomial &target)  {
    return (data == target.data);
}


void Polynomial::print() {
    for (int i = 0; i < data.size(); i++) {
        cout << data[i] << "x^" << i << endl;
    }
}

Polynomial Polynomial:: operator+(const Polynomial &target) {
    int long smaller_range = target.data.size();
    int long bigger_range = data.size();
    vector <int> biggerVector = data;

    if (target.data.size() > data.size()){
        bigger_range = target.data.size();
        smaller_range = data.size();
        biggerVector = target.data;
    }

    Polynomial sum;
    sum.data.resize(bigger_range);

    for (int i = 0; i < smaller_range; i++) {
        sum.data[i] = data[i] + target.data[i];
    }

    for (int i = smaller_range; i < bigger_range; i++) {
        sum.data[i] = biggerVector[i];
    }
    return sum;
}

Polynomial Polynomial:: operator-(const Polynomial &target) {
    int long smaller_range = target.data.size();
    int long bigger_range = data.size();
    vector <int> biggerVector = data;

    if (target.data.size() > data.size()){
        bigger_range = target.data.size();
        smaller_range = data.size();
        biggerVector = target.data;
    }

    Polynomial difference;
    difference.data.resize(bigger_range);

    for (int i = 0; i < smaller_range; i++) {
        difference.data[i] = data[i] - target.data[i];
    }

    for (int i = smaller_range; i < bigger_range; i++) {
        difference.data[i] = biggerVector[i];
    }
    return difference;
}

Polynomial Polynomial:: operator*(const Polynomial &target) {

}

Polynomial::~Polynomial(){}