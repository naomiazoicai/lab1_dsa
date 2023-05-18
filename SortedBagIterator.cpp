#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

///complexity: Θ(1) worst, average and best
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b){

    this->mainIndex = 0;
    this->frequency = 1;
}

///returns the current elment of the iterator or throws an exception if the iterator is not valid
///complexity: Θ(1) worst, average and best
TComp SortedBagIterator::getCurrent()
{
    if (valid())
        return bag.elements[mainIndex].elem;
    else
        throw exception();
}

///checks if the iterator is still valid
///returns true if it is and false otherwise
///complexity: Θ(1) worst, average and best
bool SortedBagIterator::valid()
{
    if (this->mainIndex >= this->bag.arrSize || this->mainIndex < 0)
        return false;
    return true;
}

///goes to the next element in the iterator
///complexity: Θ(1) worst, average and best
void SortedBagIterator::next()
{
    if (!valid())
        throw exception();

    if(this->frequency == bag.elements[mainIndex].frequency)
    {
        mainIndex++;
        frequency = 1;
    }
    else
    {
        frequency++;
    }
}

///resets the iterator
///complexity: Θ(1) worst, average and best
void SortedBagIterator::first()
{
    this->mainIndex = 0;
    this->frequency = 1;
}

