/**********************************************************************************
 * 		QueryWriter.h
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This class is used to write results from a query for
 *      the most frequenct occuring hashtags out of an input file
 **********************************************************************************/
#ifndef QUERY_WRITER_H
#define QUERY_WRITER_H

/* Definition for the output file name */
#define OUTPUT_FILENAME "output_file.txt"

#include <fstream>
#include <string>

/* QueryWriter class */
class QueryWriter
{
public:
    /**********************************************************
     *      QueryWriter Constructor
     **********************************************************/
    QueryWriter()
    {
        outStream.open(OUTPUT_FILENAME);
    }

    /**********************************************************
     *      QueryWriter::WriteToFile
     **********************************************************/
    void WriteToFile(string queryResult)
    {
        outStream << queryResult << endl;
    }

    /**********************************************************
     *      QueryWriter::CloseFile
     **********************************************************/
    void CloseFile()
    {
        outStream.close();
    }

private:
    /* Members */
    ofstream outStream; /* output stream */
};

#endif /* QUERY_WRITER_H */



