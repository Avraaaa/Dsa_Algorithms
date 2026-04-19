#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Computes the Longest Prefix Suffix (LPS) array for the given pattern
vector<ll> computelps(string &pattern){
    ll patternsize = pattern.size();
    vector<ll> lps(patternsize);

    ll len = 0; 
    lps[0] = 0; 

    ll i = 1;

    while(i < patternsize){
        if(pattern[i] == pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                len = lps[len - 1]; // Fallback to previous longest prefix
            }
            else{
                // Characters don't match, and no previous match exists
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// Finds all occurrences of the pattern in the text using KMP
vector<ll> kmp_search(string &text, string &pattern){
    vector<ll> occurrences;
    ll n = text.size();
    ll m = pattern.size();

    if(m == 0) return occurrences;

    vector<ll> lps = computelps(pattern);

    ll i = 0; // Text index
    ll j = 0; // Pattern index

    while(i < n){
        if(pattern[j] == text[i]){
            i++;
            j++;
        }

        if(j == m){
            occurrences.push_back(i - j); 
            j = lps[j - 1]; // Fallback to check for overlapping matches
        }
        else if(i < n && pattern[j] != text[i]){
            if(j != 0){
                j = lps[j - 1];
            }
            else{
                i++; 
            }
        }
    }

    return occurrences;
}

int main(){
    string text, pattern;
    cin >> text >> pattern;

    vector<ll> match_indices = kmp_search(text, pattern);

    if(match_indices.empty()){
        cout << "Pattern not found." << endl;
    } else {
        cout << "Pattern found at indices: ";
        for(ll idx : match_indices){
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}