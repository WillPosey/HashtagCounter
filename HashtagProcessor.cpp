/******************************************************************************************
 * 		HashtagProcessor.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class reads in hashtags and tracks their frequencies through the use of a hash
 *      table and a max fibonacci heap, as well as serves queries for the most popular hashtags
 *      by removing the maximum node held by teh fibonacci heap, doing a reverse lookup for
 *      the removed node's corresponding hashtag, and writing the hashtag to an output file
 *      through the use of a QueryWriter object
 ******************************************************************************************/
#include "HashtagProcessor.h"

#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

/**************************************************************
 * 		HashtagProcessor Constructor
 *
 *      Initializes the max fibonacci heap
 *      Sets the HashtagQueue reference
 **************************************************************/
HashtagProcessor::HashtagProcessor(HashtagQueue& tagQ) : tagQueue(tagQ)
{
    fibonacciHeap.Initialize();
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 *
 *      Perform all hashtag insertions and key increases
 *      Process all queries
 **************************************************************/
void HashtagProcessor::StartProcessing()
{
    string readStr, hashtag;
    int frequency;

    /* Loop through all input contained in the queue */
    while(tagQueue.ReadQueue(readStr))
    {
        /* Process the query */
        if(IsQuery(readStr))
        {
            ProcessQuery(atoi(readStr.c_str()));
            continue;
        }

        /* Get the hashtag and freqeuncy from the input string */
        GetHashtag(readStr, hashtag);
        GetHashtagFreqeuncy(readStr, frequency);

        /* hashtag exists, increase the frequency */
        if(HashtagExists(hashtag))
            IncreaseHashtagFrequency(hashtag, frequency);
        /* new hashtag, perform insertion */
        else
            InsertNewHashtag(hashtag, frequency);
    }
}

/******************************************************************
 * 		HashtagProcessor::HashtagExists
 *
 *      Determine if hashtag is already contained in the hashTable
 ******************************************************************/
bool HashtagProcessor::HashtagExists(string hashtag)
{
    static unordered_map<string, Node*>::const_iterator found;

    found = hashTable.find(hashtag);
    if(found == hashTable.end())
        return false;
    return true;
}

/**************************************************************
 * 		HashtagProcessor::IsQuery
 *
 *      Determine if the input string is a query
 **************************************************************/
bool HashtagProcessor::IsQuery(string check)
{
    return !(check[0] == '#');
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 *
 *
 **************************************************************/
void HashtagProcessor::InsertNewHashtag(string hashtag, int initialAmount)
{
    /* Create a new node and insert it into the hash table and fibonacci heap */
    Node* newNode = new Node(initialAmount);
    hashTable[hashtag] = newNode;
    reverseHashTable[newNode] = hashtag;
    fibonacciHeap.Insert(newNode);
}

/**************************************************************
 * 		HashtagProcessor::IncreaseHashtagFrequency
 *
 *      Increase the frequency of an already existing hashtag
 **************************************************************/
void HashtagProcessor::IncreaseHashtagFrequency(string hashtag, int amount)
{
    /* Retrieve node from hashTable, increase Node Key in fibonacci heap */
    Node* incNode = hashTable[hashtag];
    fibonacciHeap.IncreaseKey(incNode, amount);
    hashTable[hashtag] = incNode;
}

/**************************************************************
 * 		HashtagProcessor::GetMostFrequentHashtags
 *
 *      Retreive the most frequent hashtags and create a string
 *      to write to the output file
 **************************************************************/
string HashtagProcessor::GetMostFrequentHashtags(int numHashtags)
{
    /*  Get numHashtags most frequent hashtags from fibheap (n removeMax)
     *  create string of the hashtags
     *  insert n hashtags to fibheap
     */
    Node* nodeArray[numHashtags];
    string hashtags = "";

    /* Perform numHashtags retrievals */
    for(int i=0; i<numHashtags; i++)
    {
        /* Retrieve maximum from fibonacci heap */
        nodeArray[i] = fibonacciHeap.RemoveMax();

        /* Perform reverse lookup to get hashtag string associated with the Node* */
        hashtags += reverseHashTable[nodeArray[i]];
        if(i < numHashtags-1)
            hashtags += ",";
    }
    /* Reinsert the Nodes that were removed */
    for(int i=0; i<numHashtags; i++)
        fibonacciHeap.Insert(nodeArray[i]);

    return hashtags;

}

/**************************************************************
 * 		HashtagProcessor::GetHashtag
 *
 *      Return the hashtag from the input string
 **************************************************************/
void HashtagProcessor::GetHashtag(string input, string& hashtag)
{
    hashtag = input.substr(1, input.find(' ')-1);
}

/**************************************************************
 * 		HashtagProcessor::GetHashtagFreqeuncy
 *
 *      Retrieve the freqeuncy of the input hashtag, found
 *      at the end ofthe input string
 **************************************************************/
void HashtagProcessor::GetHashtagFreqeuncy(string input, int& frequency)
{
    int start = input.find(' ')+1;
    string freqStr = input.substr(start, input.length() - start);
    frequency = atoi(freqStr.c_str());
}

/********************************************************************
 * 		HashtagProcessor::ProcessQuery
 *
 *      Retrieve the number of most frequent hashtags as indicated
 *      by the query, and write them to the output file through the
 *      QueryWriter object
 ********************************************************************/
void HashtagProcessor::ProcessQuery(int numHashtags)
{
    writer.WriteToFile(GetMostFrequentHashtags(numHashtags));
}





