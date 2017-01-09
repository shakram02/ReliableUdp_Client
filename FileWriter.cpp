//
// Created by ahmed on 12/18/16.
//

#include <cstring>
#include <vector>
#include "FileWriter.h"
#include "globaldefs.h"

FileWriter::FileWriter(string &inp_file_name)
{
    this->file_name = inp_file_name;

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
#if LOG >= 1
        fprintf(stderr, "Failed to open file");
#endif

        return;
    }
    out_file.close();
}

void FileWriter::Write(std::vector<unsigned char> &buffer)
{

    if (!out_file.is_open()) {
        out_file.open(this->file_name, ios::app | ios::binary);
    }
    for (auto i = buffer.begin(); i != buffer.end(); ++i) {
        out_file << *i;
    }

    // out_file.close();    // Should i close the file ?

}

FileWriter::~FileWriter()
{
    if (out_file.is_open()) {
        {
            out_file.close();
        }
#if LOG >= 2
        cout << "File writer flushed" << endl;
#endif
    }
}