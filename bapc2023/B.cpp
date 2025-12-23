#include <iostream>
#include <math.h>
using namespace std;



int main() {
    long long n;
    cin >> n;
    int no_attacks = 0;
    long long power = 1;
    while (power < n) {
        no_attacks++;
        power *= 2;
    }
    cout << no_attacks + 1 << endl;
}