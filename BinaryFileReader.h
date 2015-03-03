#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BinaryFileReader
{
public:
	BinaryFileReader(const std::string filename);
	~BinaryFileReader();

	void setOutFile(const std::string filename);
	void ReadValues();

	//Store some binary data for testing
	void SaveValues();

	void saveOutFile(char info);
private:
	fstream _file;
	fstream _ofile;
};
