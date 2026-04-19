#include <bits/stdc++.h>

using namespace std;

#define ll int

// topdown

ll cutrod(ll i, vector<ll> &w, vector<ll> &dparr)
{

    ll ans = 0;
    if (i == 0)
        return 0;
    if (dparr[i]!= -1)
        return dparr[i];
    else
    {
        for (ll j = 1; j <= i; j++)
        {
            ans = max(ans, w[j - 1] + cutrod(i-j,w,dparr));
        }
    }
    return dparr[i ] = ans;
}

//bottom-up

ll cutrodbu(ll n,vector <ll> &w){

    vector<int> dp(w.size()+1, 0);


    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){

            dp[i] = max(dp[i],w[j-1]+dp[i-j]);

        }

    }
    return dp[n];

}

void solve()
{

    ll n;
    vector<ll> w = {1, 5, 8, 9, 10, 17, 17, 20};
    n = w.size();
    vector<ll> dparr(w.size()+1, -1);
    ll ans = cutrod(n, w, dparr);
    cout << ans << endl;
     ans = cutrodbu(n,w);
    cout<<ans<<endl;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    while (t--)
    {

        solve();
    }
}