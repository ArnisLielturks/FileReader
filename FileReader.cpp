#include "FileReader.h"

//Ctor
FileReader::FileReader(const std::string filename)
{
    _file.open(filename.c_str());
}

//Dtor
FileReader::~FileReader()
{
}

//Read the data from the file
void FileReader::ReadValues()
{
    std::string name, line;
    int age;
    float weight;
    bool student;

    cout << "NAME\t\tAGE\t\tWEIGHT\t\tSTUDENT" << endl << endl;

    while(getline(_file, line)) {
        //Clear the previously set values
        name.clear();
        age = 0;
        weight = 0.0f;
        student = false;

        std::stringstream ss(line);

        //Read the first value from the line
        ss >> name;

        // If the line starts with '#' or if it's an empty line, skip that line
        if (name.compare(0, 1, "#") == 0 || name.empty()) {
            continue;
        }


        //Read "age" value from the line
        ss >> age;
        //Read "weight" value from the line
        ss >> weight;
        //Read "student" value from the line
        ss >> student;

        cout << name << "\t\t" << age << "\t\t" << weight << "\t\t" << student << endl;

    }
}
