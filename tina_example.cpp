// https://godbolt.org/z/r7oros541

#include <algorithm>
#include <ranges>
#include <vector>
#include <https://raw.githubusercontent.com/codereport/blackbird/main/combinators.hpp>

#include <fmt/ranges.h>

using namespace std::views;
using namespace combinators;

// Tina's Code
auto random_23_1(const std::vector<double>& rng) {
    return std::views::cartesian_product(
        rng,
        std::views::iota(1, 3),
        rng | std::views::transform([](const auto e) { return e * e + 2; }))
        | std::views::transform([](const auto t) {
            const auto& [a, b, c] = t;
            return a * b + 2 * c;
        }); 
}

// Remove namespace
auto random_23_1_ns(const std::vector<double>& rng) {
    return cartesian_product(
        rng,
        iota(1, 3),
        rng | transform([](const auto e) { return e * e + 2; }))
        | transform([](const auto t) {
            const auto& [a, b, c] = t;
            return a * b + 2 * c;
        }); 
}

// Circle Code
auto random_23_1_circle(const std::vector<double>& rng) {
    auto op1 = [](const auto e) { return e * e + 2; };
    auto op2 = [](const auto t) {
            const auto& [a, b, c] = t;
            return a * b + 2 * c;
    };
    return rng 
        |> cartesian_product($, iota(1, 3), transform($, op1))
        |> transform($, op2); 
}

// Circle Code with Blackbird
auto random_23_1_circle_bb(const std::vector<double>& rng) {
    auto op1 = _b(_plus(2), _w(_mul_));
    auto op2 = [](const auto t) {
            const auto& [a, b, c] = t;
            return a * b + 2 * c;
    };
    return rng 
        |> cartesian_product($, iota(1, 3), transform($, op1))
        |> transform($, op2); 
}

// Circle Code with Blackbird & SB w/ Lambda
// auto random_23_1_circle_bb(const std::vector<double>& rng) {
//     return rng 
//         |> cartesian_product($, iota(1, 3), transform($, _b(_plus(2), _w(_mul_))))
//         |> transform($, [](const auto& [a, b, c]) { return a * b + 2 * c; }); 
// }

auto main() -> int {

    auto const vec = std::vector{1., 2.};

  fmt::print("{}\n", random_23_1(vec));
  fmt::print("{}\n", random_23_1_ns(vec));
  fmt::print("{}\n", random_23_1_circle(vec));
  fmt::print("{}\n", random_23_1_circle_bb(vec));
  
  return 0;
}
