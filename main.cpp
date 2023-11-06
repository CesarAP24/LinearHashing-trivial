#include "LinearHash.h"
#include <iostream>
#include <string>
#include "tester.h"

using namespace std;

int main(int argc, char const *argv[])
{
    LinearHash<int, float> linearHashing(2, 2);

    linearHashing.put(1, 1.1);
    linearHashing.put(2, 7.2);
    linearHashing.put(3, 3.45);
    linearHashing.put(5, 42.4);
    linearHashing.put(14, 4.5);
    linearHashing.put(7, 7.6);

    ASSERT(linearHashing.search(1) == true, "search is not working");
    ASSERT(linearHashing.search(45) == false, "search is not working");

    ASSERT(linearHashing.get(1) == 1.1, "get is not working");
    ASSERT(linearHashing.get(45) == 0, "get is not working");
    /*
    0: []
    1: [1:1.1, 5:42.4]
    2: [2:7.2, 14:4.5]
    3: [3:3.45, 7:7.6]
    */

   //assert del print
    ASSERT(linearHashing.toString() == "0: []\n1: [1:1.1, 5:42.4]\n2: [2:7.2, 14:4.5]\n3: [3:3.45, 7:7.6]\n", "toString is not working");
    

    linearHashing.erase(1);
    linearHashing.erase(2);
    ASSERT(linearHashing.search(1) == false, "search is not working");
    ASSERT(linearHashing.search(2) == false, "search is not working");

    
    return 0;
}
