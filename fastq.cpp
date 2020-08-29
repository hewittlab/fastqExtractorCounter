#include "fastq.h"

string& ltrim(string& str, const string& chars = "\t\n\v\f\r ")
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

string& rtrim(string& str, const string& chars = "\t\n\v\f\r ")
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

string& trim(string& str, const string& chars = "\t\n\v\f\r ")
{
	return ltrim(rtrim(str, chars), chars);
}

//read input csv file and get all searchable words
list<string> getAllSearchWords(string search_file) {

	fstream fin;
	fin.open(search_file, ios::in);
	list<string> search_words;
	string line, word, temp;

	if (fin.is_open()) {
		long counter = 0;
		while (getline(fin, line)) { 
			stringstream s(line);
			while (s.good()) {
				getline(s, word, ',');
				if (word.empty()) continue;
				//cehck UTF-8 BOM
				if (counter == 0 && checkBOM(word)) {
					word = word.erase(0, 3);
				}
				search_words.push_back(trim(word));
			}
			counter++;
		}
		fin.close();
		cout << "Success to read input csv file !" << endl;
	}
	else {
		cout << "Invalid csv file input..." << endl;
	}
	return search_words;
}

void search_fastq(string fastq_file, list<string> search_words) {
	cout << "Start to search fasq ..." << endl << endl;
	//construct map for search counter
	map<string, int> counter_map;
	for (list<string>::iterator it = search_words.begin(); it != search_words.end(); it++) {
		counter_map[*it] = 0;
	}
	fstream fin;
	fin.open(fastq_file, ios::in);
	string line;

	fstream out_fastq;
	out_fastq.open("output.fastq", ios::out);
	if (out_fastq.bad()) {
		cout << "Fail to create fastq output file !" << endl;
		return;
	}
	if (fin.is_open()) {
		long counter = 0;
		long process_counter = 1;
		bool fastq_start = false;
		vector<string> block;
		while (getline(fin, line)) {
			if (line.empty()) continue;

			if (counter == 0) {
				if (checkBOM(line)) {
					line = line.erase(0, 3);
				}
			}
			/*
			Fastq squence has 4 line.
			read each sequence as 4 line and parse it
			*/
			if (counter % 4 == 0) {
				if (!block.empty() && block.size() == 4) {
					//process search
					bool out_flag = false;
					cout << "Processing sequence " << process_counter << ":" << endl;
					for (list<string>::iterator it = search_words.begin(); it != search_words.end(); it++) {
						if (block[1].find(*it) != string::npos) {
							//increase counter
							counter_map[*it]++;
							//write to ooutput file
							if (!out_flag) {
								for (vector<string>::iterator vec = block.begin(); vec != block.end(); vec++) {
									out_fastq << *vec << endl;
								}
								out_flag = true;
							}
						}
						
					}
					block.clear();
					process_counter++;
				}
				block.push_back(line);
			}
			else {
				block.push_back(line);
			}
			counter++;
		}
		fin.close();
		out_fastq.close();
		//write result csv file
		fstream out_csv;
		out_csv.open("output.csv", ios::out);
		if (out_csv.bad()) {
			cout << "Fail to create output csv file !" << endl;
			return;
		}
		for (list<string>::iterator it = search_words.begin(); it != search_words.end(); it++) {
			out_csv << *it << "," << counter_map[*it] << endl;
		}
		out_csv.close();
		cout << endl;
		cout << "Success process !" << endl;
	}
	else {
		cout << "Invalid fastq file ..." << endl;
	}
}

bool startWith(string src, string prefix) {
	size_t found = src.find(prefix);
	if (found == 0)
	{
		return true;
	}
	return false;
}
bool checkBOM(string src) {
	char bom1 = src.at(0);
	char bom2 = src.at(1);
	char bom3 = src.at(2);

	char bom[3] = { 0xEF, 0xBB, 0xBF };
	if (bom1 == bom[0] && bom2 == bom[1] && bom3 == bom[2]) {
		return true;
	}
	return false;
}
