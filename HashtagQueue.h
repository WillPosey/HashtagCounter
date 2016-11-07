/******************************************************************************************
 * 		HashtagQueue.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      The HashtagQueue encapsulates a queue of strings,
 *      and allows synchronization between a queue writer and reader through a mutex
 ******************************************************************************************/
#ifndef HASHTAG_QUEUE_H
#define HASHTAG_QUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

/* HashtagQueue Class */
class HashtagQueue
{
public:
    /**********************************************************
     *      HashtagQueue Constructor
     **********************************************************/
    HashtagQueue(){moreData = true;}

    /**********************************************************
     *      HashtagQueue Copy Constructor
     **********************************************************/
    HashtagQueue(const HashtagQueue& copyQ){moreData = copyQ.moreData;}

    /**********************************************************
     *      HashtagQueue::ReadQueue
     *
     *      Reads the front of the queue
     **********************************************************/
    bool ReadQueue(string& tagEntry)
    {
        /* Indicate that writer has already completed */
        if(!moreData)
            return false;

        /* Acquire queue lock */
        queueMutex.lock();

        /* Wait for writer to insert to the queue */
        while(hashtagQueue.empty())
        {
            queueMutex.unlock();
            this_thread::sleep_for(chrono::seconds(1));
            queueMutex.lock();
        }

        /* Get the hashtag, query number, or stop indicator from the front of the queue */
        tagEntry = hashtagQueue.front();
        hashtagQueue.pop();

        /* If this is the writer stop indicator, return false */
        if(tagEntry.compare("stop") == 0 || tagEntry.compare("STOP") == 0)
            moreData = false;

        /* Give up lock and return status */
        queueMutex.unlock();
        return moreData;
    }

    /**********************************************************
     *      HashtagQueue::WriteQueue
     *
     *      Writes to the back of the queue
     **********************************************************/
    void WriteQueue(string tagEntry)
    {
        /* Acquire lock, write next entry, give up lock */
        queueMutex.lock();
        hashtagQueue.push(tagEntry);
        queueMutex.unlock();
    }

private:
    /* Members */
    queue<string> hashtagQueue; /* queue used for hastags, queries, and stop indicator */
    mutex queueMutex;           /* mutex used for reader and writer synchronization */
    bool moreData;              /* flag for stop indicator encounter */
};

#endif /* HASHTAG_QUEUE_H */

