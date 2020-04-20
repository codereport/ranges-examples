// https://godbolt.org/z/hyknk6
// Take from Eric Niebler's calendar example: 
// https://ericniebler.github.io/range-v3/md___users_eniebler__code_range-v3_doc_examples.html#example-views

#include <algorithm> // std::mismatch
#include <iostream>
#include <vector>
#include <range/v3/algorithm/mismatch.hpp>
#include <range/v3/core.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/for_each.hpp>

using namespace ranges;

template<class Rngs>
class interleave_view : public view_facade<interleave_view<Rngs>> {
    friend range_access;
    std::vector<range_value_t<Rngs>> rngs_;
    struct cursor;
    cursor begin_cursor() {
        return {0, &rngs_, views::transform(rngs_, ranges::begin) | to<std::vector>};
    }
public:
    interleave_view() = default;
    explicit interleave_view(Rngs rngs)
      : rngs_(std::move(rngs) | to<std::vector>)
    {}
};

template<class Rngs>
struct interleave_view<Rngs>::cursor {
    std::size_t n_;
    std::vector<range_value_t<Rngs>> *rngs_;
    std::vector<iterator_t<range_value_t<Rngs>>> its_;
    decltype(auto) read() const {
        return *its_[n_];
    }
    void next() {
        if(0 == ((++n_) %= its_.size()))
            for_each(its_, [](auto &it) { ++it; });
    }
    bool equal(default_sentinel_t) const {
        if(n_ != 0) return false;
        auto ends = *rngs_ | views::transform(ranges::end);
        return its_.end() != std::mismatch(
            its_.begin(), its_.end(), ends.begin(), std::not_equal_to<>{}).first;
    }
    auto equal(cursor const& that) const -> CPP_ret(bool)(
        requires forward_range<range_value_t<Rngs>>) {
        return n_ == that.n_ && its_ == that.its_;
    }
};

auto interleave() {
    return make_view_closure([](auto &&rngs) {
        using Rngs = decltype(rngs);
        return interleave_view<views::all_t<Rngs>>(
            views::all(std::forward<Rngs>(rngs)));
    });
}

auto transpose() {
    return make_view_closure([](auto &&rngs) {
        using Rngs = decltype(rngs);
        return std::forward<Rngs>(rngs)
            | interleave()
            | views::chunk(static_cast<std::size_t>(distance(rngs)));
    });
}
