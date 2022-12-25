|View/Feature|Status|For Reference|
|:-:|:-:|:-:|
|`adjacent`|:red_circle:|
|`adjacent_transform`|:red_circle:|
|`cartesian_product`|:red_circle: |Issue: https://github.com/microsoft/STL/issues/2923|
|`chunk`|:green_circle:| PR: https://github.com/microsoft/STL/pull/2685|
|`chunk_by`|:green_circle:| PR: https://github.com/microsoft/STL/pull/2565
|`join_with`|:green_circle: | PR: https://github.com/microsoft/STL/pull/2619|
|`repeat`|:orange_circle: |PR: https://github.com/microsoft/STL/pull/3142|
|`slide`|:green_circle:| PR: https://github.com/microsoft/STL/pull/2670 |
|`stride`|:green_circle: | PR: https://github.com/microsoft/STL/pull/2981|
|`zip`|:yellow_circle: | PR: https://github.com/microsoft/STL/pull/3035|
|`zip_transform`|:red_circle:| 
|`ranges::to`|:red_circle:|
|Formatting|:red_circle:|

* 🔴 - Not Done
* 🟠 - Started
* 🟡 - Done but not available on Godbolt yet
* 🟢 - Done

Godbolt: https://godbolt.org/z/4fE8GvshY

```cpp
#include <iostream>
#include <ranges>
#include <vector>

using namespace std::views;

auto print2(auto rng) {
    for (auto r : rng) {
        for (auto e : r)
            std::cout << e << ' ';
        std::cout << '\n';
    }
}

auto print(auto rng) {
    for (auto e : rng)
        std::cout << e << ' ';
    std::cout << '\n';
}

auto main() -> int {
    auto const vec = std::vector{0, 0, 1, 1, 2, 2};

    print2(iota(0, 5) | chunk(2));            // [[0,1  ], [2,3  ],[5    ]]
    print2(vec | chunk_by(std::equal_to{}));  // [[0,0  ], [1,1  ],[2,2  ]]
    print2(iota(0, 5) | slide(3));            // [[0,1,2], [1,2,3],[3,4,5]]
    print (iota(0, 10) | stride(3));          // [0, 3, 6, 9]

    return 0;
}


```
