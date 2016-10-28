/******************************************************************************************
 * 		HashtagQueue.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      The MIPS_Buffer template class encapsulates a queue of the template type,
 *      and allows synchronization between a buffer writer and reader through a semaphore
 ******************************************************************************************/
#ifndef HASHTAG_QUEUE_H
#define HASHTAG_QUEUE_H

#include <string>
#include <queue>
#include <mutex>

using namespace std;

class HashtagQueue
{
public:
    // Constructor
    HashtagQueue(){moreData = true;}

    // Reads the front of the queue
    bool ReadQueue(string& tagEntry)
    {
        if(!moreData)
            return false;

        queueMutex.lock();

        while(hashtagQueue.empty());

        tagEntry = hashtagQueue.front();
        hashtagQueue.pop();

        if(tagEntry.compare("stop") == 0)
            moreData = false;

        queueMutex.unlock();
        return moreData;
    }

    // Writes to the back of the queue
    void WriteQueue(string tagEntry)
    {
        queueMutex.lock();
        hashtagQueue.push(tagEntry);
        queueMutex.unlock();
    }

private:
    queue<string> hashtagQueue;
    mutex queueMutex;
    bool moreData;
};

#endif /* HASHTAG_QUEUE_H */

