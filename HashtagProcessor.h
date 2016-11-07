/******************************************************************************************
 * 		HashtagProcessor.h
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
#ifndef HASHTAG_PROCESSOR_H
#define HASHTAG_PROCESSOR_H

#include "MaxFibonacciHeap.h"
#include "HashtagQueue.h"
#include "QueryWriter.h"

#include <unordered_map>
#include <string>

/* HashtagProcessor Class*/
class HashtagProcessor
{
public:
    /* Constructor */
    HashtagProcessor(HashtagQueue& tagQ);

    /* Processes all insertions, key increases, and queries from input file */
    void StartProcessing();

private:
    /* Methods to determine input type */
    bool IsQuery(string check);
    bool HashtagExists(string hashtag);

    /* Methods to retreive hashtag information */
    void GetHashtag(string input, string& hashtag);
    void GetHashtagFreqeuncy(string input, int& frequency);

    /* Methods to interface to the hash table and max fibonacci heap */
    void InsertNewHashtag(string hashtag, int initialAmount);
    void IncreaseHashtagFrequency(string hashtag, int increaseAmount);

    /* Methods to process queries */
    string GetMostFrequentHashtags(int numHashtags);
    void ProcessQuery(int numHashtags);

    /* Members */
    MaxFibonacciHeap fibonacciHeap;                 /* Max Fibonacci Heap used to track hashtag frequencies */

    unordered_map<string, Node*> hashTable;         /* Hash Table */

    unordered_map<Node*, string> reverseHashTable;  /* Reverse Hash Table */
                                                    /* used to look up hashtag from Node* returned in MaxFibonaciHeap.RemoveMax() */
                                                    /* saves time that would be needed to linearly search the hash tag to do a key look up by value */

    HashtagQueue& tagQueue;                         /* Queue to read input from */

    QueryWriter writer;                             /* Writer used to write queries */
};

#endif /* HASHTAG_PROCESSOR_H */



