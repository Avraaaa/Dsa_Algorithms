#include <iostream>
#include <vector>
#include <climits>

using namespace std;
#define ll long long
const ll INF = 1e18;
void findMaxSumInterval(const vector<int>& arr, int &maxSum, int &startIdx, int &endIdx) {
    maxSum = INT_MIN;
    int currentMax = 0;
    int s = 0;

    startIdx = -1;
    endIdx = -1;

    for (int i = 0; i < arr.size(); i++) {
        currentMax += arr[i];

        if (currentMax > maxSum) {
            maxSum = currentMax;
            startIdx = s;
            endIdx = i;
        }

        if (currentMax < 0) {
            currentMax = 0;
            s = i + 1;
        }
    }
}
/*
ll kadane(vector<ll>& arr) {
    ll max_sum = -INF; // Start with the lowest possible value
    ll current_sum = 0;

    for (ll i = 0; i < arr.size(); i++) {
        current_sum += arr[i];

        // Update the maximum found so far
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }

        // If the current streak becomes negative, it's dead weight.
        // Reset it to 0 so the next number starts a fresh subarray.
        if (current_sum < 0) {
            current_sum = 0;
        }
    }

    return max_sum;
}*/
/*
vector<ll> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    
cout << "The Maximum Subarray Sum is: " << kadane(arr) << endl;
*/

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxSum, startIdx, endIdx;
    findMaxSumInterval(arr, maxSum, startIdx, endIdx);

    cout << "Maximum Sum: " << maxSum << endl;
    cout << "Interval: [" << startIdx << ", " << endIdx << "]" << endl;
    cout << "Subarray: ";
    for (int i = startIdx; i <= endIdx; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
