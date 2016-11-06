/******************************************************************************************
 * 		MaxFibonacciHeap.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#include "MaxFibonacciHeap.h"

/**************************************************************
 * 		MaxFibonacciHeap::Initialize
 *
 **************************************************************/
void MaxFibonacciHeap::Initialize()
{
    maxPointer = NULL;
}

/**************************************************************
 * 		MaxFibonacciHeap::Insert
 *
 **************************************************************/
void MaxFibonacciHeap::Insert(Node* n)
{
    /* Must insert the node with key value already set */
    n->parent = NULL;
    n->child = NULL;
    n->childCut = false;
    n->degree = 0;

    /* Check if not first element in heap */
    if(maxPointer != NULL)
    {
        /* insert into top level list */
        /* check if this should be the new max */
        PlaceTopLevel(n);
        return;
    }

    /* First insert, set as max */
    n->rightSibling = n;
    n->leftSibling = n;
    maxPointer = n;
}

/**************************************************************
 * 		MaxFibonacciHeap::CompareToMax
 *
 **************************************************************/
void MaxFibonacciHeap::CompareToMax(Node* n)
{
    /* set as new maxPointer if no current max pointer or greater key value */
    maxPointer = ( (maxPointer->value < n->value) || (maxPointer == NULL) ) ? n : maxPointer;
}

/**************************************************************
 * 		MaxFibonacciHeap::CheckIfChildPtr
 *
 **************************************************************/
bool MaxFibonacciHeap::CheckIfChildPtr(Node* n)
{
    return ( (n->parent != NULL) && (n->parent->child == n) );
}

/**************************************************************
 * 		MaxFibonacciHeap::CheckForSiblings
 *
 **************************************************************/
bool MaxFibonacciHeap::CheckForSiblings(Node* n)
{
    return !( n->rightSibling == n );
}

/**************************************************************
 * 		MaxFibonacciHeap::GetChildrenList
 *
 **************************************************************/
vector<Node*> MaxFibonacciHeap::GetChildrenList(Node* n)
{
    vector<Node*> childrenList;
    Node* startNode = n->child;
    Node* currentNode = startNode;

    while(currentNode->rightSibling != startNode)
        childrenList.push_back(currentNode);

    return childrenList;
}


/**************************************************************
 * 		MaxFibonacciHeap::IncreaseKey
 *
 **************************************************************/
void MaxFibonacciHeap::IncreaseKey(Node* n, int amount)
{
    n->value += amount;

    /* Check if parent value has been surpassed */
    if(n->parent != NULL)
        if(n->value > n->parent->value)
        {
            /* CascadeCut() from increased key node parent's position */
            /* Combine same order heaps in top level list */
            Node* nParent = n->parent;
            AssignParentNewChild(n);
            PlaceTopLevel(n);
            CascadeCut(nParent);
            Consolidate();
        }

}

/**************************************************************
 * 		MaxFibonacciHeap::RemoveMax
 **************************************************************/
Node* MaxFibonacciHeap::RemoveMax()
{
    /* save max pointer to return */
    /* save right sibling to traverse top level list*/
    /* regular remove, then consolidate top level list */
    /* set then new max pointer */
    Node* retMax = maxPointer;
    maxPointer = maxPointer->rightSibling;      // temporary
    RemoveNode(retMax);
    SetMaxPointer(temp);
    return retMax;
}

/**************************************************************
 * 		MaxFibonacciHeap::RemoveNode
 *
 **************************************************************/
void MaxFibonacciHeap::RemoveNode(Node* n)
{
    // link gap in sibling list
    // if children, place top level, set parent to null
    // if child ptr of parent, and siblings are only you (function: CheckIfChildPtr() + CheckIfOnlyChild() SetSibling), set child null
    // if child ptr of parent, have siblings, set sibling as child ptr
    //
    LinkSiblings(n);

    PlaceChildrenTopLevel(n);

    AssignParentNewChild(n);
    CascadeCut(n->parent);

    Consolidate();
}

/**************************************************************
 * 		MaxFibonacciHeap::PlaceChildrenTopLevel
 *
 **************************************************************/
void MaxFibonacciHeap::PlaceChildrenTopLevel(Node* n)
{
    if(n->degree)
    {
        vector<Node*> childrenList = GetChildrenList(n);
        for(vector<Node*>iterator it = childrenList.begin(), it < childrenList.end(), it++)
        PlaceTopLevel(*it);
    }
}

/**************************************************************
 * 		MaxFibonacciHeap::AssignParentNewChild
 *
 **************************************************************/
void MaxFibonacciHeap::AssignParentNewChild(Node* oldChild)
{
    if(n->parent != NULL)
    {
        if(CheckIfChildPtr(n))
        {
            if(CheckForSiblings(n))
                n->parent->child = n->rightSibling;
            else
                n->parent->child = NULL;
        }
    }
}

/**************************************************************
 * 		MaxFibonacciHeap::PlaceTopLevel
 *
 **************************************************************/
void MaxFibonacciHeap::PlaceTopLevel(Node* n)
{
    /* Place into top level through the use of the maxPointer */
    LinkNewNode(maxPointer, n, maxPointer->rightSibling);
    CompareToMax(n);
}

/**************************************************************
 * 		MaxFibonacciHeap::CascadeCut
 **************************************************************/
void MaxFibonacciHeap::CascadeCut(Node* n)
{
    if(n->childCut)
    {

    }
    else
        n->childCut = true;
}

/**************************************************************
 * 		MaxFibonacciHeap::SetMaxPointer
 **************************************************************/
void MaxFibonacciHeap::SetMaxPointer(Node* n)
{
    // traverse top level list (temporary max set)
    // compare and get max
}

/**************************************************************
 * 		MaxFibonacciHeap::LinkNewNode
 *
 **************************************************************/
void MaxFibonacciHeap::LinkNewNode(Node* left, Node* insertNode, Node* right)
{
    left->rightSibling = insertNode;
    insertNode->leftSibling = left;
    insertNode->rightSibling = right;
    right->leftSibling = insertNode;
}

/**************************************************************
 * 		MaxFibonacciHeap::LinkSiblings
 *
 **************************************************************/
void MaxFibonacciHeap::LinkSiblings(Node* n)
{
    n->leftSibling->rightSibling = n->rightSibling;
    n->rightSibling->leftSibling = n->leftSibling;
}

/**************************************************************
 * 		MaxFibonacciHeap::Consolidate
 **************************************************************/
void MaxFibonacciHeap::Consolidate()
{

}






