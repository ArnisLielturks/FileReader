#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string>
using namespace std;

struct AwesomeFileHeader {
    int ID;
    char name[40];
    float width;
    float height;
};

struct AwesomeFileBody {
    float x;
    float y;
    float z;
};

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
};
