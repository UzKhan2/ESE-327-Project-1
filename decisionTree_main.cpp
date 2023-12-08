#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include<fstream>
#include<algorithm>


using namespace std;


vector<string> string_split(string str);
vector<string> get_artributes();
vector<vector<string>> scan_database();
void print_database(vector<vector<string>> database);
bool digitCheck(string str);


vector<string> get_artributes() {

	string str;
	vector<string> artributes;

	cout << "Please enter all the artributes of the dataset (Seperate each artribute with a comma): ";
	getline(cin, str);
	artributes = string_split(str);	

	return artributes;

}


vector<string> string_split(string str) {
	
	vector<string> artributes;
	string temp;

	std::istringstream iss(str);
	while (getline(iss, temp, ',')) {
		artributes.push_back(temp);
	}

	return artributes;
}


vector<vector<string>> scan_database() {
	string fileName;
	fstream inFile;
	vector<vector<string>> database;
	cout << "Please enter a database file directory: ";
	cin >> fileName;
	inFile.open(fileName);

	if (!inFile) {
		cerr << "Can not open the file " << fileName << endl;
		exit(1);
	}

	string line, temp;
	int i = 0;
	while (getline(inFile, line))
	{
		database.resize(database.size() + 1);
		std::istringstream iss(line);
		database[i].resize(5);
		while (getline(iss, temp, ',')) {
			database[i].push_back(temp);
		}
		i++;
	}
	return database;
}


void print_database(vector<vector<string>> database) {
	for (int i = 0; i < database.size(); i++)
	{
		for (int j = 0; j < database[i].size(); j++)
		{
			cout << database[i][j] << ' ';
		}
		cout << endl;
	}

}

bool digitCheck(string str) {
	bool digit = true;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]) == 0)
			return false;
	}
	return true;
}


int main() {
	vector<string> artributes;
	vector<vector<string>> database;
 
	//artributes = get_artributes();
	//database = scan_database();
	//print_database(database);



	return 0;
}
