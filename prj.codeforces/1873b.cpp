#include <iostream>
#include <vector>
#include <algorithm>

// https://codeforces.com/problemset/problem/1873/B

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }

        int minIndex = std::min_element(arr.begin(), arr.end()) - arr.begin();

        arr[minIndex]++;

        long long result = 1;
        for (int i = 0; i < n; i++) {
            result *= arr[i];
        }

        std::cout << result << std::endl;
    }

    return 0;
}

