#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MAX_CHARS = 256;

// Calculates the next state for the DFA
ll get_next_state(const string& pattern, ll m, ll state, ll x) {
    // If the character matches, simply advance the state
    if (state < m && x == pattern[state]) {
        return state + 1;
    }

    // Otherwise, find the longest prefix which is also a suffix
    for (ll ns = state; ns > 0; ns--) {
        if (pattern[ns - 1] == x) {
            ll i;
            for (i = 0; i < ns - 1; i++) {
                if (pattern[i] != pattern[state - ns + 1 + i]) {
                    break;
                }
            }
            if (i == ns - 1) {
                return ns;
            }
        }
    }

    return 0;
}

// Builds the Transition Function (DFA table)
void build_dfa(const string& pattern, ll m, vector<vector<ll>>& TF) {
    for (ll state = 0; state <= m; state++) {
        for (ll x = 0; x < MAX_CHARS; x++) {
            TF[state][x] = get_next_state(pattern, m, state, x);
        }
    }
}

// Searches for the pattern using the Finite Automaton
vector<ll> finite_automaton_search(const string& text, const string& pattern) {
    vector<ll> occurrences;
    ll n = text.length();
    ll m = pattern.length();

    if (m == 0 || m > n) return occurrences;

    // TF table: (m + 1) states, each having MAX_CHARS transitions
    vector<vector<ll>> TF(m + 1, vector<ll>(MAX_CHARS, 0));

    build_dfa(pattern, m, TF);

    ll state = 0;
    
    for (ll i = 0; i < n; i++) {
        state = TF[state][(unsigned char)text[i]];

        // If we reached the final state, a full match is found
        if (state == m) {
            occurrences.push_back(i - m + 1);
        }
    }

    return occurrences;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text, pattern;
    cin >> text >> pattern;

    vector<ll> match_indices = finite_automaton_search(text, pattern);

    if (match_indices.empty()) {
        cout << "No match found\n";
    } else {
        cout << "Matching positions: ";
        for (ll idx : match_indices) {
            cout << idx << " ";
        }
        cout << "\n";
    }

    return 0;
}