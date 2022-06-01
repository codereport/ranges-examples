// Godbolt link: https://godbolt.org/z/718oEqKbz

#include <vector>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>

namespace rv = ranges::views;

auto where(auto vec) {
    return rv::zip(vec, rv::iota(1) )
         | rv::filter([](auto const& t) { return std::get<0>(t); })
         | rv::transform([](auto const& t) { return std::get<1>(t); })
         | ranges::to<std::vector>;
}
