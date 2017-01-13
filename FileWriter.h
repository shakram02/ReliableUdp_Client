//
// Created by ahmed on 12/18/16.
//

#ifndef ENHANCEDUDPCLIENT_FILERECEIVER_H
#define ENHANCEDUDPCLIENT_FILERECEIVER_H

#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

class FileWriter
{
public:
    /**
     * Manages writing to file and writing big files
     * @param inp_file_name
     */
    FileWriter(string &inp_file_name);

    /**
     * Writes an array of bytes to the file
     * @param buffer bytes to write
     */
    void Write(std::vector<unsigned char> &buffer);

    void Close();

    /**
     * Disposes the FileWrite allocated resources
     */
    ~FileWriter();

private:
    ofstream out_file;
    string file_name;
};


#endif //ENHANCEDUDPCLIENT_FILERECEIVER_H
