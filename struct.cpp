#include <iostream>

using namespace std;

struct mystr {
    char a;
    char b;
};

void output ( mystr & );

int main() {

    mystr test;
    test = { 'a', 'b' };

    cout << "a = " << test.a << endl;
    cout << "b = " << test.b << endl;

    output( test );
    
    return 0;

}

void output( mystr & something ) {
    cout << "Now in output function:" << endl;
    cout << "a = " << something.a << endl;
    cout << "b = " << something.b << endl;
}
