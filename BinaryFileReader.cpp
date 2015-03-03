#include "BinaryFileReader.h"

//ctor
BinaryFileReader::BinaryFileReader(const std::string filename)
{
    _file.open(filename.c_str(), ios::binary | ios::in | ios::out);
}

//dtor
BinaryFileReader::~BinaryFileReader()
{
    _file.close();
}

void BinaryFileReader::ReadValues()
{

    if(_file.is_open()) {
        //Go to the beggining of the file
        _file.seekg(0);
        char number;
        int i = 0;
        while(_file.good() && !_file.eof()) {
            //Read char from the file
            if(_file.get(number))
                i++;
                cout << "number : " << number << endl;
                // if (i == setOutFile)
                    // return;
                saveOutFile(number);
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

void BinaryFileReader::setOutFile(const std::string filename)
{
    _ofile.open(filename.c_str(), ios::binary | ios::in | ios::out | ios::trunc);
}

void BinaryFileReader::saveOutFile(char info)
{
    if(_ofile.is_open()) {
        int x = info;
        if (x == 25) {
            x = 100;
        }
        _ofile.put(x);
    }
}
