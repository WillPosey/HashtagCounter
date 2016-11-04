/******************************************************************************************
 * 		HashtagProcessor.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#ifndef HASHTAG_PROCESSOR_H
#define HASHTAG_PROCESSOR_H

#include "MaxFibonacciHeap.h"
#include "HashtagQueue.h"
#include "QueryWriter.h"

#include <unordered_map>
#include <string>

class HashtagProcessor
{
public:
    HashtagProcessor(HashtagQueue tagQ);
    void StartProcessing();
private:
    bool HashtagExists(string hashtag);
    void InsertNewHashtag(string hashtag, int initialAmount);
    void IncreaseHashtagFrequency(string hashtag, int increaseAmount);
    string GetMostFrequentHashtags(int numHashtags);
    void ProcessQuery(int numHashtags);

    unordered_map<string, Node*> hashTable;
    unordered_map<Node*, string> reverseHashTable;  // so you don't have to linearly search hash table when doing removeMax
    HashtagQueue tagQueue;
    MaxFibonacciHeap fibonacciHeap;
    QueryWriter writer;
};

#endif /* HASHTAG_PROCESSOR_H */



