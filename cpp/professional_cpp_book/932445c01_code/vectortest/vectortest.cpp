#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // Create a vector of strings, using C++11 uniform initialization

    // dlf: did not compile vs2010 or vs2012:
    vector <string> myVector = { "A first string", "A second string" };

    // use had to do it this way previously:
    //    vector <string> myVector;
    //    myVector.push_back("a first string");
    //    myVector.push_back("2nd string");

    // Add some strings to the vector using push_back
    myVector.push_back("A third string");
    myVector.push_back("The last string in the vector");

    // Iterate over the elements in the vector and print them
    for (auto iterator = myVector.cbegin(); iterator != myVector.cend(); ++iterator)
        cout << *iterator << endl;

    // Print the elements again using C++11 range-based for loop
    for (auto& str : myVector)
        cout << str << endl;

    return 0;
}