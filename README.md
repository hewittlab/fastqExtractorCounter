# fastqExtractorCounter


This C++ program extracts and counts specific sequences from fastq files.

On a mac terminal - the program can be compiled using:
% g++ *.cpp -o readcounter

Then run using:
% ./readcounter  

After selecting a csv file containing all contig sequences to be searched (single contig per line) and the fastq file to be analysed ... two output files will be generated:
1) Output.csv 
- which contains the sequence string and frequency of identical occurences in the fastq file
2) Output.fastq
- which contains the sequences and accompanying information for the reads which have an identical matching sequence string to the input file
