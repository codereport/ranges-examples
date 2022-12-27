### Status

|View/Feature|GCC|MSVC|For Reference|
|:-:|:-:|:-:|:-:|
|`adjacent`||:red_circle:|
|`adjacent_transform`||:red_circle:|
|`cartesian_product`||:red_circle: |Issue: https://github.com/microsoft/STL/issues/2923|
|`chunk`|:green_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2685|
|`chunk_by`|:green_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2565
|`join_with`||:green_circle: | PR: https://github.com/microsoft/STL/pull/2619|
|`pairwise`|:green_circle:|:red_circle:
|`pairwise_transform`|:green_circle:|:red_circle:
|`repeat`|:green_circle:|:orange_circle: |PR: https://github.com/microsoft/STL/pull/3142|
|`slide`|:green_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2670 |
|`stride`|:green_circle:|:green_circle: | PR: https://github.com/microsoft/STL/pull/2981|
|`zip`|:green_circle:|:yellow_circle: | PR: https://github.com/microsoft/STL/pull/3035|
|`zip_transform`|:green_circle:|:red_circle:| 
|`ranges::to`||:red_circle:|
|Formatting||:red_circle:|

* 🔴 - Not Done
* 🟠 - Started
* 🟡 - Done but not available on Godbolt yet
* 🟢 - Done

### Godbolt Links
* MSVC Godbolt: https://godbolt.org/z/6oj3d5TnK
* GCC  Godbolt: https://godbolt.org/z/d8evxK49T

```cpp
#include <array>
#include <ranges>

#include <fmt/ranges.h>

using namespace std::views;

auto main() -> int {
    auto vec = std::array{0, 0, 1, 1, 2, 2};

    fmt::print("{}\n", iota(0, 5) | chunk(2));                          // [[0, 1], [2, 3], [4]]
    fmt::print("{}\n", vec | chunk_by(std::equal_to{}));                // [[0, 0], [1, 1], [2, 2]]
    fmt::print("{}\n", iota(0, 5) | slide(3));                          // [[0, 1, 2], [1, 2, 3], [2, 3, 4]]
    fmt::print("{}\n", iota(0, 10) | stride(3));                        // [0, 3, 6, 9]
    fmt::print("{}\n", repeat(42) | take(5));                           // [42, 42, 42, 42, 42]
    fmt::print("{}\n", zip_transform(std::plus{}, vec, vec));           // [0, 0, 2, 2, 4, 4]
    fmt::print("{}\n", zip(iota(0, 3), iota(1, 4)));                    // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", adjacent<2>(iota(0, 4)));                        // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", pairwise(iota(0, 4)));                           // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", adjacent_transform<2>(iota(0, 4), std::plus{})); // [1, 3, 5]
    fmt::print("{}\n", pairwise_transform(iota(0, 4), std::plus{}));    // [1, 3, 5]

    return 0;
}
```
