#include "../includes/BinaryFileReader.h"

//ctor
BinaryFileReader::BinaryFileReader(const std::string filename)
{
    _file.open(filename.c_str(), ios::binary | ios::in | ios::out | ios::trunc);
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
        int i = 0;
        char single_char;
        char id[4];
        char *title = new char[sizeof(AwesomeFileHeader().name)];
        char size[4];
        char size2[4];
        cout << "name sizeof " << sizeof(AwesomeFileHeader().name) << endl;
        while(_file.good() && !_file.eof()) {
            //Read char from the file
            if(_file.get(single_char)) {

                if (i < sizeof(int)) {
                    id[i] = single_char;
                    cout << "Reading int byte" << endl;

                } else if (i < sizeof(int) + sizeof(AwesomeFileHeader().name)) {
                    title[i - sizeof(int)] = single_char;
                    cout << "Reading string byte " << i - sizeof(int) << endl;

                } else if (i < sizeof(int) + sizeof(AwesomeFileHeader().name) + sizeof(float)) {
                    size[i - (sizeof(int) + sizeof(AwesomeFileHeader().name))] = single_char;
                    cout << "Reading float byte 1" << endl;
                } else if (i < sizeof(int) + sizeof(AwesomeFileHeader().name) + sizeof(float) * 2) {
                    size2[i - (sizeof(int) + sizeof(AwesomeFileHeader().name) + sizeof(float))] = single_char;
                    cout << "Reading float byte 2" << endl;
                }
                i++;
            }
        }

        //Convert from char array to int/float
        int *result = (int*)id;
        float *result2 = (float*)size;
        float *result3 = (float*)size2;
		string obj_name = string(title);
        cout << "ID         :" << *result << endl;
        cout << "Name       :" << obj_name << endl;
        cout << "width      :" << *result2 << endl;
        cout << "height     :" << *result3 << endl;
    } else {
        cout << "Error while openning file!" << endl;
    }
}

void BinaryFileReader::SaveValues()
{
    if(_file.is_open()) {
        //New struct
        AwesomeFileHeader header;
        //Add some data to the struct
        header.ID = 1991;

        string name = "Oops!";
        for(int i = 0; i < sizeof(AwesomeFileHeader().name) - 1; i++) {
			if (i < name.size()) 
				header.name[i] = name[i];
        }

        //Add the string ending char
        header.name[sizeof(AwesomeFileHeader().name) - 1] = '\0';

        header.width = 222.2f;
        header.height = 333.3f;
        char *data = new char[sizeof(AwesomeFileHeader)];
        memcpy(data, &header, sizeof(AwesomeFileHeader));
        cout << "File size " << sizeof(AwesomeFileHeader) << endl;

        for(int i = 0; i < sizeof(AwesomeFileHeader); i++) {
            _file.put(data[i]);
            cout << data[i] << endl;
        }
    } else {
        cout << "Error while openning file" << endl;
    }
}
