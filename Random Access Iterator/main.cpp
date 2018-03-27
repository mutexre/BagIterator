//
//  main.cpp
//  Random Access Iterator
//
//  Created by Alexander Obuschenko on 27/03/2018.
//

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include "true_random_access_iterator.hpp"
#include "random_insert_iterator.h"

using namespace std;

using RandomEngine = std::default_random_engine;
size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
RandomEngine rnd{ static_cast<typename RandomEngine::result_type>(seed) };

template <typename Container>
double getMean(Container& cont, size_t trials)
{
//    true_random_access_iterator<std::remove_reference_t<Container>, RandomEngine> iter(cont, rnd);
    
    auto iter = make_dice_iterator(cont, rnd);
    
    double mean = 0;
    for (int i = 0; i < trials; i++)
    {
        auto x = *iter;
        mean += x;
        iter++;
    }
    mean /= trials;
    
    return mean;
}

void test0()
{
    size_t n = 100000;
    
    vector<double> v { 1, 2, 3, 4, 5 };
    deque<double> d { v.begin(), v.end() };
    list<double> l { v.begin(), v.end() };
    forward_list<double> f { v.begin(), v.end() };
    set<double> s { v.begin(), v.end() };
    multiset<double> ms { v.begin(), v.end() };
    unordered_set<double> us { v.begin(), v.end() };
    unordered_multiset<double> ums { v.begin(), v.end() };
    
    cout << "mean=" << getMean(v, n) << endl;
    cout << "mean=" << getMean(d, n) << endl;
    cout << "mean=" << getMean(l, n) << endl;
    cout << "mean=" << getMean(f, n) << endl;
    cout << "mean=" << getMean(s, n) << endl;
    cout << "mean=" << getMean(ms, n) << endl;
    cout << "mean=" << getMean(us, n) << endl;
    cout << "mean=" << getMean(ums, n) << endl;
}

void test1()
{
    vector<string> v { "a", "b", "c", "d", "e" };
    auto iter = make_dice_iterator(v, rnd);
    copy(iter, iter.take(10), ostream_iterator<string>(cout, " "));
    cout << endl;
}

void test2()
{
    vector<string> src { "*", "/", "+", "-" };
    list<string> dst { "a", "b", "c", "d", "e" };
    
    auto iter = make_dice_iterator(src, rnd);
    copy(iter, iter.take(5), random_inserter(dst, rnd));
    copy(dst.begin(), dst.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

int main(int argc, const char * argv[])
{
    test0();
    test1();
    test2();
    return 0;
}
