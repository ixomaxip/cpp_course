#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "./02.names3.cpp"

using namespace std;

int main() {
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
    }
    return 0;
}