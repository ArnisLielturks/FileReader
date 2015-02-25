#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileReader {
public:
    //We will open file in constructor
    FileReader(const std::string filename);
    ~FileReader();

    //Read the actual data from the file
    void ReadValues();
private:
    ifstream _file;
};
