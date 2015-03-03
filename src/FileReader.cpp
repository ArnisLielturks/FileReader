#include "../includes/FileReader.h"

//Ctor
FileReader::FileReader(const std::string filename)
{
    _file.open(filename.c_str());
}

//Dtor
FileReader::~FileReader()
{
    _file.close();
}

//Read the data from the file
void FileReader::ReadValues()
{
    std::string line;

    while(getline(_file, line)) {
        //Clear the previously set values

        FILE_DATA_TYPES parse;
        parse.name.clear();
        parse.age = 0;
        parse.weight = 0.0f;
        parse.student = false;


        std::stringstream ss(line);

        //Read the first value from the line
        ss >> parse.name;

        // If the line starts with '#' or if it's an empty line, skip that line
        if (parse.name.compare(0, 1, "#") == 0 || parse.name.empty()) {
            continue;
        }

        //Read "age" value from the line
        ss >> parse.age;
        //Read "weight" value from the line
        ss >> parse.weight;
        //Read "student" value from the line
        ss >> parse.student;

        _data.push_back(parse);

    }
}

vector<FILE_DATA_TYPES> FileReader::getData()
{
    return _data;
}
