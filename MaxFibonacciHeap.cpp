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
    mustConsolidate = false;
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
            AssignParentNewChildPtr(n);
            PlaceTopLevel(n);
            CascadeCut(nParent);
            mustConsolidate = true;
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
    SetNewMaxPointer();
    RemoveNode(retMax);
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

    AssignParentNewChildPtr(n);
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
        mustConsolidate = true;
        vector<Node*> childrenList = GetChildrenList(n);
        for(vector<Node*>::iterator it = childrenList.begin(); it < childrenList.end(); it++)
            PlaceTopLevel(*it);
    }
}

/**************************************************************
 * 		MaxFibonacciHeap::AssignParentNewChildPtr
 *
 **************************************************************/
void MaxFibonacciHeap::AssignParentNewChildPtr(Node* oldChild)
{
    if(oldChild->parent != NULL)
    {
        if(CheckIfChildPtr(oldChild))
        {
            if(CheckForSiblings(oldChild))
                oldChild->parent->child = oldChild->rightSibling;
            else
                oldChild->parent->child = NULL;
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
    n->parent = NULL;
    CompareToMax(n);
}

/**************************************************************
 * 		MaxFibonacciHeap::CascadeCut
 **************************************************************/
void MaxFibonacciHeap::CascadeCut(Node* n)
{
    // remember to set mustConsolidate if needed
    if(n != NULL)
    {
        if(n->parent != NULL)
        {
            if(n->childCut)
            {
                mustConsolidate = true;
                LinkSiblings(n);
                AssignParentNewChildPtr(n);
                Node* parent = n->parent;
                PlaceTopLevel(n);
                CascadeCut(parent);
            }
            else
                n->childCut = true;
        }
        else
            n->childCut = false;
    }
}

/**************************************************************
 * 		MaxFibonacciHeap::SetNewMaxPointer
 **************************************************************/
void MaxFibonacciHeap::SetNewMaxPointer()
{
    // traverse top level list (temporary max set)
    // compare and get max
    Node* currentNode = maxPointer->rightSibling;
    Node* start = maxPointer;
    Node* tempMax = maxPointer->rightSibling;
    if(maxPointer == maxPointer->rightSibling)
        maxPointer = NULL;
    else
    {
        while(currentNode != start)
        {
            if(tempMax->value < currentNode->value)
                tempMax = currentNode;
            currentNode = currentNode->rightSibling;
        }
        maxPointer = tempMax;
    }
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
 * 		MaxFibonacciHeap::LinkSiblings
 *
 **************************************************************/
void MaxFibonacciHeap::AddToChildList(Node* parent, Node* newChild)
{
    if(parent->child)
        LinkNewNode(parent->child, newChild, parent->child->rightSibling);
    else
    {
        parent->child = newChild;
        newChild->leftSibling = newChild;
        newChild->rightSibling = newChild;
    }
    newChild->parent = parent;
    parent->degree++;
}

/**************************************************************
 * 		MaxFibonacciHeap::GetNumTopLevel
 *
 **************************************************************/
int MaxFibonacciHeap::GetNumTopLevel()
{
    int numTopLevel = 0;
    Node* start = maxPointer;
    Node* currentNode;
    for(currentNode = start; currentNode->rightSibling != start; currentNode = currentNode->rightSibling)
        numTopLevel++;
    return numTopLevel;
}

/**************************************************************
 * 		MaxFibonacciHeap::Consolidate
 *
 **************************************************************/
void MaxFibonacciHeap::Consolidate()
{
    vector<Node*> ranks;
    int currentRank, numRoots, numSteps;
    Node* currentNode;

    if(mustConsolidate)
    {
        mustConsolidate = false;
        numRoots = GetNumTopLevel();
        for(currentNode = maxPointer, numSteps = 0; numSteps < numRoots; numSteps++, currentNode = currentNode->rightSibling)
        {
            currentRank = currentNode->degree;

            /* No node has had this rank yet */
            if(ranks.size() <= currentRank)
            {
                /* Fill vector with null node pointers until reaching capacity of currentRank */
                while(ranks.size() <= currentRank)
                    ranks.push_back(NULL);
                ranks[currentRank] = currentNode;
                continue;
            }

            /* Combine same degree trees */
            while(ranks[currentRank] != NULL)
            {
                /* Meld and clear index in ranks vector, increment rank */
                currentNode = Meld(currentNode, ranks[currentRank]);
                ranks[currentRank] = NULL;
                currentRank++;
                if(ranks.size() <= currentRank)
                    ranks.push_back(NULL);
            }
            ranks[currentRank] = currentNode;
        }
    }
}

/**************************************************************
 * 		MaxFibonacciHeap::Meld
 **************************************************************/
Node* MaxFibonacciHeap::Meld(Node* positionalNode, Node* moveNode)
{
    if(positionalNode->value >= moveNode->value)
    {
        /* remove moveNode from current level sibling list */
        /* Add moveNode to child list of positionalNode */
        LinkSiblings(moveNode);
        AddToChildList(positionalNode, moveNode);
        return positionalNode;
    }
    else
    {
        /* save positionalNode's siblings from current level sibling list */
        /* remove moveNode from current level sibling list */
        /* palcer moveNode at positionalNode's position in sibling list */
        /* Add positionalNode to child list of moveNode */
        Node* right = positionalNode->rightSibling;
        Node* left = positionalNode->leftSibling;
        LinkSiblings(moveNode);
        LinkNewNode(left, moveNode, right);
        AddToChildList(moveNode, positionalNode);
        return moveNode;
    }
}






