#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//Define the structure of the file line - order of elements and data types
#define FILE_DATA_TYPES FileValue<string, int, float, bool>

template<class A, class B, class C, class D>
struct FileValue
{
    A name;
    B age;
    C weight;
    D student;
};

class FileReader {
public:
    //We will open file in constructor
    FileReader(const std::string filename);
    ~FileReader();

    //Read the actual data from the file
    void ReadValues();

    vector<FILE_DATA_TYPES> getData();
private:
    ifstream _file;
    //Vector of file data with data types declared
    vector<FILE_DATA_TYPES> _data;
};
