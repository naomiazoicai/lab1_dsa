#include <exception>
#include "SortedBag.h"
#include "SortedBagIterator.h"

///constructor
///complexity: Θ(1) worst, average and best
SortedBag::SortedBag(Relation r)
{
    this->capacity = 5;
    this->r = r;
    this->arrSize = 0;
    this->elements = new TElem[this->capacity];

}

///copy-constructor
///complexity: Θ(n)
SortedBag::SortedBag(const SortedBag& other)
{
    this->capacity = other.capacity;
    this->r = other.r;
    this->arrSize = other.arrSize;
    this->elements = new TElem[this->capacity];

    for (int i = 0; i < this->arrSize; i++) {
        this->elements[i] = other.elements[i];
    }
}

//preconditions: 2 bags that, at least one of them not empty
//postconditions: returns false if the bags are empty, reunites two bags and returns true otherwise
//complexity: total: O(n), worst case Θ(n), average case Θ(n) n-size of the dynamic array, best case: Θ(1)
bool SortedBag::reunion(SortedBag& other)
{
    if(arrSize == 0 && other.arrSize==0)
    {
        return false;
    }
    if(arrSize == 0 && other.arrSize!=0)
    {
        //*this = other;
        return true;
    }
    if(arrSize != 0 && other.arrSize==0)
    {
       // *this = ;
        return true;
    }

    int index = 0;
    int index_other = 0;
            while(!this->r(elements[index].elem, other.elements[index_other].elem) && arrSize>index && other.arrSize>index_other)
            {
                index++;
                index_other++;
            }
            if (elements[index].elem == other.elements[index_other].elem)
            {
                elements[index].frequency++;
            }
            if (r(elements[index].elem, elements[index_other].elem))
            {
                elements[index+1].elem = elements[index_other].elem;
                elements[index+1].frequency = elements[index_other].frequency;
                shift(index);
                arrSize++;
            }
    if(this->arrSize == this->capacity)
    {
        this->resize();
    }
    return true;
}

//subalgorithm reunion(da, other) is:
// if da.arrSize = 0 and other.arrSize = 0 then
//      return false
// end-if
//
// index<-0
// index_other<-0
// while !r (elements[index].elem, other.elements[index_other].elem) && arrSize>index && other.arrSize>index_other) execute
//      index<-index+1
//      index_other<-index_other+1
// end-while
//
// if elements[index].elem = other.elements[index_other].elem then
//      elements[index].frequency<-elements[index].frequency+1
// end-if
// if r(elements[index].elem, elements[index_other].elem) then
//      elements[index+1].elem = elements[index_other].elem
//      shift(index)
//      arrSize<-arrSize+1
// end-if
// if arrSize = capacity then
//      resize
// end-if
// end-subalgorithm

///realocates more memory when the capacity is full
///complexity: total: Θ(n), worst case Θ(n), average case Θ(n) n-size of the dynamic array, best case: Θ(n)
void SortedBag::resize()
{
    TElem *auxArray = new TElem[this->capacity * 2];
    for (int index = 0; index < this->arrSize; index++)
        auxArray[index] = this->elements[index];
    delete[] this->elements;
    this->elements = auxArray;
    this->capacity = this->capacity * 2;
}

///complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n), n-size of the dynamic array,
void SortedBag::resize_down()
{
    TElem *auxArray = new TElem[this->capacity / 2];
    for (int index = 0; index < this->arrSize; index++)
        auxArray[index] = this->elements[index];
    delete[] this->elements;
    this->elements = auxArray;
    this->capacity = this->capacity / 2;
}

///adds a new element to the SortedBag
///Complexity: total: O(n),  worst case: Θ(n), average case: Θ(n), best case: Θ(1) n-size of the dynamic array
void SortedBag::add(TComp e)
{
    //if we don't have any elements in the array, we add on the first position
    if(this->arrSize == 0)
    {
        this->elements[this->arrSize].elem = e;
        this->elements[this->arrSize].frequency = 1;
        this->arrSize++;

    }
    else
    {
        int index = 0;

        //finds the position where element should be inserted
        while(!this->r(e, elements[index].elem) && arrSize>index)
        {
            index++;
        }

        //the element is already in the array and we increase its frequency
        if(e == elements[index].elem)
        {
            elements[index].frequency++;
        }

        //adding the element on the last position
        else if (index == arrSize)
        {
            this->elements[index].elem = e;
            this->elements[index].frequency = 1;
            arrSize++;
        }
        else
        {   //adding the element somewhere in the middle of the array
            shift(index);
            this->elements[index].elem = e;
            this->elements[index].frequency = 1;
            arrSize++;
        }
    }

    //resizing in case there is not enough space in the container
    if(this->arrSize == this->capacity)
    {
        this->resize();
    }
}

///complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n), n-size of the dynamic array,
void SortedBag::shift(int index)
{
    for(int i = arrSize; i>index ;i--)
    {
        this->elements[i] = this->elements[i-1];
    }
}

///complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n), n-size of the dynamic array,
void SortedBag::reverse_shift(int index)
{
    for(int i = index; i<arrSize; i++)
    {
        this->elements[i] = this->elements[i+1];
    }
}

///removes an element from the SortedBag
///returns true if the element has been deleted or false if it does not exist
///complexity: O(n), worst case: Θ(n), average case:Θ(n), best case: Θ(1) n-size of the dynamic array
bool SortedBag::remove(TComp e)
{
    int index=0;
    //finding the index of the element we want to remove
    while(!this->r(e, elements[index].elem) && arrSize>index)
    {
        index++;
    }

    //return false if the element does not exist
    if(index == arrSize)
    {
        return false;
    }

    if(elements[index].elem == e)
    {   //if we find the element, we decrease its frequency
        elements[index].frequency--;

        //removing the pair if the frequency is 0 and shift all the other elements
        if(elements[index].frequency==0)
        {
            reverse_shift(index);
            arrSize--;
        }

        //resizing in case of need
        if(capacity  == arrSize * 4  )
        {
            this->resize_down();
        }
     return true;
    }
    return false;
}

//searches for an element in the SortedBag
//returns true if the elements exists, false otherwise
//complexity: O(n) n-size of the dynamic array
//bool SortedBag::search(TComp elem) const
//{
//    for (int index = 0; index < this->arrSize; index++)
//        if (elem == this->elements[index].elem)
//            return true;
//    return false;
//}


///searches for an element in the SortedBag
///returns true if the elements exists, false otherwise
///complexity: O(logn) worst case: Θ(logn), average case: Θ(logn) n-size of the dynamic array, best case: Θ(1)
 bool SortedBag::search(TComp elem) const
 {

    int left = 0;
    int right = this->arrSize - 1;
    int middle;

    while (left <= right)
    {
        middle = (left + right) / 2;
        if (this->elements[middle].elem == elem)
            return true;
        else if (r(this->elements[middle].elem, elem))
            left = middle + 1;
        else
            right = middle - 1;
    }
    return false;
}

///returns the number of occurences of a given element
///complexity: O(n), worst case: Θ(n), average case: Θ(n) n-size of the dynamic array, best case: Θ(1)
int SortedBag::nrOccurrences(TComp elem) const
{
    for (int index = 0; index < this->arrSize; index++)
        if (elem == this->elements[index].elem)
            return this->elements[index].frequency;
    return 0;
}


///returns the size of the SortedBag
///complexity:O(n), worst case: Θ(n) , average case: Θ(n) n-size of the dynamic array, best case: Θ(1)
int SortedBag::size() const
{
    int s = 0;
    for (int index = 0; index < this->arrSize; index++)
        s += this->elements[index].frequency;
    return s;
}

///verifies if the SortedBag is empty
///returns true if it is and false otherwise
///complexity: Θ(1) worst, average and best
bool SortedBag::isEmpty() const
{
    if(this->arrSize == 0)
        return true;
    return false;
}


///complexity: Θ(1) worst, average and best
SortedBagIterator SortedBag::iterator() const
{
    return SortedBagIterator(*this);
}

///destructor
///complexity: Θ(1) worst, average and best
SortedBag::~SortedBag()
{
    delete[] this->elements;
}
