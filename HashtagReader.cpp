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

/**************************************************************
 * 		HashtagReader Constructor
 **************************************************************/
HashtagReader::HashtagReader(string inputFilename, HashtagQueue tagQ) : tagQueue(tagQ)
{
    inStream.open(inputFilename.c_str());
    readThread = thread(&HashtagReader::ReadHashtags, this);
}

/**************************************************************
 * 		HashtagReader::ReadHashtags
 **************************************************************/
void HashtagReader::ReadHashtags()
{
    string line;
    while(getline(inStream, line))
        tagQueue.WriteQueue(line);
    inStream.close();
}




