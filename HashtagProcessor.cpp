/******************************************************************************************
 * 		HashtagProcessor.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#include "HashtagProcessor.h"

#include <cstring>
#include <iostream>

/**************************************************************
 * 		HashtagProcessor Constructor
 **************************************************************/
HashtagProcessor::HashtagProcessor(HashtagQueue& tagQ) : tagQueue(tagQ)
{
    // init fibheap
    fibonacciHeap.Initialize();
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 **************************************************************/
void HashtagProcessor::StartProcessing()
{
    // while hashtags to read from queue
    // read
    // if query, processquery
    // if hashtag, insert or increase key
    string readStr, hashtag;
    int frequency;

    while(tagQueue.ReadQueue(readStr))
    {
        if(IsQuery(readStr))
        {
            ProcessQuery(atoi(readStr.c_str()));
            continue;
        }

        GetHashtag(readStr, hashtag);
        GetHashtagFreqeuncy(readStr, frequency);

        if(HashtagExists(readStr))
            IncreaseHashtagFrequency(hashtag, frequency);
        else
            InsertNewHashtag(hashtag, frequency);
    }
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 **************************************************************/
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
 **************************************************************/
bool HashtagProcessor::IsQuery(string check)
{
    return !(check[0] == '#');
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 **************************************************************/
void HashtagProcessor::InsertNewHashtag(string hashtag, int initialAmount)
{
    Node* newNode = hashTable[hashtag];
    newNode = new Node();
    newNode->value = initialAmount;
    reverseHashTable[newNode] = hashtag;
    fibonacciHeap.Insert(newNode);
}

/**************************************************************
 * 		HashtagProcessor::IncreaseHashtagFrequency
 **************************************************************/
void HashtagProcessor::IncreaseHashtagFrequency(string hashtag, int amount)
{
    Node* incNode = hashTable[hashtag];
    fibonacciHeap.IncreaseKey(incNode, amount);
}

/**************************************************************
 * 		HashtagProcessor::GetMostFrequentHashtags
 **************************************************************/
string HashtagProcessor::GetMostFrequentHashtags(int numHashtags)
{
    /*  Get numHashtags most frequent hashtags from fibheap (n removeMax)
     *  create string of the hashtags
     *  insert n hashtags to fibheap
     */
    Node* nodeArray[numHashtags];
    string hashtags = "";

    for(int i=0; i<numHashtags; i++)
    {
        nodeArray[i] = fibonacciHeap.RemoveMax();
        hashtags += reverseHashTable[nodeArray[i]] + ",";
    }
    for(int i=0; i<numHashtags; i++)
        fibonacciHeap.Insert(nodeArray[i]);

    return hashtags;

}

/**************************************************************
 * 		HashtagProcessor::GetHashtag
 **************************************************************/
void HashtagProcessor::GetHashtag(string input, string& hashtag)
{
    hashtag = input.substr(1, input.find(' ')-1);
}

/**************************************************************
 * 		HashtagProcessor::GetHashtagFreqeuncy
 **************************************************************/
void HashtagProcessor::GetHashtagFreqeuncy(string input, int& frequency)
{
    int start = input.find(' ')+1;
    string freqStr = input.substr(start, input.length() - start);
    frequency = atoi(freqStr.c_str());
}

/**************************************************************
 * 		HashtagProcessor::ProcessQuery
 **************************************************************/
void HashtagProcessor::ProcessQuery(int numHashtags)
{
    writer.WriteToFile(GetMostFrequentHashtags(numHashtags));
}





