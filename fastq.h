#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <map>


using namespace std;

#define FAIL -1
#define SUCCESS 0
#define FASTQSTART "@"

list<string> getAllSearchWords(string search_file);
void search_fastq(string fastq_file, list<string> search_words);
bool startWith(string src, string prefix);
bool checkBOM(string src);
