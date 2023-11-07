#include "LinearHash.h"
#include <iostream>
#include <string>
#include "tester.h"

using namespace std;

int main(int argc, char const *argv[])
{
    LinearHash<int, string> linearHashing(2, 2);

    linearHashing.put(1, "Alo");
    linearHashing.put(2, "quien");
    linearHashing.put(3, "es");
    linearHashing.put(5, "quien");
    linearHashing.put(14, "habla");
    linearHashing.put(7, "porfavor");

    linearHashing.print();

    ASSERT(linearHashing.search(1) == true, "search is not working");
    ASSERT(linearHashing.search(45) == false, "search is not working");

    ASSERT(linearHashing.get(1) == "Alo", "get is not working");
    ASSERT(linearHashing.get(45) == "", "get is not working");
    /*
    0: []
    1: [1:"Alo", 5:"quien"]
    2: [2:"quien", 14:"habla"]
    3: [3:"es", 7:"porfavor"]
    */

    //assert del print
    ASSERT(linearHashing.toString() == "0: []\n1: [1:Alo, 5:quien]\n2: [2:quien, 14:habla]\n3: [3:es, 7:porfavor]\n", "toString is not working");

    linearHashing.erase(1);
    linearHashing.erase(2);
    ASSERT(linearHashing.search(1) == false, "search is not working");
    ASSERT(linearHashing.search(2) == false, "search is not working");

    
    return 0;
}
