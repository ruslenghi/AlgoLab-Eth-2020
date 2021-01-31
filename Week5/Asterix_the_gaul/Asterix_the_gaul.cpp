//DISCLAIMER:: I FOUND THIS SOLUTION ONLINE, I DID NOT WRITE IT

#include <iostream>
#include <vector>
#include<cmath>
#include <utility>
#include <cassert>
#include <algorithm>

using namespace std;

//This one is here to order the pairs, no big deal
//This sorts the pair in order of time, that is pairs with a smaller time come frist
//if two pairs have equal time lengths the one with the longer distance is put first 
bool compare(pair<long, long> p1, pair<long, long> p2) {
    if (p1.first < p2.first) {
        return true;
    } else if (p1.first == p2.first) {
        return p1.second > p2.second;
    } else {
        return false;
    }
}

//Now, what follows is the hard part! This is a function that tells us efficiently
//if, with a given increment, Asterix can warn panoramix in time. Notice that the function
//does not take the moves in input by reference, but it copies them, as it needs to reorder them each time

// based on split
bool suffice(long D, long T, vector<pair<long, long> > M, long increment) {

    // random_shuffle(M.begin(), M.end());
    vector<pair<long, long> > S1, S2;
    int count = 0;
    for (auto move : M) {
        move.second += increment;
        if (count < M.size() / 2) {
            S1.push_back(move);
        } else {
            S2.push_back(move);
        }
        count++;
    }

//Luckily lines 40 to 63 are the same, twice

    vector<pair<long, long> > sum1, sum2;
    int n1 = S1.size();
    int n2 = S2.size();
    // 1 << n1 should just be 2^n1 I believe...
    for (int i = 0; i < 1 << n1; i++) {
        long t_total = 0, d_total = 0;
        for (int j = 0; j < n1; j++) {
            //The following if is a check to see if the i-th bit of j is turned off
            if (i & 1 << j) {
                t_total += S1[j].first;
                d_total += S1[j].second;
            }
        }
        sum1.push_back(make_pair(t_total, d_total));
    }

    for (int i = 0; i < 1 << n2; i++) {
        long t_total = 0, d_total = 0;
        for (int j = 0; j < n2; j++) {
            if (i & 1 << j) {
                t_total += S2[j].first;
                d_total += S2[j].second;
            }
        }
        sum2.push_back(make_pair(t_total, d_total));
    }
    
    //Again, as above, lines 69 to 87 are the same

    sort(sum1.begin(), sum1.end(), compare);
    long max_d = 0;
    for (auto &s : sum1) {
        if (s.second > max_d) {
            max_d = s.second;
        } else {
            s.second = max_d;
        }
    }

    sort(sum2.begin(), sum2.end(), compare);
    max_d = 0;
    for (auto &s : sum2) {
        if (s.second > max_d) {
            max_d = s.second;
        } else {
            s.second = max_d;
        }
    }
    
    //This is new though
    int p1 = 0, p2 = sum2.size() - 1;
    while(p1 < sum1.size() && p2 >= 0) {
        if (sum1[p1].first + sum2[p2].first < T) { 
            if (sum1[p1].second + sum2[p2].second >= D) {
                return true;
            }
            p1++;
        } else {
            p2--;
        }
    }
    return false;
}

//Here everything is straightforward, we basically only do binary search 
//given that we can use the suffice function
void testcase() {
    int n, m;
    long D, T;
    cin >> n >> m >> D >> T;
    vector<pair<long, long> > M;
    for (int i = 0; i < n; i++) {
        long d, t;
        cin >> d >> t;
        M.push_back(make_pair(t, d));
    }
    vector<long> s;
    s.push_back(0);
    for (int i = 0; i < m; i++) {
        long increment; cin >> increment;
        s.push_back(increment);
    }

    if (suffice(D, T, M, 0)) {
        cout << 0 << endl;
        return;
    } else if (!suffice(D, T, M, s.back())) {
        cout << "Panoramix captured" << endl;
        return;
    }

    int l = 0, r = m;
    while(l < r) {
        int mid = (l + r) / 2;
        if (!suffice(D, T, M, s[mid])) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    assert (l == r);
    cout << l << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        testcase();
    }
}
