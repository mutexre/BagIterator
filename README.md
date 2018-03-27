# DiceIterator
"True" random access iterator in C++ &amp; random_inserter

There are two classes in this project that implement STL iterator interface. The first is "true_random_access_iterator".
It allows to access an STL container at randomly selected locations. The position is randomised when incrementing an iterator.
New location is choosen as random() % size(container). This iterator is a forward iterator, hence it only supports increment operator, 
that is absolutely sufficient for this iterator type.
