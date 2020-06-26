#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <ranges>

namespace ra = std::ranges;
namespace rv = ra::views;

auto print(auto t) {
    for (auto e : t)
        std::cout << e << ' ';
    std::cout << '\n';
}

int main() {

    std::vector v = { 4, 2, 3 };
    
    {
        auto n = std::accumulate(v.cbegin(), v.cend(), 0);
        std::vector ans(n, 0);
        std::for_each(v.cbegin(), v.cend(), 
            [&, start = ans.begin()](auto val) mutable {
                std::iota(start, start + val, 1);
                start += val;
            });

        print(ans);
    }

    {
        std::vector<int> ans;
        std::for_each(v.cbegin(), v.cend(), 
            [&](auto val) {
                std::vector temp(val, 0);
                std::iota(temp.begin(), temp.end(), 1);
                ans.insert(ans.end(), temp.begin(), temp.end());
            });

        print(ans);
    }

    {
        auto n = std::accumulate(v.cbegin(), v.cend(), 0);
        std::vector ans(n, 1);
        std::for_each(v.cbegin(), v.cend() - 1, 
            [&, pos = 0](auto val) mutable {
                pos += val;
                ans[pos] -= val;
            });
        std::partial_sum(ans.begin(), ans.end(), ans.begin());

        print(ans);
    }

    {
        auto ans = v 
            | rv::transform([](auto val) { return rv::iota(1, val + 1); })
            | rv::join;
            
        print(ans);
    }

    return 0;
}
