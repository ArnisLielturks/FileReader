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
        int k = 0;
        char single_char;
        char id[4];
        char *title = new char[AWS_NAME_SIZE];
        char size[4];
        char size2[4];
        char vCount[4];

        char temp[4];

        cout << "name sizeof " << BYTE_AWS_NAME << endl;
        while(_file.good() && !_file.eof()) {
            //Read char from the file
            if(_file.get(single_char)) {

                if (i < BYTE_INT) {
                    // id[i] = single_char;
                    storeInt(single_char, i);
                    // cout << "Reading int byte" << endl;

                } else if (i < BYTE_INT + BYTE_AWS_NAME) {
                    title[i - BYTE_INT] = single_char;
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT) {
                    storeFloat(single_char, i - (BYTE_INT + BYTE_AWS_NAME));
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2) {
                    storeFloat(single_char, i - (BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT));
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2 + BYTE_INT) {
                    storeInt(single_char, i - (BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2));
                } else {
                    // cout << "K " << k << endl;
                    // temp[k] = single_char;
                    storeFloat(single_char, k);
                    k++;
                    if (k > 3) {
                        k = 0;
                    //     float *t = (float*)temp;
                    //     cout << "Reading vector value " << *t << endl;
                    }
                }
                i++;
            }
        }

        //Convert from char array to int/float
  //       int *result = (int*)id;
  //       float *result2 = (float*)size;
  //       float *result3 = (float*)size2;
        string obj_name = string(title);
  //       int *vertCount = (int*)vCount;
  //       cout << "ID         :" << *result << endl;
        cout << "Name       :" << obj_name << endl;
  //       cout << "width      :" << *result2 << endl;
  //       cout << "height     :" << *result3 << endl;
  //       cout << "vertice count : " << *vertCount << endl;
    } else {
        cout << "Error while openning file!" << endl;
    }
}

void BinaryFileReader::storeInt(char intByte, int pos)
{
    _readInt[pos] = intByte;
    if (pos == 3) {
        int *t = (int*)_readInt;
        cout << "Int ready --- " << *t << endl;
    }
}

void BinaryFileReader::storeFloat(char intByte, int pos)
{
    _readFloat[pos] = intByte;
    if (pos == 3) {
        float *t = (float*)_readFloat;
        cout << "Float ready --- " << *t << endl;
    }
}

void BinaryFileReader::SaveValues()
{
    if(_file.is_open()) {
        //New struct
        AwesomeFileHeader header;
        //Add some data to the struct
        header.ID = 1991;

        string name = "Oops! I didnt want this to happen Im really sorry. HA!";
        for(int i = 0; i < BYTE_AWS_NAME - 1; i++) {
            if (i < name.size() - 1) {
                header.name[i] = name[i];
            } else {
                header.name[i] = '\0';
            }
        }

        //Add the string ending char
        header.name[BYTE_AWS_NAME - 1] = '\0';

        header.width = 222.2f;
        header.height = 333.3f;

        header.verticeCount = 10;
        char *data = new char[BYTE_AWS];
        memcpy(data, &header, BYTE_AWS);
        cout << "File size " << BYTE_AWS << endl;

        for(int i = 0; i < BYTE_AWS; i++) {
            _file.put(data[i]);
            // cout << data[i] << endl;
        }

        //Append body
        AwesomeFileBody tempBody;
        tempBody.x = 3.1;
        tempBody.y = 4.1;
        tempBody.z = 5.1;
        char *body = new char[BYTE_AWS_BODY];
        memcpy(body, &tempBody, BYTE_AWS_BODY);
        for (int k = 0; k < 4; k++) {
            for(int i = 0; i < BYTE_AWS_BODY; i++) {
                _file.put(body[i]);
                // cout << body[i] << endl;
            }
        }

    } else {
        cout << "Error while openning file" << endl;
    }
}
