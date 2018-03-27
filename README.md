# "True" random access iterator in C++ &amp; random_inserter

There are two classes in this project that implement STL iterator interface. The first is a "true_random_access_iterator" that allows accessing any STL container at randomly selected locations. The position is shuffled when iterator gets incremented.
New location is choosen to be random() % size(container). This iterator is a forward iterator, hence it only supports increment operator, 
that is sufficient for this iterator type. It allows to write code like this:

```c++
size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine rnd{ static_cast<std::default_random_engine::result_type::result_type>(seed) };

auto iter = make_dice_iterator(cont, rnd);
for (int i = 0; i < trials; i++)
{
  auto x = *iter; // pick an element of a container at current random position
  mean += x;
  iter++; // shuffle the position
}
```

The second iterator is random_insert_iterator which is similar to common output iterators like back_insert_iterator and front_insert_iterator. Unlike these iterator types random_insert_iterators insert elements at random positions inside a container. It allows us to write code like this:

```c++
vector<string> src { "A", "B", "C", "D" };
list<string> dst { "a", "b", "c", "d" };

auto iter = make_dice_iterator(src, rnd);
copy(iter, iter.take(5), random_inserter(dst, rnd));

copy(dst.begin(), dst.end(), ostream_iterator<string>(cout, " "));
cout << endl;
```
  
true_random_access_iterator::take(long long n) is a convenience function for creating an 'end' iterator for use with
loops and algorithms. It creates an iterator that is n elements far from given iterator. When an iterator is shuffled n times by calling ++ operator, it becomes equal to its take(n) counterpart.
