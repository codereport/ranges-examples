|View|Status|
|:-:|:-:|
|`adjacent`|:red_circle:|
|`adjacent_transform`|:red_circle:|
|`cartesian_product`|:red_circle: Issue: https://github.com/microsoft/STL/issues/2923|
|`chunk`|:green_circle:|
|`chunk_by`|:green_circle:|
|`join_with`|:yellow_circle: PR: https://github.com/microsoft/STL/pull/2619|
|`repeat`|:red_circle: Issue: https://github.com/microsoft/STL/issues/2933|
|`slide`|:green_circle:|
|`stride`|:yellow_circle: PR https://github.com/microsoft/STL/pull/2981|
|`zip`|:red_circle: PR: https://github.com/microsoft/STL/pull/3035|
|`zip_transform`|:red_circle:| 

```cpp

#include <iostream>.
#include <vector>
#include <ranges>
// #include <string>

// using namespace std::string_literals;
using namespace std::views;

auto chunk_example() {
	for (auto c : iota(0, 5) | chunk(2)) {
		for (auto i : c) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}

auto chunk_by_example() {
	auto const vec = std::vector{ 0, 0, 1, 1, 2, 2 };
	for (auto c : vec | chunk_by(std::equal_to{})) {
		for (auto i : c) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}

auto slide_example() {
	for (auto c : iota(0, 5) | slide(3)) {
		for (auto i : c) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
}

//auto zip_example() {
//	for (auto [x, y] : zip(iota(0, 5), iota(10, 15)) {
//		std::cout << x << ',' << y << '\n';
//	}
//}

auto main() -> int {

	chunk_example();    // [[0,1],[2,3],[5]]
	chunk_by_example(); // [[0,0],[1,1],[2,2]]
	slide_example();    // [[0,1,2],[1,2,3],[3,4,5]]
	//zip_example();

	return 0;
}

```
