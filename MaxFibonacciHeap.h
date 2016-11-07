/******************************************************************************************
 * 		MaxFibonacciHeap.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class contains the functionality of a max fibonacci heap
 ******************************************************************************************/
#ifndef MAX_FIBONACCI_HEAP_H
#define MAX_FIBONACCI_HEAP_H

#include <vector>
#include <cstddef>

/* Definition of Node structure contained in the max fibonacci heap */
struct Node
{
    Node* parent;
    Node* leftSibling;
    Node* rightSibling;
    Node* child;
    bool childCut;
    long degree;
    long value;

    /* Constructor for Node struct; initialize to point at itself in sibling list */
    Node(int initVal) : parent(NULL),
                        leftSibling(this),
                        rightSibling(this),
                        child(NULL),
                        childCut(false),
                        degree(0),
                        value(initVal)
                        {}
};

using namespace std;

/* MaxFibonacci Class */
class MaxFibonacciHeap
{
public:
    void Initialize();
    void Insert(Node* n);
    void IncreaseKey(Node* n, int amount);
    Node* RemoveMax();

private:
    /* Main operations of the heap */
    void CascadeCut(Node* n);
    void RemoveNode(Node* n);
    void Consolidate();

    /* Operations used to update or get information about the root level list */
    int GetNumTopLevel();
    void PlaceTopLevel(Node* n);
    void PlaceChildrenTopLevel(Node* n);
    void CompareToMax(Node* n);
    void SetNewMaxPointer();

    /* Operations used to update Node parent, child, and sibling pointers */
    Node* Meld(Node* positionalNode, Node* moveNode);
    void LinkNewNode(Node* left, Node* insertNode, Node* right);
    void LinkSiblings(Node* n);
    void AddToChildList(Node* parent, Node* newChild);
    void AssignParentNewChildPtr(Node* oldChild);

    /* Operations used to update or get information about a Node's children or child pointer status */
    bool CheckForSiblings(Node* n);
    bool CheckIfChildPtr(Node* n);
    vector<Node*> GetChildrenList(Node* n);

    /* Members */
    Node* maxPointer;       /* Pointer to the max fibonacci heap */
    bool mustConsolidate;   /* Flag indicating that a remove or increase key operation has added nodes to the top level list */
};

#endif /* MAX_FIBONACCI_HEAP_H */


