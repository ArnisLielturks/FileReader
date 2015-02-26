#include "BinaryFileReader.h"

//ctor
BinaryFileReader::BinaryFileReader(const std::string filename)
{
    _file.open(filename.c_str(), ios::binary | ios::in | ios::out);
}

//dtor
BinaryFileReader::~BinaryFileReader()
{
}

void BinaryFileReader::ReadValues()
{

    if(_file.is_open()) {
        //Go to the beggining of the file
        _file.seekg(0);
        char number;
        while(_file.good() && !_file.eof()) {
            //Read char from the file
            if(_file.get(number))
                cout << "number : " << (int)number << endl;
        }
    } else {
        cout << "Error while openning file!" << endl;
    }
}

void BinaryFileReader::SaveValues()
{
    if(_file.is_open()) {
        //Store integer values from 0 - 9 in file
        for(int i = 0; i < 10; i++) {
            _file.put(i);
        }
    } else {
        cout << "Error while openning file" << endl;
    }
}
