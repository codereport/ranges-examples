// Godbolt: https://godbolt.org/z/8aTM5P4TK

#include <algorithm>
#include <ranges>

#include <fmt/ranges.h>

auto main() -> int 
{
    auto const nums = std::array{0, 1, 2, 3};

    auto add1 = [](auto e) { return e + 1; };

    auto out  = std::array<int, 4>{};
    auto out2 = std::array<int, 4>{};

    std::transform(nums.begin(), nums.end(), out.begin(), add1); // C++ 98
    std::ranges::transform(nums, out2.begin(), add1);            // C++ 20
    auto const out3 = nums | std::views::transform(add1);        // C++ 20 (Ranges)

    fmt::print("{}\n", out);
    fmt::print("{}\n", out2);
    fmt::print("{}\n", out3);

    return 0;
}
