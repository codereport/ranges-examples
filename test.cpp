// godbolt link: https://godbolt.org/z/-8y2K2

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <range/v3/action/join.hpp>
#include <range/v3/view/intersperse.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

namespace rv = ranges::views;
namespace ra = ranges::actions;

namespace hs {
    template <typename T, typename BinOp>
    auto reduce(T init, BinOp binOp) {
        return ranges::make_pipeable([&](auto&& rng) {
            return std::accumulate(
                ranges::begin(rng), 
                ranges::end(rng), 
                init, 
                binOp);
        });
    }
}

int main () {
    
    auto const v = rv::iota(1, 11) 
        | ranges::to<std::vector<int>>;

    auto const iota10 = v 
        | rv::transform([](auto const& e) { return std::to_string(e); })
        | rv::intersperse(" ")
        | ra::join
        | ranges::to<std::string>;

    auto const sumIota10 = v 
        | hs::reduce(0, std::plus{});

    std::cout << iota10    << '\n';
    std::cout << sumIota10 << '\n';

    return 0;
}
