#include "../includes/FileReader.h"
#include "../includes/BinaryFileReader.h"

int main()
{
	//############## TEXT FILE READER ##############
	FileReader reader("example.dat");
	reader.ReadValues();
	vector< FILE_DATA_TYPES > data = reader.getData();

	//Output data to screen
	cout << "Name\t\tAge\t\tWeight\t\tStudent" << endl << endl;
	for (int i = 0; i < data.size(); i++) {
		cout << data.at(i).name << "\t\t" << data.at(i).age << "\t\t" << data.at(i).weight << "\t\t" << data.at(i).student << endl;
	}

	cout << endl << "-------" << endl << endl;

	//############## BINARY FILE READER ##############

	BinaryFileReader reader2("example_binary.bin");
	reader2.SaveValues();
	reader2.ReadValues();

	return 0;
}
