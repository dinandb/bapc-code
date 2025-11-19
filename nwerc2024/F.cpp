#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

int main() {

    int n, q;
    cin >> n >> q;
    vector<int> vec ={};
    
    
    int c;
    for (int i = 0; i < n; i++) {
        cin >> c;
        vec.push_back(c);
    }
    string command;
    int amount;
    for (int i = 0; i < q; i++) {
        cin >> command;
        if (command == "?") {
            cin >> c;
        }
        else {
            cin >> c >> amount;
        }
         
        // do something
    }
    vector<int> first_increasing_cap(n, 0);
    for (int i = 0; i < n; i++) {
        int elt  = vec.at(i);
        bool found_next = false;
        for (int j = i+1; j < n; j++) {
            if (vec.at(j) > elt) {
                first_increasing_cap.at(i) = j;
                found_next = true;
                break;
            }
        }
        if (!found_next)
        {
            first_increasing_cap.at(i) = -1;
        }
    }
    // add something for the last element?
    // for (int i : vec) {
    //     cout << i << endl;
    // }
    // for (int i : first_increasing_cap) {
    //     cout << i << endl;
    // }

    

    return 0;
}  