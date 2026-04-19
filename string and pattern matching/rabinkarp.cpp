#include <bits/stdc++.h>

using namespace std;

#define ll long long

// BASE is 256 to represent the total ASCII characters available
const ll BASE = 256;

const ll PRIME = 1e9 + 7;

vector<ll> rabin_karp(const string &text, const string &pattern)
{

    vector<ll> occurrences;
    ll n = text.length();
    ll m = pattern.length();

    if (m > n || m == 0)
        return occurrences;

    ll pattern_hash = 0;
    ll window_hash = 0;
    ll leftmost_multiplier = 1;

    //------------------- Pre-compute BASE^(M-1) % PRIME -----------------------------
    for (ll i = 0; i < m - 1; i++)
    {

        leftmost_multiplier = (leftmost_multiplier * BASE) % PRIME;
    }

    // Calculating initial hash values

    for (ll i = 0; i < m; i++)
    {

        pattern_hash = (pattern_hash * BASE + pattern[i]) % PRIME;
        window_hash = (window_hash * BASE + text[i]) % PRIME;
    }

    // Sliding the window

    for (ll i = 0; i < n - m; i++)
    {

        if (pattern_hash == window_hash)
        {
            bool match = true;
            for (ll j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                occurrences.push_back(i);
            }
        }

        // 3. Roll the Hash Forward Safely
        if (i <= n - m)
        {
            // STEP A: Calculate the value of the character leaving the window
            ll char_to_remove = (text[i] * leftmost_multiplier) % PRIME;
            // STEP B: Subtract it safely.
            // We add PRIME before taking the modulo to guarantee the result is strictly positive!
            window_hash = (window_hash - char_to_remove + PRIME) % PRIME;
            // STEP C: Shift left (multiply by BASE) and add the new character
            window_hash = (window_hash * BASE + text[i + m]) % PRIME;
        }
    }
    return occurrences;
}

int main()
{
    string text;
    string pattern;
    cin >> text;
    cin >> pattern;

    vector<ll> match_indices = rabin_karp(text, pattern);
    if (match_indices.empty())
    {
        cout << "Pattern not found." << endl;
    }
    else
    {
        cout << "Pattern found at indices: ";
        for (ll idx : match_indices)
        {
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
Input: 
AABAACAADAABAABA
AABA
*/