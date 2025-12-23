

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <tuple>


using namespace std;

long max(long a, long b) {
    if (a > b) return a;
    return b;
}

int main () {
    int n;
    cin >> n;
    long c;
    cin >> c;
    long arrivals;
    vector<long> arriving_ppl = {};
    for (int i = 0; i < n; i++) {
        cin >> arrivals;
        arriving_ppl.push_back(arrivals);
    }

    vector<tuple<long, long>> DP (n, make_tuple(0, 0));

    DP.at(0) = make_tuple(arriving_ppl.at(0), arriving_ppl.at(0)/c);

    for (int i = 1; i < n; i++) {
        long rest = max(get<0>(DP.at(i-1)) - c, 0);
        DP.at(i) = make_tuple(rest + arriving_ppl.at(i), (rest + arriving_ppl.at(i))/c);
    }
    // cout << "DP:\n";
    // for (int i = 0; i < n; i++) {
    //     cout << "(" << get<0>(DP.at(i)) << ", " << get<1>(DP.at(i)) << ")" <<  ", ";
    // }cout << endl;
    long smallest_wait = __LONG_MAX__;
    
    
    long best_moment_to_start = -1;
    for (int i = 0; i < DP.size(); i++) {
        long cur_wait = get<1>(DP.at(i));
        if (cur_wait < smallest_wait && cur_wait + i < DP.size()) {
            cout << "new best time = " << cur_wait << " at moment = " << i << endl;
            smallest_wait = cur_wait;
            best_moment_to_start = i;
        }
    }
    // cout << "best time = " << smallest_wait << endl;
    // cout << "best moment to start = " << best_moment_to_start << endl;
    if (best_moment_to_start == -1) {
        cout << "impossible\n";
        return 0;
    }
    cout << best_moment_to_start << endl;

    return 0;
}