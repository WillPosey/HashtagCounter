/******************************************************************************************
 * 		HaashtagReader.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#ifndef HASHTAG_READER_H
#define HASHTAG_READER_H

#include "HashtagQueue.h"

#include <fstream>
#include <string>
#include <thread>

class HashtagReader
{
public:
    HashtagReader(string inputFilename, HashtagQueue& tagQ);
    void ReadHashtags(HashtagQueue& tagQ);
private:
    ifstream inStream;
    thread readThread;
};

#endif /* HASHTAG_READER_H */




