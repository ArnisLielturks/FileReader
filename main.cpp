#include "FileReader.h"

int main()
{
	FileReader reader("example.dat");
	reader.ReadValues();
	vector< FILE_DATA_TYPES > data = reader.getData();

	//Output data to screen
	cout << "Name\t\tAge\t\tWeight\t\tStudent" << endl << endl;
	for (int i = 0; i < data.size(); i++) {
		cout << data.at(i).name << "\t\t" << data.at(i).age << "\t\t" << data.at(i).weight << "\t\t" << data.at(i).student << endl;
	}
	return 0;
}
