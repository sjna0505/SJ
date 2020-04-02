#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "md_parser.h"
#include "txt_parser.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Must provide an index file and output file" << endl;
        return 1;
    }

    // ---------------------- [TO BE COMPLETED] -------------------------------

    
    //create a map of parsers and extensions
    map<string, PageParser*> parsers;
    PageParser * mdparser = new MDParser;
    parsers.insert(make_pair("md", mdparser));
    PageParser * txtparser = new TXTParser;
    parsers.insert(make_pair("txt", txtparser));

    ifstream in_file;
    in_file.open(argv[1]);
    ofstream out_file(argv[2]);

    if(in_file.fail() || out_file.fail()){
    	cout << "Invalid filename" << endl;
    	return 1;
    }

    string filename;
    set<string> processed;

    while(getline(in_file, filename)){

    	string extension = extract_extension(filename);

    	map<string, PageParser*>::iterator it = parsers.find(extension);
    	//if its not .md or .txt
    	if(it == parsers.end())
    		continue;
    	//else crawl
    	else{
    		it->second->crawl(parsers, filename, processed, out_file);
    	}
    }

    in_file.close();
    out_file.close();

    
    // You may add cleanup code here if necessary

    delete mdparser;
    delete txtparser;
    parsers.clear();


    return 0;
}
