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

/**************************************************************
 * 		HashtagProcessor Constructor
 **************************************************************/
HashtagProcessor::HashtagProcessor(HashtagQueue tagQ) : tagQueue(tagQ)
{
    // init fibheap
}

/**************************************************************
 * 		HashtagProcessor::StartProcessing
 **************************************************************/
void HashtagProcessor::StartProcessing()
{
    // while hashtags to read from queue
    // read
    // if query, processquery
    // if hashtag, increase key
}

/**************************************************************
 * 		HashtagProcessor::IncreaseHashtagFrequency
 **************************************************************/
void HashtagProcessor::IncreaseHashtagFrequency(string hashtag, int amount)
{
    // get node from hashtable
    // call increase key on node (what if new node?)
}

/**************************************************************
 * 		HashtagProcessor::GetMostFrequentHashtags
 **************************************************************/
string HashtagProcessor::GetMostFrequentHashtags(int numHashtags)
{
    /*  Get numHashtags most freqeunct hashtags from fibheap (n removeMax)
     *  create string of the hashtags
     *  insert n hashtags to fibheap
     */
}

/**************************************************************
 * 		HashtagProcessor::ProcessQuery
 **************************************************************/
void HashtagProcessor::ProcessQuery(int numHashtags)
{
    // calls GetMostFrequenctHashtags
    // sends the string to query writer
}





