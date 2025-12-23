

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;



int main () {
    int n, m;
    cin >> n; // no_cities
    cin >> m; // no_letters
    string name;
    vector<string> names = {};
    for (int i = 0; i < n; i++) {
        cin >> name;
        names.push_back(name);
    }

    vector<int> counts (26,0);
    string final_name = "";
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < 26; k++) {
            counts.at(k) = 0;
        }
        for (int i = 0; i < n; i++) {
            char letter = names.at(i).at(j);
            counts.at(letter - 'a')++;
            // cout << "at name " << i << ", char " << j << ", we count a " << letter << ", with index = " << letter - 'a' << endl;
        }
        char to_add = 'a';
        int max_count = 0;
        for (int k = 0; k < 26; k++) {
            if (counts.at(k) > max_count) {
                max_count = counts.at(k);
                to_add = 'a' + k;
                // cout << "new to_add = " << to_add << ", because its count was " << counts.at(k) << endl;
            }
        }
        
        final_name += to_add;
    }
    cout << final_name << endl;

    return 0;
}
