/******************************************************************************************
 * 		MaxFibonacciHeap.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class contains the functionality of a max fibonacci heap
 ******************************************************************************************/
#include "MaxFibonacciHeap.h"

/*****************************************************************
 * 		MaxFibonacciHeap::Initialize
 *
 *      Set the maxPointer to null to indicate the heap is empty
 *****************************************************************/
void MaxFibonacciHeap::Initialize()
{
    maxPointer = NULL;
    mustConsolidate = false;
}

/****************************************************************************
 * 		MaxFibonacciHeap::Insert
 *
 *      Insert a node into the heap by placing it into the top level list
 *      using the maxPointer; check if Node n is the new maxPointer
 ****************************************************************************/
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

/********************************************************************
 * 		MaxFibonacciHeap::CompareToMax
 *
 *      Node n has been placed into the top level list
 *      Compare Node n to the maxPointer, update maxPointer if needed
 ********************************************************************/
void MaxFibonacciHeap::CompareToMax(Node* n)
{
    /* set as new maxPointer if no current max pointer or greater key value */
    maxPointer = ( (maxPointer->value >= n->value) || (maxPointer == NULL) ) ? maxPointer : n;
}

/**************************************************************
 * 		MaxFibonacciHeap::CheckIfChildPtr
 *
 *      Determine if Node n is the child pointer of its parent
 **************************************************************/
bool MaxFibonacciHeap::CheckIfChildPtr(Node* n)
{
    return ( (n->parent != NULL) && (n->parent->child == n) );
}

/**************************************************************
 * 		MaxFibonacciHeap::CheckForSiblings
 *
 *      Determine if Node n has any siblings by checking if its
 *      sibling pointer points to itself
 **************************************************************/
bool MaxFibonacciHeap::CheckForSiblings(Node* n)
{
    return !( n->rightSibling == n );
}

/********************************************************************
 * 		MaxFibonacciHeap::GetChildrenList
 *
 *      Return the children of Node n in a vector of node pointers
 ********************************************************************/
vector<Node*> MaxFibonacciHeap::GetChildrenList(Node* n)
{
    vector<Node*> childrenList;

    /* If no children, return empty vector */
    if(n->degree)
    {
        /* Traverse children list, and place into the vector */
        Node* startNode = n->child;
        Node* currentNode = startNode;

        while(currentNode->rightSibling != startNode)
            childrenList.push_back(currentNode);
    }
    return childrenList;
}


/**********************************************************************************
 * 		MaxFibonacciHeap::IncreaseKey
 *
 *      Increase the key of Node n, cascade cut or set as new max if needed
 **********************************************************************************/
void MaxFibonacciHeap::IncreaseKey(Node* n, int amount)
{
    n->value += amount;

    /* Check if n is a top level node */
    if(n->parent != NULL)
    {
        /* Parent's value has been surpassed */
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
    /* Check if now the new max */
    else
        CompareToMax(n);
}

/**************************************************************
 * 		MaxFibonacciHeap::RemoveMax
 *
 *      Return the Node associated with the maxPointer
 *      Update the heap
 **************************************************************/
Node* MaxFibonacciHeap::RemoveMax()
{
    /* save max pointer to return */
    /* save right sibling to traverse top level list */
    /* regular remove, then consolidate top level list */
    /* set then new max pointer */
    Node* retMax = maxPointer;
    SetNewMaxPointer();
    RemoveNode(retMax);
    return retMax;
}

/*******************************************************************************
 * 		MaxFibonacciHeap::RemoveNode
 *
 *      Node n is being removed, and its sibling list must be updated,
 *      its children must be reinserted, and cascading cuts and consolidation
 *      may be needed
 *******************************************************************************/
void MaxFibonacciHeap::RemoveNode(Node* n)
{
    /* Link the gap in the sibling list caused by removing Node n */
    LinkSiblings(n);

    /* Place any children of n into the top level list */
    PlaceChildrenTopLevel(n);

    /* If Node n was a child pointer of its parent, updated the parent's child pointer */
    AssignParentNewChildPtr(n);

    /* Conditionally CascadeCut from parent node and Consolidate */
    CascadeCut(n->parent);
    Consolidate();
}

/************************************************************************************
 * 		MaxFibonacciHeap::PlaceChildrenTopLevel
 *
 *      Node n has been removed, and its children must be reinserted to the heap
 ************************************************************************************/
void MaxFibonacciHeap::PlaceChildrenTopLevel(Node* n)
{
    /* Check if the node had any children */
    if(n->degree)
    {
        /* Place each child in the top level list, and indicate consolidation is needed */
        mustConsolidate = true;
        vector<Node*> childrenList = GetChildrenList(n);
        for(vector<Node*>::iterator it = childrenList.begin(); it < childrenList.end(); it++)
            PlaceTopLevel(*it);
    }
}

/****************************************************************************************
 * 		MaxFibonacciHeap::AssignParentNewChildPtr
 *
 *      A node oldChild has been removed from its sibling list
 *      If the oldChild was a child pointer, the child pointer must be updated
 ****************************************************************************************/
void MaxFibonacciHeap::AssignParentNewChildPtr(Node* oldChild)
{
    /* Check if the oldChild node was at the top level */
    if(oldChild->parent != NULL)
    {
        /* If oldChild was the child pointer of its parent */
        /* then set the parent's child pointer to a sibling or to null */
        if(CheckIfChildPtr(oldChild))
        {
            if(CheckForSiblings(oldChild))
                oldChild->parent->child = oldChild->rightSibling;
            else
                oldChild->parent->child = NULL;
        }
    }
}

/******************************************************************
 * 		MaxFibonacciHeap::PlaceTopLevel
 *
 *      Insert the node to the right of the maxPointer
 *      Determine if the newly inserted node is now the maxPointer
 ******************************************************************/
void MaxFibonacciHeap::PlaceTopLevel(Node* n)
{
    LinkNewNode(maxPointer, n, maxPointer->rightSibling);
    n->parent = NULL;
    CompareToMax(n);
}

/*****************************************************************************************
 * 		MaxFibonacciHeap::CascadeCut
 *
 *      Node n has just had a child removed
 *      If Node n exists and is not a top level node, check its childCut value
 *      If this is not the first time a child has been removed from n, remove it from its
 *      sibling lsit, place at the top level, and make recursive call on n's parent
 *****************************************************************************************/
void MaxFibonacciHeap::CascadeCut(Node* n)
{
    /* Check if the node that was removed was actually a top level node */
    /* if the node was at the top level, it would have passed in a null parent pointer */
    if(n != NULL)
    {
        /* Check if the node is at the top level */
        if(n->parent != NULL)
        {
            /* Cut node n from its sibling list and place at top level */
            /* Make recursive call on node n's parent */
            if(n->childCut)
            {
                mustConsolidate = true;
                LinkSiblings(n);
                AssignParentNewChildPtr(n);
                Node* parent = n->parent;
                PlaceTopLevel(n);
                CascadeCut(parent);
            }
            /* This is the first time a child node has been removed from node n */
            else
                n->childCut = true;
        }
        /* Node n is at top level, ensure childCut is set to false */
        else
            n->childCut = false;
    }
}

/********************************************************************
 * 		MaxFibonacciHeap::SetNewMaxPointer
 *
 *      The maxPointer node is being removed, traverse top level
 *      list and set maxPointer to node with the next greatest value
 ********************************************************************/
void MaxFibonacciHeap::SetNewMaxPointer()
{
    Node* currentNode = maxPointer->rightSibling;
    Node* start = maxPointer;
    Node* tempMax = maxPointer->rightSibling;

    /* maxPointer was the only node in the heap */
    if(maxPointer == maxPointer->rightSibling)
        maxPointer = NULL;
    /* traverse through top level list, set new maxPointer */
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
 *      A new node insertNode is being added to a siblnig list
 *      Insert between left and right nodes
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
 *      Node n is being removed from its sibling list
 *      Link together Node n's siblings
 **************************************************************/
void MaxFibonacciHeap::LinkSiblings(Node* n)
{
    n->leftSibling->rightSibling = n->rightSibling;
    n->rightSibling->leftSibling = n->leftSibling;
}

/*************************************************************************
 * 		MaxFibonacciHeap::AddToChildList
 *
 *      Insert newChild node to child list of parent node
 *************************************************************************/
void MaxFibonacciHeap::AddToChildList(Node* parent, Node* newChild)
{
    /* the child pointer of the parent node exists */
    /* insert newChild node to the right of the parent node's child pointer */
    if(parent->child)
        LinkNewNode(parent->child, newChild, parent->child->rightSibling);
    /* the parent node has no children */
    /* point parent's child pointer at newChild node */
    else
    {
        parent->child = newChild;
        newChild->leftSibling = newChild;
        newChild->rightSibling = newChild;
    }
    /* set newChild's parent pointer ot the parent node */
    /* increase parent's degree to account for newChild */
    newChild->parent = parent;
    parent->degree++;
}

/************************************************************************
 * 		MaxFibonacciHeap::GetNumTopLevel
 *
 *      Traverse through the top level list, starting at the maxPointer
 *      Return the count of the nodes in the top level list
 ************************************************************************/
int MaxFibonacciHeap::GetNumTopLevel()
{
    /* Heap is empty */
    if(maxPointer == NULL)
        return 0;

    /* Heap has at least the maxPointer in the top level list */
    /* Traverse through list once, incrementing count at each node */
    int numTopLevel = 1;
    Node* start = maxPointer;
    Node* currentNode;

    for(currentNode = start; currentNode->rightSibling != start; currentNode = currentNode->rightSibling)
        numTopLevel++;

    return numTopLevel;
}

/***************************************************************************************
 * 		MaxFibonacciHeap::Consolidate
 *
 *      Consolidate is used to combine nodes of the same degree at the root level
 *      Consolidation is only performed if a node removal or key increase has
 *      caused children nodes to be reinserted at the root level
 *      One traversal is made through the root level list, melding nodes where necessary
 ***************************************************************************************/
void MaxFibonacciHeap::Consolidate()
{
    vector<Node*> ranks;
    int currentRank, numRoots, numSteps;
    Node* currentNode;

    /* Check first if new nodes have indeed been placed at root level */
    if(mustConsolidate)
    {
        /* Get number of nodes in top level, traverse through and meld same degree nodes */
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

/********************************************************************************
 * 		MaxFibonacciHeap::Meld
 *
 *      Meld is used in Consolidate to meld two nodes of equal degree
 *      In order to make only pass through the root level nodes,
 *      the positionalNode should be the node currently being processed
 *      in Consolidate, and moveNode should be the node previously processed
 *      that now has the same degree as positionalNode
 ********************************************************************************/
Node* MaxFibonacciHeap::Meld(Node* positionalNode, Node* moveNode)
{
    /* Determine which node has a greater value */
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






