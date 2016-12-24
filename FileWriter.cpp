//
// Created by ahmed on 12/18/16.
//

#include <cstring>
#include "FileWriter.h"


FileWriter::FileWriter(char *inp_file_name)
{
    this->file_name = string(inp_file_name);

    // TODO use exceptions
//    try
//    {
//        // Just checking if the file exists
//        out_file.open(this->file_name, ios::in);
//    }
//    catch (exception &exc)
//    {
//        cout << "Unable to open the file, " << exc.what() << endl;
//    }

    out_file.open(this->file_name, ios::binary);
    if (!out_file.is_open()) {
        fprintf(stderr, "Failed to open file");

        return;
    }
    out_file.close();
}

void FileWriter::Write(void *buffer, unsigned int size)
{
    if (!out_file.is_open()) {
        out_file.open(this->file_name, ios::app | ios::binary);
    }
    out_file.write((char *) buffer, size);
    out_file.close();

}

FileWriter::~FileWriter()
{
    if (out_file.is_open()) {
        cout << "File writer flushed" << endl;
        out_file.close();
    }
}