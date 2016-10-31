/******************************************************************************************
 * 		MaxFibonacciHeap.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#ifndef MAX_FIBONACCI_HEAP_H
#define MAX_FIBONACCI_HEAP_H

#include <vector>

struct Node
{
    Node* parent;
    Node* leftSibling;
    Node* rightSibling;
    Node* child;
    bool childCut;
    long degree;
    long value;

    Node(long val) : value(val)
};

class MaxFibonacciHeap
{
public:

private:

};

#endif /* MAX_FIBONACCI_HEAP_H */


