#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

#define AWS_NAME_SIZE 60


//Struct size should be dividable by 4
struct AwesomeFileHeader {
    int ID;
    char name[AWS_NAME_SIZE];
    float width;
    float height;
    int verticeCount;
};

#define BYTE_AWS sizeof(AwesomeFileHeader)
#define BYTE_AWS_NAME sizeof(char[AWS_NAME_SIZE])
#define BYTE_INT 4
#define BYTE_FLOAT 4

struct AwesomeFileBody {
    float x;
    float y;
    float z;
};

#define BYTE_AWS_BODY sizeof(AwesomeFileBody)

class BinaryFileReader
{
public:
    BinaryFileReader(const std::string filename);
    ~BinaryFileReader();

    void ReadValues();

    //Store some binary data for testing
    void SaveValues();
private:
    fstream _file;

    char _readInt[4];
    char _readFloat[4];

    void storeInt(char intByte, int pos);
    void storeFloat(char intByte, int pos);
};
