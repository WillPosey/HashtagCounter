/*******************************************************************************************************
 * 		HashtagCounter.cpp
 *
 *      Author: William Posey
 *      Course: COP 5536
 *      Project: HashtagCounter
 *
 *      This program reads hashtags and corresponding frequencies of their use from an input file
 *      and stores them in a hash table and max fibonacci heap, respectively. The input file also
 *      queries for the n most frequent hashtags at that point, which are read from the max fibonacci heap
 *      and written to an output file
 *******************************************************************************************************/

 // Created Header Files
#include "HashtagReader.h"
#include "HashtagQueue.h"
#include "HashtagProcessor.h"

// System Header Files
#include <string>
#include <iostream>
#include <sys/stat.h>

using namespace std;

/**************************************************************
 * 		HashtagCounter Main Method
 **************************************************************/
int main(int argc, char** argv)
{
    // Make sure input filename supplied
    if(argc != 2)
    {
        cout << "ERROR: Please indicate the input file name" << endl;
        return 0;
    }

    // Make sure input file exists
    struct stat buffer;
    if(stat (argv[1], &buffer) != 0)
    {
        cout << "ERROR: Please supply an existing input file" << endl;
        return 0;
    }

    HashtagQueue tagQueue;                          // Queue used for reader and writer synchronization
    HashtagReader tagReader (argv[1], tagQueue);    // Construct HashtagReader and start thread
    HashtagProcessor tagProcessor (tagQueue);       // Construct HashtagProcessor
    tagProcessor.StartProcessing();                 // Process Hashtag frequencies and queries

	return 0;
}



