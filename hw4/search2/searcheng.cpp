#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"

using namespace std;


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


/**
 * Performs the PageRank algorithm on the webpages in the input set
 * [TO BE WRITTEN]
 *
 * @param[in] in_pages
 *   Unexpanded candidate set of webpages to run the PageRank algorithm on
 *
 * @return vector of pairs of webpage pointers and their PageRank score
 */

std::vector<std::pair<WebPage*, double> > SearchEng::pageRank(const WebPageSet& in_pages)
{

    map<WebPage*, int> candidateSet;
    map<WebPage*, set<int> > incomingPageRank;
    map<WebPage*, set<int> > outgoingPageRank;
    vector<pair<WebPage*, double> > pageRankList;

    //loop to create candidate set
    for(set<WebPage*>::iterator it = in_pages.begin(); it != in_pages.end(); ++it)
    {
        map<WebPage*, int>::iterator findIt = candidateSet.find(*it);
        if(findIt == candidateSet.end()){
            pageRankList.push_back(make_pair(*it, 0.0));
            candidateSet.insert(make_pair(*it, (int)pageRankList.size()-1 ));
        }


        set<WebPage*> incomingLinks = (*it)-> incoming_links();

        for(set<WebPage*>::iterator inIt = incomingLinks.begin(); inIt != incomingLinks.end(); ++inIt)
        {
            map<WebPage*, int>::iterator findIt2 = candidateSet.find(*inIt);
            if(findIt2 == candidateSet.end()){
                pageRankList.push_back(make_pair(*inIt, 0.0));
                candidateSet.insert(make_pair(*inIt, (int)pageRankList.size()-1 ));
            }
        }

        set<WebPage*> outgoingLinks = (*it)-> outgoing_links();

        for(set<WebPage*>::iterator outIt = outgoingLinks.begin(); outIt != outgoingLinks.end(); ++outIt)
        {
            map<WebPage*, int>::iterator findIt2 = candidateSet.find(*outIt);
            if(findIt2 == candidateSet.end()){
                pageRankList.push_back(make_pair(*outIt, 0.0));
                candidateSet.insert(make_pair(*outIt, (int)pageRankList.size()-1 ));
            }
        }
    }


    //loop to create outgoing links and incoming links for each webpage that is within candidate set
    for(unsigned long int i = 0; i < pageRankList.size(); i++)
    {

        set<WebPage*> incomingLinks = pageRankList[i].first->incoming_links();
        pageRankList[i].second = 1.0/ candidateSet.size();
        set<WebPage*> outgoingLinks = pageRankList[i].first-> outgoing_links();

        set<int> checkIncoming;
        
        for(set<WebPage*>::iterator inIt = incomingLinks.begin(); inIt != incomingLinks.end(); ++inIt)
        {
            
            map<WebPage*, int>::iterator exist = candidateSet.find(*inIt);
            //if it's in candidate set
            if(exist != candidateSet.end()){
                
                checkIncoming.insert(exist->second);
            }
        }
        incomingPageRank.insert(make_pair(pageRankList[i].first, checkIncoming));


        set<int> checkOutgoing;

        for(set<WebPage*>::iterator outIt = outgoingLinks.begin(); outIt != outgoingLinks.end(); ++outIt)
        {
            map<WebPage*, int>::iterator exist = candidateSet.find(*outIt);
            if(exist != candidateSet.end()){

                checkOutgoing.insert(exist->second);
            }

        }
        outgoingPageRank.insert(make_pair(pageRankList[i].first, checkOutgoing));

    }

    vector<pair<WebPage*, double> > tempProb;
    //loop to calculate page rank
    for(int t = 0; t <= 20; t++){

        if(t == 0){
            tempProb = pageRankList;
            continue;
        }

        //loop to account for each webpage for page rank
        for(unsigned long int i = 0; i < pageRankList.size(); i++)
        {
            double random = 0.15/ candidateSet.size();
            double nonRandom = 0.0;

            map<WebPage*, set<int> >::iterator incom = incomingPageRank.find(pageRankList[i].first);
            set<int> incomings;
            incomings = incom-> second;
            //loop to get the probability of incoming links of respective webpage in the last iteration
            for(set<int>::iterator webInc = incomings.begin(); webInc != incomings.end(); ++webInc)
            {
                map<WebPage*, set<int> >::iterator outIt = outgoingPageRank.find(tempProb[*webInc].first);
                
                nonRandom += tempProb[*webInc].second / (outIt->second.size()+1);

            }

            //account for self-loop
            map<WebPage*, set<int> >::iterator selfOutIt = outgoingPageRank.find(tempProb[i].first);
            nonRandom += tempProb[i].second/ (selfOutIt->second.size()+1);

            double prob = random + 0.85 *nonRandom;
            
            pageRankList[i].second = prob;
        }
        //copy over to temp to use it for next iteration
        tempProb = pageRankList;


    }

    return pageRankList;

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
            wbSet = combiner ->combine(wbSet, tempSet);
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





