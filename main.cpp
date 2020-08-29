#include "fastq.h"



int main() {
	string input_csv;
	string input_fastq;

	cout << "Please enter input csv path: ";
	std::getline(cin, input_csv);
	cout << "Please enter input fastq path: ";
	std::getline(cin, input_fastq);
	list<string> search_words = getAllSearchWords(input_csv);
	if (search_words.empty()) {
		cout << "There is not exist search words..." << endl;
		return FAIL;
	}
	search_fastq(input_fastq, search_words);

	return SUCCESS;
}
