#include "QS.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

string boolToString(bool retVal) {
	if (retVal) return "OK";
	return "Error";
}

int main(int argc, char* argv[]) {
	VS_MEM_CHECK

	//open files
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}
	ifstream in(argv[1]);
	if (!in.is_open()) {
		cout << "Uh oh there was an inputFile error..." << endl;
		return 2;
	}
	ofstream out(argv[2]);
	if (!out.is_open()) {
		cout << "Uh oh there was an outputFile error..." << endl;
		return 3;
	}

	QS<int> cksort;
	string input;
	bool checkArray = false, arrayFinal = true;
	int capacity, left, right, pivot;

	while (in >> input) {
		if (input == "QuickSort") {
			in >> capacity;
			out << input << " " << capacity << " " << boolToString(cksort.createArray(capacity)) << endl;
		}
		else if (input == "AddToArray") {
			out << input <<  "  ";
			string input;
			getline(in, input);
			string end = input.substr(input.length() - 1, 1);
			stringstream is(input);
			while (is >> input) {
				if (is.peek() == string::npos) 
					out << input << " ";
				else
					out << input << ",";
				checkArray = cksort.addElement(stoi(input));
				if (!checkArray) arrayFinal = false;
			}
			out << boolToString(arrayFinal) << endl;
		}
		else if (input == "Capacity") {
				out << input << " " << cksort.capacity() << endl;
		}
		else if (input == "Clear") {
			out << input << " " << boolToString(cksort.clear()) << endl;
		}
		else  if (input == "Size") {
			out << input << " " << cksort.size() << endl;
		}
		else  if (input == "Sort") {
			in >> left;
			in >> right;
			out << input << " " << left << "," << right << " " << boolToString(cksort.sort(left, right)) << endl;
		}
		else if (input == "SortAll") {
			out << input << " " << boolToString(cksort.sortAll()) << endl;
		}
		else if (input == "MedianOfThree") {
			in >> left;
			in >> right;
			out << input << " " << left << "," << right << " = " << cksort.medianOfThree(left, right) << endl;
		}
		else if (input == "Partition") {
			in >> left;
			in >> right;
			in >> pivot;
			int fake = left;
			if (left < 0 || right < 0 || pivot < 0) left = right;
			out << input << " " << fake << "," << right << "," << pivot << " = " << cksort.partition(left, right, pivot) << endl;
		}
		else if (input == "PrintArray") {
			out << input << " ";
			if (cksort.size() > 0) {
				QS<int>::Iterator iter = cksort.begin();
				for (; iter != cksort.end(); ++iter) {
					if (iter != cksort.endb4())
						out << *iter << ",";
					else
						out << *iter << " ";
				}
			}
			else out << "Empty ";
			out << endl;
		}
		else if (input == "Stats") {
			out << input << " not implemented" << endl;
		}
		else {
			out << "Uh oh" << endl;
		}
	}

	cksort.endClear();
	in.close();
	out.close();
	return 0;
};