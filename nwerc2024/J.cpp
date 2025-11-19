#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<tuple<int,int,int,int,int>> vec ={};
    int elt1;
    int elt2;
    int elt3;
    for (int i = 0; i < n; i++) {
        cin >> elt1 >> elt2 >> elt3;
        vec.push_back(make_tuple(elt3, elt2, elt1,i,0));
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());

    for (int i = 0; i < n; i++) {
        // we want to maximize the length of the crane. 
        get<4>(vec.at(i)) = get<0>(vec.at(i));
        for (int j = i - 1; j >= 0; j--) {
            // get dist from i to j
            double dist = sqrt( pow(get<1>(vec.at(i)) - get<1>(vec.at(j)), 2) + pow(get<2>(vec.at(i)) - get<2>(vec.at(j)), 2)   );
            int dist_rounded = floor(dist);
        
            get<4>(vec.at(i)) = min(dist_rounded, get<4>(vec.at(i)));
        }
    }
    // sort by second to last arg in the uple
    sort(vec.begin(), vec.end(), [](auto &a, auto &b) {
    return get<3>(a) < get<3>(b);  // sort by second element
    });
    for (int i = 0; i < n; i++) {
        cout << get<4>(vec.at(i)) << endl;
    }

    return 0;
}