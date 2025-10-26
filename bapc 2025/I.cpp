#include <iostream>
#include <string>
#include <vector>
#include <tuple>

int main() [
    int n, w;
    std::cin >> n;
    std::cin >> w;

    std::vector<std::tuple<int,int>> WM;
    int p, t;
    for (int i = 0; i < n; i++) {
        std::cin >> p;
        std::cin >> t;
        WM.pushback({p,t})

    }
    cout << WM << endl;

    return 0;
]