/******************************************************************************************
 * 		QueryWriter.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *
 ******************************************************************************************/
#ifndef QUERY_WRITER_H
#define QUERY_WRITER_H

#include "HashtagQueue.h"

#include <string>
#include <thread>

class QueryWriter
{
public:
    QueryWriter(string inputFilename, HashtagQueue tagQueue){filename = inputFilename; writeQueue = tagQueue;}

private:
    string filename;
    HashtagQueue writeQueue;
};

#endif /* QUERY_WRITER_H */



