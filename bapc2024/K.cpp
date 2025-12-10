#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional> 
#include <unordered_set>
#include <unordered_map>

using namespace std;

using DPelement = vector<tuple<int,int>>;
// score, vector of (start, end)

DPelement init_empty_element(int size) {
    vector<tuple<int,int>> empty_vector(size, make_tuple(0,0));
    return empty_vector;
}

vector<tuple<int,int>> find_begin_ends(string s, string sub_s) {
    // find_begin_ends bv tuple(0, 2). dan was er een substr beginnend bij 0, eindigend bij 2 (inclusief)
    vector<tuple<int,int>> begin_ends = {};
    // int ignore_amount = 0;
    for (int i = 0; i < s.size() - sub_s.size() + 1; i++) {
        // if (ignore_amount > 0) {
        //     ignore_amount--;
        // }
        // else {
            bool is_sub_string = true;
            for (int j = 0; j < sub_s.size(); j++) {
                if (s[i+j] != sub_s[j]) {
                    is_sub_string = false;
                    break;
                }
            }
            if (is_sub_string) {
                begin_ends.push_back(make_tuple(i, i + sub_s.size() - 1));
                // ignore_amount += sub_s.size()-1;
            }
        // }
    }
    return begin_ends;
}

int getScore(const vector<tuple<int,int>>& begin_ends, int len_substr, int n) {
    // score = len(s*) + len(substr)
    // len(s*) = n - amount_substr_occurence*len_substr + amount_substr_occurence + len_substr
    
    // walk through begin_ends, remembering the last valid end. 
    if (begin_ends.size() == 0) return INT32_MAX;
    tuple<int,int> first_begin_end = begin_ends.at(0);
    int last_valid_end = get<1>(first_begin_end);
    int amount_valid_substr_occurence = 1;
    for (tuple<int,int> begin_end : begin_ends) {
        if (get<0>(begin_end) > last_valid_end) {
            amount_valid_substr_occurence++;
            last_valid_end = get<1>(begin_end);
        }
    }
    
    return (n - amount_valid_substr_occurence*len_substr + amount_valid_substr_occurence) + len_substr;
}

vector<tuple<int,int>> update_begin_ends_from_left(vector<tuple<int,int>> begin_ends, char c, string s) {
    vector<int> mark_to_be_erased;
    for (int i = 0; i < begin_ends.size(); i++) {
        // if i has been cancelled, do not use it
        // it must have been cancelled by the last one (i-1)
        if (mark_to_be_erased.size() == 0 || mark_to_be_erased.at(mark_to_be_erased.size()-1) != i) {
            int end = get<1>(begin_ends.at(i));
            if (end+1 >= s.size() || s[end+1] != c) {
                // remove this end at index i
                // begin_ends.erase(begin_ends.begin() + i);
                mark_to_be_erased.push_back(i);
            }
            else {
                // we keep it, but this end should be increased by 1
                get<1>(begin_ends.at(i))++;
                // add a check if we intsect the begin of the next (if next exists). if this is the case, erase at i+1
                // if (i < begin_ends.size()-1) {
                //     // if (get<1>(begin_ends.at(i)) > get<0>(begin_ends.at(i+1))) {
                //     //     cout << "this should never happend\n";
                //     // }
                //     // if (get<1>(begin_ends.at(i)) == get<0>(begin_ends.at(i+1))) {
                //     //     // begin_ends.erase(begin_ends.begin()+i+1);

                //     //     // 
                //     //     mark_to_be_erased.push_back(i+1);
                //     // }
                // }
            }
        }
    }
    // remove uniques from mark_to_be_erased
    // sort(mark_to_be_erased.begin(), mark_to_be_erased.end());
    // mark_to_be_erased.erase(unique(mark_to_be_erased.begin(), mark_to_be_erased.end()), mark_to_be_erased.end());

    // sort reverse

    // sort(mark_to_be_erased.rbegin(), mark_to_be_erased.rend());

    // remove from list
    for (int i = 0; i < mark_to_be_erased.size(); i++) {
        int remove_index = mark_to_be_erased.at(mark_to_be_erased.size()-1-i);
        begin_ends.erase(begin_ends.begin() + remove_index);
    }

    // cout << "length ends after update " << begin_ends.size() << endl;
    return begin_ends;
}

vector<int> emptyvector(int n) {
    vector<int> vec(n,-1);
    return vec;
}


int makeDP(string s) {
    int n = s.size();
    vector<DPelement> all_begin_ends;
    vector<vector<int>> DP (n, emptyvector(n));
    // for (int i = 0; i < n; i++) {
    //     DP.push_back({});
    //     for (int j = 0; j < n; j++) {
    //         DP.at(i).push_back(init_empty_element(n));
    //     }
    // }


    // now we init the DP

    // hash<string> hashmap; // this takes a substring of s, and maps it to an int. this is the key. value is the associated vector<tuple<int,int>> begin_ends
    unordered_set<string> seen;
    unordered_map<string,int> substr_index;
    long no_seen_substrings = 0;

    int max_score = INT32_MAX;
    for (int j = 0; j < n-1; j++) {
        // substring = s[0]..s[j] -> fill the DP
        // substring = s.substr(0, j+1), j+1 is the length
        string substr = s.substr(j, 2);
        if (seen.count(substr)) {
            // is true if not count == 0, thus we have already seen it
            // index =
            // cout << "we have already seen substr " << substr << endl;
            int index = substr_index[substr];
            DP.at(j).at(j+1) = index;
            continue;
        }
        
        seen.insert(substr);

        
        vector<tuple<int,int>> begin_ends = find_begin_ends(s, substr);

        // cout << "for substr " << substr << ", we have the following tuples \n";
        // for (tuple<int,int> begin_end : begin_ends) {
        //     cout << "(" << get<0>(begin_end) << ", " << get<1>(begin_end) << "), ";
        // }
        // cout << endl;


        int score = getScore(begin_ends, substr.size(), n);
        if (score < max_score) {
            // cout << "score improved from " << max_score << " to " << score;
            // cout << "\nachieved with substr: " << substr << endl; 
            max_score = score;
        }
        // cout << "initing DP at " << j << ", " << j+1 << endl;
        // cout << "setting ends to ";
        // for (int begin_end : ends) {
        //     cout << end << ", ";
        // }
        // cout << endl;
        all_begin_ends.push_back(begin_ends);
        substr_index[substr] = no_seen_substrings;
        DP.at(j).at(j+1) = no_seen_substrings;
        no_seen_substrings++;
    }
    // cout << "DP after init\n";
    // for (vector<int> dp : DP) {
    //     for (int d : dp) {
    //         cout << d << ", ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    int total_removed = 0;
    for (int i = 0; i < n-2; i++) {
        for (int j = 0; j < n-2-i; j++) {
            string substr = s.substr(j,i+3);
            if (seen.count(substr)) {
                // is true if not count == 0, thus we have already seen it
                // index =
                int index = substr_index[substr];
                DP.at(j).at(j+i+2) = index;
                continue;
            }
            seen.insert(substr);

            // cout << "using for substring "  << substr << ":\n";
            // for (tuple<int,int> begin_end : all_begin_ends.at(DP.at(j).at(i+1+j) - total_removed)) {
            //     cout << "(" << get<0>(begin_end) << ", " << get<1>(begin_end) << "), ";
            // }       
            // cout << endl;
            vector<tuple<int,int>> begin_ends_from_left = update_begin_ends_from_left(all_begin_ends.at(DP.at(j).at(i+1+j) - total_removed), s[j+i+2], s);
            // cout << "for substr " << substr << ", we have the following tuples \n";
            // for (tuple<int,int> begin_end : begin_ends_from_left) {
            //     cout << "(" << get<0>(begin_end) << ", " << get<1>(begin_end) << "), ";
            // }
            // cout << endl;
            // vector<tuple<int,int>> begin_ends_from_left = update_begin_ends_from_left(DP.at(j).at(i+1+j), s[j+i+2], s);
            int new_score = getScore(begin_ends_from_left, i+3, n);
            
            if (new_score < max_score) {
                // cout << "score improved from " << max_score << " to " << new_score;
                // cout << "\nachieved with substr: " << substr << endl; 
                max_score = new_score;
            }
            all_begin_ends.push_back(begin_ends_from_left);
            substr_index[substr] = no_seen_substrings;
            DP.at(j).at(j+i+2) = no_seen_substrings; 
            no_seen_substrings++;
        }
        //we have walked a diagonal. we can now walk the previous diagonal, save the indices and remove all values at these indices from the big all_begin_ends vector
        vector<int> to_remove = {};
        // we have now everywhere i <- i-1
        for (int j = 0; j < n-2-(i-1); j++) {
            if (find(to_remove.begin(), to_remove.end(), DP.at(j).at(j+i-1+2)-total_removed) == to_remove.end()) {
                to_remove.push_back(DP.at(j).at(j+i-1+2)-total_removed);
            }
            
            // cout << "going to remove index " << DP.at(j).at(j+i-1+2)-total_removed << endl;
            // only uniques
        }
        sort(to_remove.rbegin(), to_remove.rend());
        
        for (int remove_index : to_remove) {
            all_begin_ends.erase(all_begin_ends.begin() + remove_index);
        }
        // cout << "removed " << to_remove.size() << endl;
        total_removed += to_remove.size();

        // cout << endl;

        // cout << "all_begin_ends after removing\n";
        // for (DPelement dp_elt : all_begin_ends) {
        //     // cout << "elt\n";
        //     for (tuple<int,int> begin_end : dp_elt) {
        //         cout << "(" << get<0>(begin_end) << ", " << get<1>(begin_end) << "), ";
        //     }
        //     cout << endl;
        // }
        

    }

    return max_score;
}

int main() {

    string s;
    cin >> s;

    // vector<int> ends = find_ends(s, "ab");
    // for (int end : ends) {
        // cout << end << ", ";
    // }
    // cout << endl;
    // cout << getScore(3, 2, 6) << endl;
    int score = makeDP(s);
    cout << score << endl;




    return 0;
}