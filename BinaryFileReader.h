#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

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
