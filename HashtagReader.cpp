/******************************************************************************************
 * 		HaashtagReader.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#include "HashtagReader.h"

#include <iostream>
#include <functional>

/**************************************************************
 * 		HashtagReader Constructor
 **************************************************************/
HashtagReader::HashtagReader(string inputFilename, HashtagQueue& tagQ)
{
    inStream.open(inputFilename.c_str());
    readThread = thread(&HashtagReader::ReadHashtags, this, ref(tagQ));
    readThread.detach();
}

/**************************************************************
 * 		HashtagReader::ReadHashtags
 **************************************************************/
void HashtagReader::ReadHashtags(HashtagQueue& tagQueue)
{
    string line;
    while(getline(inStream, line))
        tagQueue.WriteQueue(line);
    inStream.close();
}




