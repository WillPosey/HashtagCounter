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
#include <cstddef>

struct Node
{
    Node* parent;
    Node* leftSibling;
    Node* rightSibling;
    Node* child;
    bool childCut;
    long degree;
    long value;

    Node() : parent(NULL), leftSibling(this), rightSibling(this), child(NULL),
             childCut(false), degree(0), value(0) {}
};

using namespace std;

class MaxFibonacciHeap
{
public:
    void Initialize();
    void Insert(Node* n);
    void IncreaseKey(Node* n, int amount);
    Node* RemoveMax();
private:
    int GetNumTopLevel();
    void PlaceTopLevel(Node* n);
    void CascadeCut(Node* n);
    void RemoveNode(Node* n);
    void SetNewMaxPointer();
    void Consolidate();
    Node* Meld(Node* positionalNode, Node* moveNode);
    void LinkNewNode(Node* left, Node* insertNode, Node* right);
    void LinkSiblings(Node* n);
    void AddToChildList(Node* parent, Node* newChild);
    void CompareToMax(Node* n);
    bool CheckIfChildPtr(Node* n);
    void AssignParentNewChildPtr(Node* oldChild);
    void PlaceChildrenTopLevel(Node* n);
    bool CheckForSiblings(Node* n);
    vector<Node*> GetChildrenList(Node* n);

    Node* maxPointer;
    bool mustConsolidate;
};

#endif /* MAX_FIBONACCI_HEAP_H */


