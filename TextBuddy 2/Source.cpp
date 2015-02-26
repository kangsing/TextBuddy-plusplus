// Author: Kang Sing
// Matric card: A0114411B
//
// **********ASSUMPTIONS AND FUNCTIONALITIES**********
// Assuming the user input would be all valid.
// E.g. Typing a number after the command "delete".
//
// If user tries to delete items when the list is empty, programme will show error message.
// If user tries to delete items out of the list, programme will show error message.
// This is a project to create a text file based on user input 
// The program will take in and store sentences by updating the text file.
// 
// Functions:
// Add, Delete, Clear, Display, Sort, Search, Exit
// 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

string fileName= "";

void createFile(string fileName);
vector<string> extractData(vector<string> file);
vector<string> updateFile(vector<string> file);
void commandAdd();
string commandDisplay(vector<string> file);
void commandDelete();
void commandClear();
vector<string> commandSort(vector<string> file);
string commandSearch(vector<string> file, string searchString);
void printMessageSuccessAdd (string inputline);
void printMessageSuccessDelete(string deleteString);
void printMessageSuccessSort();
void printMessageError(int errorNumber);
void printMessageClear();
void printMessageWelcome();
void printMessageCommand();
string readCommand(string command);
void performCommand();

int main(int argc, char* argv[]){
	cout << "c:>";
	if(argc==2){	
		fileName = argv[1];
		createFile(fileName);
	}

	printMessageWelcome();
	printMessageCommand();
	performCommand();

	return 0;
}

void createFile(string fileName){
	ofstream writeFile(fileName);
		writeFile.close();
}

// This function extracts exisitng file's data into vector "file"
// and returns a vector of strings.
vector<string> extractData(vector<string> file){

	string data;
	ifstream extract(fileName);
	while(getline(extract,data)){
		file.push_back(data);
	}
	extract.close();

	return file;
}

// This function opens exisitng file and updates it with new information.
vector<string> updateFile(vector<string> file){
	ofstream add(fileName);	
	int i=0;
	int size=file.size();

	while(size > 0){
		add << file[i] << endl;
		i++; 
		size--;
	}

	add.close();
	file.clear();
	return file;
}

// This function adds a new piece of information to 
// the destination file. 
void commandAdd(){
	vector <string> file;
	string inputline;
	getline(cin,inputline);
		
	//Removing the extra whitespace infront
	inputline = inputline.substr(1,inputline.length()); 
	
	file = extractData(file);
	file.push_back(inputline);
	printMessageSuccessAdd(inputline);

	file = updateFile(file);
	file.clear();
}

// This function displays all exisitng contents in the file.
// This function takes in vector of strings and return a string to be cout.
string commandDisplay(vector<string> file){
	
	//Printing the contents in the format of
	//1. <content #1>
	//2. <content #2>
	int counter=1;
	ostringstream oss;
	for(int i=0 ; i!=file.size() ; i++){
		oss << counter << ". ";
		oss << file[i] << endl;
		counter++;
	}

	//Error #3 tells user that file is empty.
	if(file.empty()){
		printMessageError(3); 
	}
	file.clear();

	return oss.str();
}

// This function deletes the specific information specify by the user input. 
// It returns error messages if there is nothing to be deleted
// or the number input to be deleted is invalid.
void commandDelete(){
	vector <string> file;

	int number=0;
	cin >> number;

	file = extractData(file);

	//Error #1 tells users that file is empty, there is
	//nothing to delete.
	if(file.empty()){
		printMessageError(1);
	}

		//Error #2 tells users that there is no such
		//data to be deleted - Invalid input.
		else 
			if(number > file.size()){
				printMessageError(2);
			}

				else{
					string deleteString;
					deleteString = file[number-1];
					file.erase(file.begin()+number-1);
					printMessageSuccessDelete(deleteString);
					file = updateFile(file);
				}
}

// This function prints the respective error messages.
void printMessageError(int errorNumber){
	switch (errorNumber){
		case(1):
			cout << "Error: File is empty, nothing to delete." <<endl;
			break;

		case(2):
			cout << "Error: Invalid item number to be deleted." << endl;
			break;

		case(3):
			cout << fileName << " is empty"<< endl;
			break;
		}
}

// This function clears all the contents in the file
// and returns with a success message. 
void commandClear(){
	ofstream add(fileName);
	add.close();
	printMessageClear();
}

// This function sorts the items in the file in ascending order
// Order: Numerical order first then in alphabetical order.
// Note: Capitalized letters have higher precedence than uncapitalized ones.
vector<string> commandSort(vector<string> file){
	sort(file.begin(), file.end());
	return file;
}

// This function searches for the keyword that the user input
// and prints the search results out with it's repective number. 
string commandSearch(vector<string> file, string searchString){
	ostringstream oss;

	for(int i=0; i<file.size() ; i++){
			string extractString;
			extractString = file[i];
			if(extractString.find(searchString) != extractString.npos){
				oss << i+1 << ". " << extractString << endl; 
			}
	}
	return oss.str();
}

void printMessageSuccessAdd (string inputline) {
	cout << "added to " << fileName << ": " << '"' << inputline << '"' << endl;	
}

void printMessageSuccessDelete(string deleteString){
	cout<< "deleted from " << fileName << ": " << '"' << deleteString << '"' << endl;
}

void printMessageSuccessSort(){
	cout<< fileName << " has been sorted." << endl;
}

void printMessageClear(){
	cout<< "all content deleted from " << fileName << endl;
}

void printMessageWelcome(){
	cout << "Welcome to TextBuddy. "<< fileName <<" is ready for use" << endl;
}

void printMessageCommand(){
	cout << "command: ";
}

// This function reads in the command and transform it into proper format.
// For example transforming uppercase to lowercase.
string readCommand(string command){
	transform(command.begin(),command.end(),command.begin(),tolower);
	return command;
}

// This function sorts the command and calls the respective functions.
void performCommand(){
	string command = "";
	cin >> command;	
	command = readCommand(command);

	while(command != "exit"){

		if(command == "add"){
			commandAdd();
		}

		else if(command == "display"){
			vector <string> file;
			file = extractData(file);
			cout << commandDisplay(file);
		}

		else if(command == "delete"){
			commandDelete();
		}

		else if(command == "clear"){
			commandClear();
		}
		
		else if(command == "sort"){
			vector<string> file;
			file = extractData(file);
			file = commandSort(file);
			file = updateFile(file);
			file.clear();
			printMessageSuccessSort();
		}

		else if(command == "search"){
			vector <string> file;
			file = extractData(file);
			string searchString;
			cin >> searchString;
			cout << commandSearch(file, searchString);
			file.clear();
		}

		printMessageCommand();
		cin >> command;
		command = readCommand(command);
	}
}

