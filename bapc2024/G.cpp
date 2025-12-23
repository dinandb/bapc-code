



#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

tuple<int,int,int,int> mod5(vector<int> prices) {
    int n = prices.size();
    
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    int mod5_res;
    // cout << "a\n";
    for (int i = 0; i < n; i++) {
        mod5_res = prices.at(i)%5;
        if (mod5_res == 0) {
            continue;
        }
        else if (mod5_res == 1) {
            count_1++;
        }
        else if (mod5_res == 2) {
            count_2++;
        }
        else if (mod5_res == 3) {
            count_3++;
        }
        else if (mod5_res == 4) {
            count_4++;
        }

    }
    // cout << "b\n";
    return make_tuple(count_1, count_2, count_3, count_4);
}


int main() {
    int n;
    
    double price;
    cin>> n;
    vector<int> prices(n);
    int total_price = 0;
    for (int i = 0; i < n; i++) {
        // cout << prices.size() << endl;
        cin >> price;
        // cout << (int) lround(price * 100) << endl;
        prices.at(i) = (int) lround(price*100);
        total_price += (int) lround(price*100);
    }
    tuple<int,int,int,int> counts = mod5(prices);
    int total_korting = 0;
    int count1 = get<0>(counts);
    int count2 = get<1>(counts);
    int count3 = get<2>(counts);
    int count4 = get<3>(counts);
    // cout << "counts retrieved\n";
    // cout << "counts: " << count1 << ", " << count2 << ", " << count3 << ", " << count4 << ", " << endl;

    total_korting += 2*count2;
    count2 = 0;

    // int amount_1_pairs;
    // if (count1 % 2 == 0) {
    //     amount_1_pairs = count1 /2;
    // }
    // else {
    //     amount_1_pairs = (count1-1)/2;
    // }
    // count1 -= amount_1_pairs*2;

    total_korting += count1;
    count1 = 0;

    int amount_34_pairs = min(count3, count4);

    count3 -= amount_34_pairs;
    count4 -= amount_34_pairs;

    total_korting += 2*amount_34_pairs;

    int triple_4;
    int double_3;
    if (count1 == 0) {
        if (count3 == 0) {
            triple_4 = count4/3;
            total_korting += 2*triple_4;
        }
        else {
            double_3 = count3/2;
            total_korting += double_3;
        }
    }
    // else {
    //     if (count3 >= 2) {
    //         count1--;
    //         count3 -= 2;
    //         total_korting += 2;
    //         // 3 paren weghalen 
    //         double_3 = count3/2;
    //         total_korting += 2*double_3;
    //     }
    //     else {
    //         // 1 1, 0 of 1 3'en, als 0 3en, dan mogelijk vieren, anders niet
    //         if (count3 == 1) {
    //             total_korting += 1; // voor de 1
    //         }
    //         else {
                
    //             triple_4 = count4/3;
    //             total_korting += 2*triple_4;
    //             total_korting += 1; // voor de 1
    //             // cout << "halloooo\n";
    //         }
    //     }
    // }
    string final = to_string(total_price-total_korting);
    if (final.size() == 0) {
        cout <<"sdoifjsdoifjsdiofjsdio" << endl;
    }
    if (final.size() == 1) {
        final.insert(0, 1, '0');
    }
    final.insert(final.size()-2, 1, '.');
    if (final.size() == 3) {
        final.insert(0, 1, '0');
    }
    cout << final << endl;
    


    return 0;
}
