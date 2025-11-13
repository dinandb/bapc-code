#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>



using namespace std;

int main() {

    int n;
    cin >> n;
    cin.ignore();
    vector<tuple<string, string>> vec = {};
    string elt;
    string first_cap_word;
    for (int i = 0; i < n; i++) {
        getline(cin, elt);
        for (int j = 0; j < elt.size(); j++) {
            if ('A' <= elt.at(j) && elt.at(j) <= 'Z') {
                first_cap_word = elt.substr(j);
                break;
            }
            // what if no capital is found?
        }
        // find the first capitlized word, add it
        vec.push_back(make_tuple(first_cap_word, elt));
    }
    sort(vec.begin(), vec.end());

    for (tuple<string,string> tup : vec) {
        cout << get<1>(tup) << endl;
    }
    
    return 0;
}