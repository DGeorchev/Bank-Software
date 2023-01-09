#include <iostream>
using namespace std;
#include <fstream>

int main() {
    fstream my_file;
    my_file.open("users.txt");
    if (!my_file) {
        cout << "File not created!";
    }
    else {
        cout << "File created successfully!";
        my_file << "Hello world"<<" "<<"Hi"<<"hello";
        my_file << "Hello world"<<" "<<"Hi"<<"hello";
        my_file.close();
    }
    return 0;
}
