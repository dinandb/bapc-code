

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>

using namespace std;
vector<int> empty_vec_int(int size) {
    vector<int> res(size);
    return res;
}
vector<unsigned long long> empty_vec(int size) {
    vector<unsigned long long> res(size);
    return res;
}
unsigned long long power(unsigned long long a, int b) {
    unsigned long long result = 1;
    unsigned long long base = a;

    while (b > 0) {
        if (b & 1) {
            result *= base;
        }
        base *= base;
        b >>= 1;   // divide b by 2
    }

    return result;
}

vector<vector<unsigned long long>> build_hash_substr_to_index(const string s) {
    int n = s.size();
    vector<vector<unsigned long long>> indices(n, empty_vec(n));
    // vector<vector<int>> counts (n, empty_vec_int(n));
    
    int b = 472564;
    unsigned long long M = 40275937593893785;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // substr is s[i]..s[j]
            if (j > i) {
                //
                unsigned long long prev = indices.at(i).at(j-1);
                // calc res[i,j] with prev
                unsigned long long added = s[j]*power(b, j-i);

                indices.at(i).at(j) = (prev + added) % M;
                
            }
            else {
                // just calc res[i,j]
                indices.at(i).at(j) = s[i];
            }
        }
    }
    return indices;
}

unordered_map<unsigned long long, int> count_occurences(const vector<vector<unsigned long long>> indices) {
    int n = indices.size();
    // vector<vector<int>> occurences(n, empty_vec_int(n));

    unordered_map<unsigned long long, int> last_seen_substr_end;
    unordered_map<unsigned long long, int> occurences;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // check of deze substr al mag, dan, de occurence 1tje hoger
            if (last_seen_substr_end.find(indices.at(i).at(j)) != last_seen_substr_end.end() && last_seen_substr_end[indices.at(i).at(j)] >= i) {
                continue;
            }
            else {
                // we havent seen it yet, or the last ending of this substring was smaller than i, meaning we are allowed to pick it again
                if (last_seen_substr_end.find(indices.at(i).at(j)) == last_seen_substr_end.end()) occurences[indices.at(i).at(j)] = 1;
                
                else occurences[indices.at(i).at(j)] += 1;
                
            }
        }
    }
    return occurences;

}

int main(){
    string s;
    cin >> s;

    vector<vector<unsigned long long>> indices = build_hash_substr_to_index(s);

    // cout << "indices\n";
    // for (vector<unsigned long long> row : indices) {
    //     for (unsigned long long elt : row) {
    //         cout << elt << ",";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    unordered_map<unsigned long long, int> occurences = count_occurences(indices);
    cout << "occurencs\n";
    for (vector<unsigned long long> row : indices) {
        for (unsigned long long elt : row ) {
            cout << occurences[elt] << ", ";
        }
        cout << endl;
    }
    cout << endl;

}