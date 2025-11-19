#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

// A tuple of (index, value)
struct Item {
    int index;
    int value;
};

// Comparator: only compare by value, ties broken by index
struct Cmp {
    bool operator()(const Item& a, const Item& b) const {
        if (a.value != b.value) return a.value < b.value;
        return a.index < b.index;   // ensure strict ordering
    }
};

class PopSet {
private:
    set<Item, Cmp> s;

public:
    // Insert (index, value), return all items with smaller value
    vector<Item> insert_and_pop_smaller(int index, int value) {
        Item x{ index, value };

        // find first element with value >= x.value
        auto it = s.lower_bound(x);

        // collect smaller items
        vector<Item> smaller;
        for (auto p = s.begin(); p != it; ++p)
            smaller.push_back(*p);

        // erase smaller items
        s.erase(s.begin(), it);

        // insert the new item
        s.insert(x);

        return smaller;
    }
};


vector<int> findNextLarger(vector<int> input) {
    vector<int> result(input.size());
    PopSet ps;

    for (int i = 0; i < input.size(); i++) {
        vector<Item> smaller = ps.insert_and_pop_smaller(i, input[i]);
        for (int j = 0; j < smaller.size(); j++) {
            result.at(smaller[j].index) = i;
        }
    }

    return result;
}

int main() {

    int n, q;
    cin >> n >> q;
    vector<int> cap ={};


    int c;
    for (int i = 0; i < n; i++) {
        cin >> c;
        cap.push_back(c);
    }
    vector<tuple<bool, int, int>> command_amount; // true if it is addition, layer, amount
    string command;
    int amount;
    int layer;
    for (int i = 0; i < q; i++) {
        cin >> command;
        cin >> layer;
        if (command != "?") { // not query -> addition
            cin >> amount;
            command_amount.push_back(make_tuple(true, layer-1, amount));
        }
        else { // query
            command_amount.push_back(make_tuple(false, layer-1, 0));
        }
    }
    vector<int> first_increasing_cap(n, 0);
    for (int i = 0; i < n; i++) {
        int elt  = cap.at(i);
        bool found_next = false;
        for (int j = i+1; j < n; j++) {
            if (cap.at(j) > elt) {
                first_increasing_cap.at(i) = j;
                found_next = true;
                break;
            }
        }
        if (!found_next)
        {
            first_increasing_cap.at(i) = -1;
        }
    }
    // add something for the last element?
    // for (int i : cap) {
    //     cout << i << endl;
    // }
    // for (int i : first_increasing_cap) {
    //     cout << i << endl;
    // }
    vector<int> amounts(n, 0);
    // nu de queries uitvoeren.
    for (int i = 0; i < command_amount.size(); i++) {

        tuple<bool,int,int> cur_command = command_amount.at(i);
        // cout << "command = " << get<0>(cur_command) << ", " << get<1>(cur_command) << ", " << get<2>(cur_command) << endl;
        if (!get<0>(cur_command)) { // addition is true, hier moeten we komen als het niet addition is
            cout << amounts.at(get<1>(cur_command)) << endl;
        }
        else {
            // going to add
            // int prev_layer = -1;
            int potential_next;
            int cur_layer = get<1>(cur_command);
            int amount_to_fill = get<2>(cur_command);
            int to_pour;
            while (amount_to_fill > 0 && cur_layer != -1) {
                to_pour = min(cap.at(cur_layer) - amounts.at(cur_layer), amount_to_fill);

                // cout << "pouring " << to_pour << " at layer " << cur_layer << endl;
                amounts.at(cur_layer) += to_pour;
                // if (amounts.at(cur_layer) == cap.at(cur_layer)) {
                //     // if prev_layer = -1, we are at the first and should do nothing
                //     // else, prev_layer should now point to the successor of cur_layer
                //     if (prev_layer != -1) {
                //         first_increasing_cap.at(prev_layer) = first_increasing_cap.at(cur_layer);
                //     }
                // }
                // prev_layer = cur_layer;
                potential_next = first_increasing_cap.at(cur_layer);
                vector<int> encountered = {};
                while ( potential_next != -1 && amounts.at(potential_next) >= cap.at(potential_next)) { // next is full
                    encountered.push_back(potential_next);
                    potential_next = first_increasing_cap.at(potential_next); // look at next of next
                    first_increasing_cap.at(cur_layer) = potential_next; // update next of cur to be next of next
                }
                for (int i : encountered) {
                    first_increasing_cap.at(i) = potential_next;
                }
                cur_layer = potential_next;
                amount_to_fill -= to_pour;
            }
        }
    }




    return 0;
}