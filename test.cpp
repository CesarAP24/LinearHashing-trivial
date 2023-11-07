#include "bucket.h"
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{
    Bucket<int, float> b(2);
    b.insert(1, 1.1);
    b.insert(2, 2.2);
    b.insert(3, 3.3);
    b.insert(4, 4.4);

    cout << b.toString() << endl;

    return 0;
}
