#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;


void MDParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if(!wfile) {
        throw invalid_argument("Bad webpage filename in MDParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            // ADD YOUR CODE HERE

            if(c == '['){
                state = LINKTEXT;
            }

            if(isalnum(c)){
                term += c;

            }
            else{
                if(term != ""){
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                }
                term = "";
            }

        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // ADD YOUR CODE HERE

            if(c == ']'){
                state = ISLINK;
            }


            if(isalnum(c)){
                term += c;

            }

            else{
                if(term != ""){
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                }
                term = "";
            }

        }
        else if( state == ISLINK )
        {
            // ADD YOUR CODE HERE

            if(c == '('){
                state = LINKURL;
                link = "";
            }

            else{
                if(isalnum(c)){
                    term += c;
                    
                }
                
                state = NORMALTEXT;
            }


        }
        // Else we are in the LINKURL state.
        else
        {
            // ADD YOUR CODE HERE

            if(c == ')'){
                //link = conv_to_lower(link);
                allOutgoingLinks.insert(link);
                state = NORMALTEXT;
            }

            else
                link += c;

        }
        // Attempt to get another character from the file.
        c = wfile.get();
            
            
    }
    // ADD ANY REMAINING CODE HERE
    if(term != ""){
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }




    // Close the file.
    wfile.close();
}

std::string MDParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        // Logic for parsing a normal term.
        if (state == NORMALTEXT)
        {
            // The moment we hit a bracket, we input our current working term
            // into the allSearchableTerms set, reset the current term, and move into
            // parsing a link.
            if (c == '[')
            {
                state = LINKTEXT;
            }
            retval += c;
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // When we hit the closing bracket, then we must be finished getting the link.
            if (c == ']')
            {
                state = ISLINK;
            }
            retval += c;
        }
        else if (state == ISLINK) {
            if (c == '(') {
                state = LINKURL;
            }
            else
            {
                state = NORMALTEXT;
                retval += c;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // When we hit a closing parenthese then we are done, and the link can be inserted.
            if (c == ')')
            {
                state = NORMALTEXT;
            }
        }
        c = wfile.get();
    }
    return retval;
}

void MDParser::crawl(
    const std::map<std::string, PageParser*>& parsers,
    std::string filename,
    std::set<std::string>& processed,
    std::ostream& ofile)
{
    ifstream in_file;
    in_file.open(filename);

    //check if the file fails to open(base case)
    if(in_file.fail())
        return;

    //check if the file already exists(base case)
    else if(processed.find(filename) != processed.end()){
        in_file.close();
        return;
    }

    else{
        processed.insert(filename);
        ofile << filename << endl;

        set<string> outgoingLinks;
        crawlParse(in_file, filename, outgoingLinks);

        set<string>::iterator it;

        if(!outgoingLinks.empty()){

            //go to the outgoing links to crawl
            for(it = outgoingLinks.begin(); it != outgoingLinks.end(); ++it)
            {
                crawl(parsers, *it, processed, ofile);
            }
        }
        
        in_file.close();
        return;
    }
}

void MDParser::crawlParse(std::istream& wfile ,std::string filename, std::set<std::string>& outgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    outgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            // ADD YOUR CODE HERE

            if(c == '['){
                state = LINKTEXT;
            }

            if(isalnum(c)){
                term += c;

            }
            else{
                term = "";
            }

        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // ADD YOUR CODE HERE

            if(c == ']'){
                state = ISLINK;
            }


            if(isalnum(c)){
                term += c;

            }

            else{
                term = "";
            }

        }
        else if( state == ISLINK )
        {
            // ADD YOUR CODE HERE

            if(c == '('){
                state = LINKURL;
                link = "";
            }

            else{
                if(isalnum(c)){
                    term += c;
                    
                }
                
                state = NORMALTEXT;
            }


        }
        // Else we are in the LINKURL state.
        else
        {
            // ADD YOUR CODE HERE

            if(c == ')'){
                outgoingLinks.insert(link);
                state = NORMALTEXT;
            }

            else
                link += c;

        }
        // Attempt to get another character from the file.
        c = wfile.get();
            
            
    }

    

}


