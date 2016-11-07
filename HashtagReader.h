/******************************************************************************************
 * 		HashtagReader.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class is used to read an input file containing hashtags and hastag frequencies,
 *      queries for most used hashtags, and a stop indictor, and write all to a HashtagQueue
 *      for processing
 ******************************************************************************************/
#ifndef HASHTAG_READER_H
#define HASHTAG_READER_H

#include "HashtagQueue.h"

#include <fstream>
#include <string>
#include <thread>

/* HashtagReader Class */
class HashtagReader
{
public:
    /* Constructor */
    HashtagReader(string inputFilename, HashtagQueue& tagQ);

    /* Thread method, reads in every line from input file */
    void ReadHashtags(HashtagQueue& tagQ);

private:
    /* Members */
    ifstream inStream;  /* input stream */
    thread readThread;  /* thread to run ReadHashtags */
};

#endif /* HASHTAG_READER_H */




