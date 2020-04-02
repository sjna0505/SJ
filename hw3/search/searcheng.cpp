#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

std::string extract_extension(const std::string& filename);


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary


}

SearchEng::~SearchEng()
{
    //delete web page list
    while(!webpgList.empty()){
        delete webpgList.back();
        webpgList.pop_back();
    }

    extensions.clear();

    delete noExtensionParser_;

}


void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{

    //make a new pair for extension
    extensions.insert(make_pair(extension, parser));

}






void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}


/**
     * Retrieves the WebPage object for a given page/file
     * [TO BE WRITTEN]
     *
     * @param[in] page_name
     *   Name of page/file to retrieve
     *
     * @return Pointer to the corresponding WebPage object.  Should not be used
     *   to alter or deallocate the object.
     *   Return NULL if page_name does not exist.
     */
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{

    map<string, int>::const_iterator it = webpgMap.find(page_name);
    int index = 0;
    if(it != webpgMap.end()){
        index = it->second;

        if(index < 0 || (long unsigned)index >= webpgList.size())
            return NULL;
        else
            return webpgList[index];
    }

    return NULL;
}



 /**
     * Displays the contents of the page/file
     * [TO BE WRITTEN]
     *
     * @param[inout] ostr
     *   Output stream to display the contnents
     * @param[in] page_name
     *   Name of page/file to display
     *
     * @throw std::invalid_argument if the page_name does not exist
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    if(retrieve_page(page_name) !=  NULL){
        map<string, PageParser*>::const_iterator it = extensions.find(extract_extension(page_name));
        //check if you can find the appropriate parser
        if(it != extensions.end()){

            ostr << it->second->display_text(page_name);

        }

        else
            throw std::logic_error("no parser is registered for the file's extension");

    }
    else
        throw std::invalid_argument("page name doesn't exist");

}


/**
     * Uses the given search terms and combiner to find the set of webpages
     *  that match the query
     * [TO BE WRITTEN]
     *
     * @param[in] terms
     *   words/terms to search for
     * @param[in] combiner
     *   Combiner object that implements the strategy for combining the
     *   pages that contain each term (i.e. AND, OR, DIFF, etc.)
     *
     * @return Set of webpages matching the query
     */
WebPageSet SearchEng::search(const std::vector<std::string>& terms,
                                             WebPageSetCombiner* combiner) const
{
    WebPageSet wbSet;

    //if there is nothing in the list, return an empty set
    if(terms.size() == 0)
        return wbSet;


    for(long unsigned int i = 0; i < terms.size(); i++){

        //find if there is a term that exists in webpages
        map<string, set<int> >::const_iterator it = termMap.find(terms[i]);

        WebPageSet tempSet;

        if(it != termMap.end()){

            //iterate through the webpage indexes for a found term
            for(set<int>::iterator it2 = it->second.begin(); 
                            it2 != it->second.end(); ++it2)
            {
                //if i is 0, just add everything to wbset
                if(i == 0){
                    wbSet.insert(webpgList[*it2]);
                }

                else{

                    tempSet.insert(webpgList[*it2]);
                }

            }
            
            if(i == 0)
                continue;

            else{
                wbSet = combiner->combine(wbSet, tempSet);
                tempSet.clear();
            }
        }
        else
            throw std::invalid_argument("term not found");
    }

    return wbSet;


}



void SearchEng::read_page(const std::string& filename)
{
    int curIndex = 0;
    

    map<string, int>::iterator checkIt = webpgMap.find(filename);
    WebPage * webpg;

    //if the webpage associated with the filename doesnt exist, allocate
    //new webpage
    if(checkIt == webpgMap.end()){
        webpg = new WebPage(filename);
        webpgList.push_back(webpg);
        curIndex = webpgList.size() -1;
        webpgMap.insert(make_pair(filename, curIndex));
    }
    //else finish implementing the already existing webpage
    else{

        curIndex = checkIt -> second;
        webpg = webpgList[curIndex];
    }

    PageParser * pgprs;
    
    string exten = extract_extension(filename);

    map<string, PageParser*>::iterator extIt = extensions.find(exten);
    if(extIt != extensions.end())
        //get the appropriate parser
        pgprs = extIt -> second;
    else
        throw std::logic_error("no parser is registered for the file's extension");


    set<string> searchableTerms;
    set<string> outgoingLinks;

    pgprs->parse(filename, searchableTerms, outgoingLinks);

    webpg->all_terms(searchableTerms);
    

    for(set<string>::iterator it = outgoingLinks.begin(); 
                            it != outgoingLinks.end(); ++it)
    {
        map<string, int>::const_iterator it2 = webpgMap.find(*it);
        //if the outgoinglink already exists
        if(it2 != webpgMap.end()){
            int foundIndex = it2 -> second;
            webpg->add_outgoing_link(webpgList[foundIndex]);
            webpgList[foundIndex]->add_incoming_link(webpgList[curIndex]);
        }
        //if it doesnt exist
        else{
            //allocate new webpage
            WebPage * emptyWebPg = new WebPage(*it);
            webpgList.push_back(emptyWebPg);
            int tempIndex = webpgList.size() -1;
            webpg->add_outgoing_link(emptyWebPg);
            emptyWebPg->add_incoming_link(webpgList[curIndex]);
            webpgMap.insert(make_pair(*it, tempIndex));
            
        }
    }

    for(set<string>::iterator termIt = searchableTerms.begin(); 
        termIt != searchableTerms.end(); ++termIt){


        map<string, set<int> >::iterator mapIt = termMap.find(*termIt);

        //adds all the appropriate webpage indexes associated with a respective term
        if(mapIt != termMap.end()){
            mapIt ->second.insert(curIndex);
        }

        //create a new pair
        else{
            set<int> termInt;
            termInt.insert(curIndex);
            termMap.insert(make_pair (*termIt, termInt));
            termInt.clear();
        }

    }

}



std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


