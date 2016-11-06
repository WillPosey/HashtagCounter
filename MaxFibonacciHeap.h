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

    Node() : parent(NULL), leftSibling(this), rightSibling(this), child(NULL)
             childCut(false), degree(0), value(0)
};

class MaxFibonacciHeap
{
public:
    void Initialize();
    void Insert(Node* n);
    void IncreaseKey(Node* n, int amount);
    Node* RemoveMax();
private:
    Node* maxPointer;
    void PlaceTopLevel(Node* n);
    void CascadeCut(Node* n);
    void RemoveNode(Node* n);
    void SetMaxPointer(Node* n);
    void Consolidate();
    void LinkNewNode(Node* left, Node* insertNode, Node* right);
    void LinkSiblings(Node* n);
    void CompareToMax(Node* n);
    bool CheckIfChildPtr(Node* n);
    void AssignParentNewChild(Node* oldChild);
    void PlaceChildrenTopLevel(Node* n);
    bool CheckForSiblings(Node* n);
    vector<Node*> GetChildrenList(Node* n);
};

#endif /* MAX_FIBONACCI_HEAP_H */


