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

#define OUTPUT_FILENAME "output_file.txt"

#include <fstream>
#include <string>

class QueryWriter
{
public:
    QueryWriter(){outStream.open(OUTPUT_FILENAME);}
    WriteToFile(string queryResult){outStream << queryResult;}
    CloseFile(){outStream.close();}
private:
    ofstream outStream;
};

#endif /* QUERY_WRITER_H */



