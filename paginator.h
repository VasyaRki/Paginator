#ifndef PAGINATOR_H
#define PAGINATOR_H

#include <vector>
#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>


template <typename Iterator >
class IteratorRange {
private:
    Iterator first, last;
public:
    IteratorRange(Iterator f, Iterator l)
        : first(f)
        , last(l)
    {}
    Iterator begin() const {
        return first;
    }
    Iterator end() const {
        return last;
    }
    Iterator begin() {
        return first;
    }
    Iterator end() {
        return last;
    }
    size_t size() const {
        return last - first;
    }
};

template <typename Iterator>
class Paginator {
private:
    std::vector<IteratorRange<Iterator>> pages;
public:
    Paginator(Iterator _begin, Iterator _end, size_t _page_size)
    {
        Iterator it = _begin;
        while (it != _end) {
            size_t DistanceToEnd = _end - it;
            pages.push_back({ it, next(it, std::min(_page_size, DistanceToEnd)) });
            it = next(it, std::min(_page_size, DistanceToEnd));
        }
    }
    auto begin() const {
        return pages.begin();
    }
    auto end() const {
        return pages.end();
    }
    auto begin() {
        return pages.begin();
    }
    auto end() {
        return pages.end();
    }
    size_t size() const { return pages.size(); }
};


// A template function that returns an object that can be iterated over.
template <typename Container>
auto Paginate(Container& c, size_t page_size) {
    return Paginator { c.begin(), c.end(), page_size };
}

#endif