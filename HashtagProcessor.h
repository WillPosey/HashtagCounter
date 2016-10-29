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
    void IncreaseHashtagFrequency(string hashtag, int amount);
    string GetMostFrequentHashtags(int numHashtags);
    void ProcessQuery(int numHashtags);

    unordered_map<string, Node*> hashTable;
    HashtagQueue tagQueue;
    MaxFibonacciHeap fibonacciHeap;
    QueryWriter writer;
};

#endif /* HASHTAG_PROCESSOR_H */



