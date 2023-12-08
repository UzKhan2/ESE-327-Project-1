#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include<fstream>
#include<algorithm>


using namespace std;


vector<string> string_split(string str);
vector<string> get_artributes();
vector<string> scan_database();


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
		std::cout << temp << std::endl;
		artributes.push_back(temp);
	}

	return artributes;
}


vector<string> scan_database() {
	string fileName;
	fstream inFile;
	vector<string> database;
	cout << "Please enter a database file directory: ";
	cin >> fileName;
	inFile.open(fileName, 'r');

	if (!inFile) {
		cerr << "Can not open the file " << fileName << endl;
		exit(1);
	}


	return database;


}


int main() {
	vector<string> artributes;


	get_artributes();
	scan_database();


	return 0;
}
