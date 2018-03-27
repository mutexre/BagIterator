//
//  true_random_access_iterator.hpp
//  Random Access Iterator
//
//  Created by Alexander Obuschenko on 27/03/2018.
//

#pragma once

#include <iterator>
#include <random>

template <class Container, class RandomEngine>
class true_random_access_iterator: public std::iterator<std::forward_iterator_tag,
                                                        typename Container::value_type>
{
    Container& container;
    RandomEngine rnd;
    
    using BaseIter = decltype(std::begin(container));
    using BaseIterTraits = std::iterator_traits<BaseIter>;
    using BaseIterRef = typename BaseIterTraits::reference;
    using BaseIterCategory = typename BaseIterTraits::iterator_category;
    using BaseIterDiff = typename BaseIterTraits::difference_type;
    
    BaseIter current;
    
    long long i = 0;
    
public:
    template <class Cont, class RND>
    explicit true_random_access_iterator(Cont& c, RND&& rnd) :
        container(c)
    {
        this->rnd = std::forward<RandomEngine>(rnd);
        current = std::begin(container);
        next();
    }

    BaseIterRef operator*() const {
        return *current;
    }
    
    true_random_access_iterator<Container, RandomEngine>&
    operator++() {
        next();
        return *this;
    };
    
    true_random_access_iterator<Container, RandomEngine>&
    operator++(int) {
        auto tmp = *this;
        next();
        return tmp;
    };
    
    BaseIter base() const {
        return current;
    }
    
    bool operator!=(const true_random_access_iterator<Container, RandomEngine>& other) {
        return i != other.i;
    }
    
    true_random_access_iterator<Container, RandomEngine>
    take(BaseIterDiff dist) {
        auto tmp = *this;
        tmp.i += dist;
        return tmp;
    }

private:
    void next()
    {
        auto begin = std::begin(container);
        auto end = std::end(container);
        
        current = begin;
        i++;
        
        if (begin != end)
        {
            auto size = std::distance(begin, end);
            auto i = rnd() % size;
            std::advance(current, i);
        }
    }
};

template <class Container, class RandomEngine>
true_random_access_iterator<std::remove_reference_t<Container>,
                            std::remove_reference_t<RandomEngine>>
make_dice_iterator(Container& cont, RandomEngine&& rnd)
{
    return true_random_access_iterator<std::remove_reference_t<Container>,
                                       std::remove_reference_t<RandomEngine>>(cont, std::forward<RandomEngine>(rnd));
}
