#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int findRepeat(int n, long long k) {
    int counter = 0;
    int mid = n/2 + 1;
    int index = 2;
    do {
        counter += 1;
        if (index % 2 == 1) {
            index = (index+1)/2;
        }
        else {
            index = mid + index/2;
        }
    } while (index != 2);
    
    cout << "counter = " << counter << endl;
    return counter;
}

int main_odd(int n, long long int k, string word) {
    int counter = findRepeat(n,k);
    k -= counter*(k/counter);
    if (k == 0) {
        cout << word << endl;
        return 0;
    }
    string new_word;
    string cur_word = word + word;
    for (int i = 0; i < k; i++) {
        new_word = "";
        for (int j = 0; j < word.size(); j ++) {
            new_word += cur_word.at((2*j)%cur_word.size());
        }
        cur_word = new_word;
        // cout << new_word << endl;
        if (new_word==word) {
            // cout << "word\n";
            long long int m = k/(i+1);
            k -= (i+1)*(m-1);
        }
        // cout << cur_word << endl;
    }

    cout << new_word << endl;
    return 0;
}

int main_even(int n, long long int k, string word) {
    string new_word;
    int hoi;
    string cur_word = word;
    for (int i = 0; i < k; i++) {
        new_word = "";
        for (int j = 0; j < word.size(); j ++) {
            new_word += cur_word.at((2*j)%cur_word.size());
        }
        cur_word = new_word;
        // cout << new_word << endl;
        // cout << cur_word << endl;
        cout << cur_word << endl;
        cin >> hoi;
    }


    return 0;
}

int main() {
    int n;
    long long int k; 
    string word;
    cin >> n >> k >> word;
    if (n % 2 == 1) {
        return main_odd(n, k, word);
    }
    else {
        return main_even(n, k, word);
    }
}