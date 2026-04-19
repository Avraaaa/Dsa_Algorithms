#include <bits/stdc++.h>
using namespace std;

#define ll long long

void naive_search(const string& text, const string& pattern) {
    ll n = text.length();
    ll m = pattern.length();
    bool found = false;

    if (m > n || m == 0) {
        cout << "No match found\n";
        return;
    }

    vector<ll> occurrences;

    for (ll i = 0; i <= n - m; i++) {
        ll j;

        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break; 
            }
        }

        if (j == m) {
            occurrences.push_back(i);
            found = true;
        }
    }

    if (!found) {
        cout << "No match found\n";
    } else {
        cout << "Matching positions: ";
        for (ll idx : occurrences) {
            cout << idx << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text, pattern;
    cin >> text >> pattern;

    naive_search(text, pattern);

    return 0;
}