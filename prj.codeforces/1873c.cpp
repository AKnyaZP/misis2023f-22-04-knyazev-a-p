#include <iostream>
#include <vector>
// https://codeforces.com/problemset/problem/1873/C

int main(){
    std::vector<std::vector<int>> target(10, std::vector<int>(10, 0));
    char a;
    int t;

    std::cin >> t;

    while (t > 0){
        int sum = 0;
        for (int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j){
                std::cin >> a;
                if (a == 'X' and (i == 0 or j == 0 or j == 9 or i == 9))
                    sum ++;
                if (a == 'X' and (((i == 1 or i == 8) and (1 <= j and j <= 8)) or ((j == 1 or j == 8) and (1 <= i and i <= 8))))
                    sum += 2;
                if (a == 'X' and (((i == 2 or i == 7) and (2 <= j and j <= 7)) or ((j == 2 or j == 7) and (2 <= i and i <= 7)))) 
                    sum += 3;
                if (a == 'X' and (((i == 3 or i == 6) and (3 <= j and j <= 6)) or ((j == 3 or j == 6) and (3 <= i and i <= 6))))
                    sum += 4;
                if (a == 'X' and (((i == 4 or i == 5) and (4 <= j and j <= 5)) or ((j == 4 or j == 5) and (4 <= i and i <= 5))))
                    sum += 5;
            };
        };
        std::cout << sum << '\n';
        t--;
    }
    return 0;
}
