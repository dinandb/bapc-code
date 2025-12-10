#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

vector<vector<bool>> SubsetSum(vector<int> &arr, int sum) {
    int n = arr.size();

    // Create a 2D vector for storing results
  	// of subproblems
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

    // If sum is 0, then answer is true (empty subset)
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    // Fill the dp table in bottom-up manner
    for (int i = 1; i <= n; i++) {
      
        for (int j = 1; j <= sum; j++) {
            if (j < arr[i - 1]) {
              
               // Exclude the current element
                dp[i][j] = dp[i - 1][j]; 
            }
            else {
              
               // Include or exclude
                dp[i][j] = dp[i - 1][j] 
                || dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    return dp;
}


int main() {
    int n;
    cin >> n;
    int w;
    int total = 0;
    vector<int> moles = {};
    for (int i = 0; i < n; i++) {

        cin >> w;
        total += w;
        moles.push_back(w);
    }
    
    
    vector<vector<bool>> SS1 = SubsetSum(moles, total);
    vector<int> moles_rev = moles;
    reverse(moles_rev.begin(), moles_rev.end());
    
    vector<vector<bool>> SS2 = SubsetSum(moles_rev, total);
    
    for (size_t i = 0; i < SS1.size(); i++) {
        vector<bool> sub = SS1.at(i);
        for (size_t j =0; j < sub.size(); j++) {
            cout << sub.at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (size_t i = 0; i < SS2.size(); i++) {
        vector<bool> sub = SS2.at(i);
        for (size_t j =0; j < sub.size(); j++) {
            cout << sub.at(j) << " ";
        }
        cout << endl;
    }
    cout << "now we print the possible moles\n";
    int target;
    
    for (int i=1; i < n+1; i++) {
        
        if ((total - moles.at(i-1)) % 2 != 0) {
            // not possible to be a mole
            cout << i << " cannot be a mole\n";
            continue;
        }
        target = (int) ((total - moles.at(i-1))/2);

        if (i==1) {
            if (SS2[n-1][target]) {
                cout << "mole: " << i <<endl;
            }
            continue;
            
        }
        else if (i==n) {
            if (SS1[n-1][target]) {
                cout << i;
            }
            continue;
        }
        // cout << "we get here\n";

        for (int t = 0; t <= target; t++) {
            if (SS1[i-1][t] && SS2[n-(i+1)][target-t]) {
                cout << i;
                break;
            }
            // else {
            //     cout << "either not SS1(" << i-1 << ", "<< t << ") or not SS2(" << n-(i+1) << "," << target-t << ")\n";
            // }
        }
    }
    cout << endl;


    return 0;
}