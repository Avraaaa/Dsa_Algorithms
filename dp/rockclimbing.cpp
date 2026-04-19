#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n = 4;
int m = 5;
int arr[4][5];
int dp[4][5];
vector <ll> printto;

int dynamic(int i,int j){
    if(j<0||j>=m){
        return 100000000;
    }
    if(i==n-1){
        return arr[i][j];
    }
    if(dp[i][j]!=-1){
        return dp[i][j];
    }

    int t = 100000000;
    t = min(t,dynamic(i+1,j-1));    
    t = min(t,dynamic(i+1,j+1));
    t = min(t,dynamic(i+1,j));
    return dp[i][j] = t+arr[i][j];

}


void printBest(int i,int j){

    printto.push_back(arr[i][j]);
    if(i==n-1){
        return;
    }
    
    int t =dp[i][j]-arr[i][j]; 
    if(j-1>=0 && dp[i+1][j-1]==t){
        printBest(i+1,j-1);
    }
    else if(j+1<m && dp[i+1][j+1]==t){
        printBest(i+1,j+1);
    }
    else{
        printBest(i+1,j);
    }

}


void solve(){

    for(int i =0;i<n;i++){
        for(int j = 0;j<m;j++){
            cin>>arr[i][j];
            dp[i][j] = -1;
        }
    }
    int result = 100000000;
    for(int i=0;i<m;i++){
        result = min(result,dynamic(0,i));
    }
    ll p = -1;
    cout<<result<<endl;
    for(int i=0;i<m;i++){
        if(dp[0][i] == result){
            p = i;
            break;
        }
    }
    for(int i =0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"path attmept print\n";
    printBest(0,p);

    for(int i =printto.size()-1;i>=0;i--){
        cout<<printto[i]<<endl;
    }

    
}

int main()
{



    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t = 1;
    while (t--)
    {
        solve();
    }
}