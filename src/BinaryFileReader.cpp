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

        //Which byte we are reading from Awesome File Body
        int byteNum = 0;
        //Which value we are reading X,Y,Z from Awesome File Body
        int valueNum = 0;

        char single_char;
        char *title = new char[AWS_NAME_SIZE];

        char temp[4];
        AwesomeFileHeader awesome;
        AwesomeFileBody awesomeBody;
        cout << "name sizeof " << BYTE_AWS_NAME << endl;
        while(_file.good() && !_file.eof()) {
            if(_file.get(single_char)) {

                if (i < BYTE_INT) {
                    //Read the ID
                    storeInt(single_char, i, awesome.ID);
                } else if (i < BYTE_INT + BYTE_AWS_NAME) {
                    //Read the title
                    awesome.name[i - BYTE_INT] = single_char;
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT) {
                    //Read the width
                    storeFloat(single_char, i - (BYTE_INT + BYTE_AWS_NAME), awesome.width);
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2) {
                    //Read the height
                    storeFloat(single_char, i - (BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT), awesome.height);
                } else if (i < BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2 + BYTE_INT) {
                    //Read the vertice count
                    storeInt(single_char, i - (BYTE_INT + BYTE_AWS_NAME + BYTE_FLOAT * 2), awesome.verticeCount);
                } else {
                    //Store float value after each 4 bytes
                    float t;
                    storeFloat(single_char, byteNum, t);
                    byteNum++;
                    if (byteNum > 3) {
                        byteNum = 0;

                        switch(valueNum) {
                            case 0:
                                awesomeBody.x = t;
                                break;
                            case 1:
                                awesomeBody.y = t;
                                break;
                            case 2:
                                awesomeBody.z = t;
                                break;
                        }
                        valueNum++;

                        //After 3 float values update vertice vector
                        if (valueNum > 2) {
                            _vertices.push_back(awesomeBody);
                            valueNum = 0;
                        }
                    }
                }
                i++;
            }
        }

        string obj_name = string(awesome.name);
        cout << "ID         : " << awesome.ID << endl;
        cout << "Name       : " << obj_name << endl;
        cout << "Width      : " << awesome.width << endl;
        cout << "Height     : " << awesome.height << endl;
        cout << "Vertices   : " << awesome.verticeCount << endl;
        cout << "================" << endl;
        for(int i=0; i < _vertices.size(); i++) {
            cout << "Vertice [" << _vertices.at(i).x << ",\t\t" << _vertices.at(i).y << ",\t\t" << _vertices.at(i).z << "]" << endl;
        }

    } else {
        cout << "Error while openning file!" << endl;
    }
}

void BinaryFileReader::storeInt(char intByte, int pos, int &value)
{
    _readInt[pos] = intByte;
    if (pos == 3) {
        int *t = (int*)_readInt;
        value = *t;
        // cout << "Int ready --- " << *t << endl;
    }
}

void BinaryFileReader::storeFloat(char intByte, int pos, float &value)
{
    _readFloat[pos] = intByte;
    if (pos == 3) {
        float *t = (float*)_readFloat;
        value = *t;
        // cout << "Float ready --- " << *t << endl;
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
        for (int k = 0; k < 4; k++) {
            for(int i = 0; i < BYTE_AWS_BODY; i++) {
                AwesomeFileBody tempBody;
                tempBody.x = k * i * 0.5f;
                tempBody.y = k + i + 0.2f;
                tempBody.z = k + i + 0.5f;
                char *body = new char[BYTE_AWS_BODY];
                memcpy(body, &tempBody, BYTE_AWS_BODY);
                _file.put(body[i]);
                // cout << body[i] << endl;
            }
        }

    } else {
        cout << "Error while openning file" << endl;
    }
}
