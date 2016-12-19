//
// Created by ahmed on 12/18/16.
//

#include <cstring>
#include "FileWriter.h"


FileWriter::FileWriter(char *fileName)
{
    this->fileName = (char *) malloc(strlen(fileName) + 1);
    strcpy(this->fileName, fileName);

    // TODO use exceptions
//    try
//    {
//        // Just checking if the file exists
//        outFile.open(this->fileName, ios::in);
//    }
//    catch (exception &exc)
//    {
//        cout << "Unable to open the file, " << exc.what() << endl;
//    }

    outFile.open(this->fileName, ios::in);
    if (!outFile.is_open())
    {
        fprintf(stderr, "Failed to open file");

        return;
    }
    outFile.close();
}

void FileWriter::Write(char *buffer)
{
    if (!outFile.is_open())
    {
        outFile.open(this->fileName, ios::app | ios::binary);
    }
    outFile.write(buffer, strlen(buffer));
    outFile.close();

}

FileWriter::~FileWriter()
{
    free(this->fileName);
}