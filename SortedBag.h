#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR


//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;

typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
    SortedBag(SortedBag &);

    SortedBag(const SortedBag &other);

    friend class SortedBagIterator;

private:

    struct TElem{
        TComp elem;
        int frequency;
    };
    Relation r;
    TElem *elements;        //a TElem is a pair
    int arrSize;
    int capacity;


public:
    //constructor
    SortedBag(Relation r);

    void resize();

    //adds an element to the sorted bag
    void add(TComp e);

    void shift(int index);

    void reverse_shift(int index);

    //removes one occurence of an element from a sorted bag
    //returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
    bool remove(TComp e);

    //checks if an element appearch is the sorted bag
    bool search(TComp e) const;

    //returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp e) const;

    //returns the number of elements from the sorted bag
    int size() const;

    //returns an iterator for this sorted bag
    SortedBagIterator iterator() const;

    //checks if the sorted bag is empty
    bool isEmpty() const;

    //destructor
    ~SortedBag();

    void resize_down();


    bool reunion(SortedBag &other);
};