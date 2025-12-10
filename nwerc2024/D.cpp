#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> fillDP (vector<int> party_sizes, int total) {
    int n = party_sizes.size();

    vector<vector<int>> dp1(n, vector<int>(total+1, 0));
    vector<vector<int>> dp2(n, vector<int>(total+1, 0));

    // party_sizes is sorted
    for (int index = 0; index < party_sizes.size(); index++) {
        // set dp [index, party_size] = true
        int party_size = party_sizes.at(index);
        if (index % 2 == 0) {
            
            // go through the entire dp, for every true at index i, j set also true at index 
            // i, j + party_size (the min does not need to be taken, just i, if we
            // sort party_sizes beforehand)
        
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < total+1-party_size; j++) {
                    if (dp1.at(i).at(j)) {
                        // cout << "there are " << dp1.at(i).at(j-party_size) << " ways to create " << j - party_size << " with smallest party has size " << party_sizes.at(i) << ", now j = " << j << endl; 
                        dp2.at(i).at(j+party_size) += dp1.at(i).at(j);
                    }
                }
            }
            
            dp2.at(index).at(party_size) += 1;
            dp1 = dp2;
        }
        else {
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < total+1-party_size; j++) {
                    if (dp2.at(i).at(j)) {
                        // cout << "there are " << dp2.at(i).at(j-party_size) << " ways to create " << j - party_size << " with smallest party has size " << party_sizes.at(i) << ", now j = " << j << endl; 
                        dp1.at(i).at(j+party_size) += dp2.at(i).at(j); 
                    }
                }
            }
            dp1.at(index).at(party_size) += 1;
            dp2 = dp1;
        }
        // cout << "index = " << index << endl;
        // for (vector<int> vec : dp1) {
        //     for (int i : vec) {
        //         cout << i << ", ";
        //     }
        //     cout << endl;
        // }
        
    }
    // cout << "=================\n";
    return dp1;
} 


int countParliaments(vector<vector<int>> dp, vector<int> party_sizes) {
    int n = dp.size();
    int total = dp.at(0).size()-1;
    
    int min_size_parliament = total/2 + 1; // works for both total odd and even
    // cout << "minsize/total = " << min_size_parliament << "/" << total << endl;
    int counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = min_size_parliament; j < total + 1; j++) {
        
            if (dp[i][j]) {
                // cout << "seeing dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
                if (j - party_sizes.at(i) < min_size_parliament) {
                    counter += dp[i][j];
                    // cout << "ADDING dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
                }
            }

        }
    }

    return counter;
    }

int main() {

    int n;
    int total = 0;
    cin >> n;
    vector<int> party_sizes ={};
    int elt;
    for (int i = 0; i < n; i++) {
        cin >> elt;
        total += elt;
        party_sizes.push_back(elt);
    }
    sort(party_sizes.begin(), party_sizes.end());
    vector<vector<int>> dp = fillDP(party_sizes, total);
    // for (vector<int> vec : dp) {
    //     for (int i : vec) {
    //         cout << i << ", ";
    //     }
    //     cout << endl;
    // }
    
    
    cout <<  countParliaments(dp, party_sizes) << endl;
    return 0;
}