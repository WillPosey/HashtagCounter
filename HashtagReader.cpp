/******************************************************************************************
 * 		HashtagReader.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class is used to read an input file containing hashtags and hastag frequencies,
 *      queries for most used hashtags, and a stop indictor, and write all to a HashtagQueue
 *      for processing
 ******************************************************************************************/
#include "HashtagReader.h"

#include <iostream>
#include <functional>

/******************************************************************
 * 		HashtagReader Constructor
 *
 *      Open an input stream with the input file
 *      Start and detach a thread to read through the file and write
 *      to a queue, which is read by the HashtagProcessor
 ******************************************************************/
HashtagReader::HashtagReader(string inputFilename, HashtagQueue& tagQ)
{
    inStream.open(inputFilename.c_str());
    readThread = thread(&HashtagReader::ReadHashtags, this, ref(tagQ));
    readThread.detach();
}

/**************************************************************
 * 		HashtagReader::ReadHashtags
 *
 *      Thread method, read through each line in the input stream
 *      and write to the queue
 **************************************************************/
void HashtagReader::ReadHashtags(HashtagQueue& tagQueue)
{
    string line;
    while(getline(inStream, line))
        tagQueue.WriteQueue(line);
    inStream.close();
}




