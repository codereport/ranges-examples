### Status

|View/Feature|GCC|Clang|MSVC|MSVC PR|
|:-:|:-:|:-:|:-:|:-:|
|`adjacent`|:green_circle:|:red_circle:|:yellow_circle:| PR: https://github.com/microsoft/STL/pull/3508 |
|`adjacent_transform`|:green_circle:|:red_circle:|:yellow_circle:| PR: https://github.com/microsoft/STL/pull/3546 |
|`cartesian_product`|:green_circle:|:red_circle:|:yellow_circle: |PR: https://github.com/microsoft/STL/pull/3561|
|`chunk`|:green_circle:|:red_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2685|
|`chunk_by`|:green_circle:|:red_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2565
|`enumerate`|:green_circle:|:red_circle:|:yellow_circle:|PR: https://github.com/microsoft/STL/pull/3472|
|`join_with`|:green_circle:|:red_circle:|:green_circle: | PR: https://github.com/microsoft/STL/pull/2619|
|`pairwise`|:green_circle:|:red_circle:|:yellow_circle: | PR: https://github.com/microsoft/STL/pull/3508 |
|`pairwise_transform`|:green_circle:|:red_circle:|:yellow_circle: | PR: https://github.com/microsoft/STL/pull/3546 |
|`repeat`|:green_circle:|:red_circle:|:green_circle: |PR: https://github.com/microsoft/STL/pull/3142|
|`slide`|:green_circle:|:red_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2670 |
|`stride`|:green_circle:|:red_circle:|:green_circle: | PR: https://github.com/microsoft/STL/pull/2981|
|`zip`|:green_circle:|:red_circle:|:green_circle: | PR: https://github.com/microsoft/STL/pull/3035|
|`zip_transform`|:green_circle:|:red_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/3322 |
|`ranges::to`|:red_circle:|:red_circle:|:green_circle:| PR: https://github.com/microsoft/STL/pull/2806 |
|Formatting|:red_circle:|:red_circle:|:red_circle:|

* 🔴 - Not Done
* 🟡 - Started
* 🟢 - Done (and available on Compiler Explorer)

### Godbolt Links
* MSVC Compiler Explorer: https://godbolt.org/z/8b654v3e1
* GCC Compiler Explorer: https://godbolt.org/z/96jG84aeh

```cpp
#include <array>
#include <ranges>
#include <string>

#include <fmt/ranges.h>

using namespace std::views;
using namespace std::string_literals;

auto main() -> int {
    auto const nums    = std::array{0, 0, 1, 1, 2, 2};
    auto const animals = std::array{"cat"s, "dog"s};

    fmt::print("{}\n", iota(0, 5) | chunk(2));                           // [[0, 1], [2, 3], [4]]
    fmt::print("{}\n", nums | chunk_by(std::equal_to{}));                // [[0, 0], [1, 1], [2, 2]]
    fmt::print("{}\n", iota(0, 5) | slide(3));                           // [[0, 1, 2], [1, 2, 3], [2, 3, 4]]
    fmt::print("{}\n", iota(0, 10) | stride(3));                         // [0, 3, 6, 9]
    fmt::print("{}\n", repeat(42) | take(5));                            // [42, 42, 42, 42, 42]
    fmt::print("{}\n", zip_transform(std::plus{}, nums, nums));          // [0, 0, 2, 2, 4, 4]
    fmt::print("{}\n", zip(iota(0, 3), iota(1, 4)));                     // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", iota(0, 4) | adjacent<2>);                        // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", iota(0, 4) | pairwise);                           // [(0, 1), (1, 2), (2, 3)]
    fmt::print("{}\n", iota(0, 4) | adjacent_transform<2>(std::plus{})); // [1, 3, 5]
    fmt::print("{}\n", iota(0, 4) | pairwise_transform(std::plus{}));    // [1, 3, 5]
    fmt::print("{}\n", animals | join_with(','));                        // ['c', 'a', 't', ',', 'd', 'o', 'g']
    fmt::print("{}\n", cartesian_product(iota(0, 2), "AZ"s));            // [(0, 'A'), (0, 'Z'), (1, 'A'), (1, 'Z')]
    fmt::print("{}\n", "APL"s | enumerate);                              // [(0, 'A'), (1, 'P'), (2, 'L')]

    return 0;
}
```
