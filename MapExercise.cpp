#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h> // for floor
using namespace std;

const bool DEBUG = true;

int main() {

	// 1. Look at data file for a pattern
	int value; float precip;
	map<int, vector<int>> temperature;

	// 2. open file for input
	ifstream infile;
	infile.open("tempAndPrecip.txt", ios_base::in);

	// 3. Check to see if file opened
	if (infile.fail())
	{
		cout << "The File was not successfully open." << endl;
		exit(1); // ends ENTIRE program!!!
	}

	// 4. read in the data
	//5.  Read in data from file
	while (infile >> value >> precip) // this command is IMPORTANT!
	{
		if(DEBUG) { cout << "read values: " << value << " " << precip << endl; }

		// gather value for key
		int stem = floor(value/10);
        int leaf = value - (stem*10);

		if (temperature.find(stem) == temperature.end())
		{
			temperature.insert(pair<int, vector<int>>(stem, vector<int>()));
			temperature[stem].push_back(value%10);
		}
		else
		{
			temperature[stem].push_back(value%10);
		}

		cout << value << endl;
	}

	// 5. close the file
	infile.close();

	map<int,vector<int>>::iterator itr;

	for(itr = temperature.begin(); itr != temperature.end(); itr++)
	{
        cout<<itr->first<<" ->";
        for(int i = 0; i < itr->second.size(); i++)
        { cout<<" "<<itr->second[i]; }
        cout<<endl;
	}

	return 0;
}
