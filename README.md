# "True" random access iterator &amp; random_inserter

The aim of this repository is to provide convenience iterators for shuffled access and insertion. The first iterator provided is a "true_random_access_iterator" that allows accessing a container at a randomly selected location. The position iterator is pointing at is randomly shuffled when iterator is incremented. In other words, new position is choosen to be equal to random() % size(container). The iterator is a forward iterator and it only supports increment operation. It allows one to write code like this:

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

The second iterator is a random_insert_iterator which is similar to common output iterator types like back_insert_iterator and front_insert_iterator. Random_insert_iterator inserts an element at a random position inside a container using insert(iter, value) member function. This class allows one to write code like this:

```c++
vector<string> src { "A", "B", "C", "D" };
list<string> dst { "a", "b", "c", "d" };

auto iter = make_dice_iterator(src, rnd);
copy(iter, iter.take(5), random_inserter(dst, rnd));
```
  
true_random_access_iterator::take(long long n) is a convenience function for creating an 'end' iterator for use with
loops and various STL algorithms. It creates an iterator that is n elements ahead of given iterator. When an instance of true_random_access_iterator is shuffled n times by calling ++ operator, it becomes equal to its take(n) counterpart.
