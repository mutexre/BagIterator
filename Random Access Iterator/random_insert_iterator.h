//
//  random_inserter.h
//  Random Access Iterator
//
//  Created by Alexander Obuschenko on 27/03/2018.
//

#pragma once

#include <iterator>
#include <random>

template <class Container, class RandomEngine>
class random_insert_iterator
{
    Container& container;
    RandomEngine rnd;
    
    using BaseIter = decltype(std::begin(container));
    using BaseIterTraits = std::iterator_traits<BaseIter>;
    using BaseIterValue = typename BaseIterTraits::value_type;
    using BaseIterRef = typename BaseIterTraits::reference;
    using BaseIterCategory = typename BaseIterTraits::iterator_category;
    using BaseIterDiff = typename BaseIterTraits::difference_type;
    
    BaseIter current;
    
    long long i = 0;
    
public:
    template <class Cont, class RND>
    explicit random_insert_iterator(Cont& c, RND&& rnd) :
        container(c)
    {
        this->rnd = std::forward<RND>(rnd);
        next();
    }
    
    random_insert_iterator<Container, RandomEngine>&
    operator=(const BaseIterValue& value)
    {
        container.insert(current, value);
        next();
        return *this;
    }
    
    random_insert_iterator<Container, RandomEngine>&
    operator*() {
        return *this;
    }
    
    random_insert_iterator<Container, RandomEngine>&
    operator++() {
        return *this;
    };
    
    random_insert_iterator<Container, RandomEngine>&
    operator++(int) {
        return *this;
    };
    
    BaseIter base() const {
        return current;
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
random_insert_iterator<std::remove_reference_t<Container>,
                       std::remove_reference_t<RandomEngine>>
random_inserter(Container& cont, RandomEngine&& rnd)
{
    return random_insert_iterator<std::remove_reference_t<Container>,
                                  std::remove_reference_t<RandomEngine>>(cont, rnd);
}
