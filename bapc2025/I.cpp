#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
int main() {
    int n;
    double w;
    cin >> n;
    cin >> w;
    
    vector<tuple<double,double>> WM;
    int p, t;
    for (int i = 0; i < n; i++) {
        cin >> p >> t;
        
        WM.emplace_back(p,t);

    }
    sort(WM.begin(), WM.end(), [](const auto& a, const auto&b) {
        return get<1>(a) < get<1>(b);
    });
    // for (const auto& [p_val, t_val] : WM) {
    //     cout << "(" << p_val << ", " << t_val << ")\n";
    // }
    vector<tuple<double,double>> DP;
    DP.emplace_back(w/get<0>(WM.at(0)) + 2*get<1>(WM.at(0)), get<0>(WM.at(0)));
    double werktijd;
    double total_rate;
    double T_bespaar;
    for (int i = 1; i < n; i++) {
        werktijd = get<0>(DP.at(i-1)) - 2*get<1>(WM.at(i));
        if (werktijd < 0) break;
        total_rate = get<0>(WM.at(i)) + get<1>(DP.at(i-1));
        T_bespaar = (werktijd*get<0>(WM.at(i)))/total_rate;
        DP.emplace_back(get<0>(DP.at(i-1))-T_bespaar, total_rate);
    }
    // for (const auto& [fst, snd] : DP) {
    //     cout << "(" << fst << ", " << snd << ")" << endl;
    // }
    cout << get<0>(DP.at(DP.size()-1)) << endl;
    return 0;
}