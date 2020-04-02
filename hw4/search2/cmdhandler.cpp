#include "cmdhandler.h"
#include "util.h"
#include <algorithm>
using namespace std;

//comparison object for sorting alphabetically
struct AlphabetComp{
    bool operator()(pair<WebPage*, double> i, pair<WebPage*, double> j){
        string iName = i.first->filename();
        string jName = j.first->filename();

        if(iName.compare(jName) < 0)
            return false;
        else
            return true;
    }

};

//comparison object for sorting by rank
struct ProbabilityComp{
    bool operator()(pair<WebPage*, double> i, pair<WebPage*, double> j){
        return (i.second > j.second);
    }

};


QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}


ANDHandler::ANDHandler()
{

}

ANDHandler::ANDHandler(Handler* next)
    : Handler(next)
{

}

bool ANDHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T ANDHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;
    vector<string> words;
    WebPageSet wbset;

    while(instr >> name){
        name = conv_to_lower(name);
        words.push_back(name);
    }

    WebPageSetCombiner* combiner = new ANDWebPageSetCombiner();
    wbset = eng->search(words, combiner);
    display_hits(wbset, ostr);
    delete combiner;
    return HANDLER_OK;


}

ORHandler::ORHandler()
{

}

ORHandler::ORHandler(Handler* next)
    : Handler(next)
{

}

bool ORHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T ORHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;
    vector<string> words;
    WebPageSet wbset;

    while(instr >> name){
        name = conv_to_lower(name);
        words.push_back(name);
    }

    WebPageSetCombiner* combiner = new ORWebPageSetCombiner();
    wbset = eng->search(words, combiner);
    display_hits(wbset, ostr);
    delete combiner;
    return HANDLER_OK;


}

DIFFHandler::DIFFHandler()
{
    
}

DIFFHandler::DIFFHandler(Handler* next)
    : Handler(next)
{

}

bool DIFFHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DIFFHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;
    vector<string> words;
    WebPageSet wbset;

    while(instr >> name){
        name = conv_to_lower(name);
        words.push_back(name);
    }


    WebPageSetCombiner* combiner = new DiffWebPageSetCombiner();
    wbset = eng->search(words, combiner);
    display_hits(wbset, ostr);
    delete combiner;
    return HANDLER_OK;


}


IncomingHandler::IncomingHandler()
{

    
}


IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}


bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";
}


Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    else{
        WebPage * wbpg = eng->retrieve_page(name);
        if(wbpg == NULL){
            return HANDLER_ERROR;
        }
        WebPageSet wbset = wbpg -> incoming_links();

        int setSize = wbset.size();
        ostr << setSize << endl;

        for(set<WebPage*>::iterator it = wbset.begin(); it != wbset.end(); ++it)
        {
            ostr << (*it)->filename() << endl;
        }
        

    }

    return HANDLER_OK;


}

OutgoingHandler::OutgoingHandler()
{

    
}


OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}


bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";
}


Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    else{
        WebPage * wbpg = eng->retrieve_page(name);
        if(wbpg == NULL){
            return HANDLER_ERROR;
        }
        WebPageSet wbset = wbpg -> outgoing_links();

        int setSize = wbset.size();
        ostr << setSize << endl;

        for(set<WebPage*>::iterator it = wbset.begin(); it != wbset.end(); ++it)
        {
            ostr << (*it)-> filename() << endl;
        }
        

    }

    return HANDLER_OK;


}


PRANDHandler::PRANDHandler()
{

    
}

PRANDHandler::PRANDHandler(Handler* next)
    : Handler(next)
{

}

bool PRANDHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRAND";
}

Handler::HANDLER_STATUS_T PRANDHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;
    string sort;
    vector<string> words;
    WebPageSet wbset;
    vector< pair<WebPage*, double> > pgRankList;

    //check to see what kind of sorting the user asks
    instr >> sort;
    if(sort != "r" && sort != "n")
        return HANDLER_ERROR;

    while(instr >> name){
        name = conv_to_lower(name);
        words.push_back(name);
    }

    WebPageSetCombiner* combiner = new ANDWebPageSetCombiner();
    wbset = eng->search(words, combiner);

    AlphabetComp a;
    ProbabilityComp p;

    //get the list with rank
    pgRankList = eng->pageRank(wbset);

    if(sort == "n")
        mergeSort(pgRankList, a);
    else
        mergeSort(pgRankList, p);

    //print
    display_ranked_hits(pgRankList, ostr);

    delete combiner;
    return HANDLER_OK;


}

PRORHandler::PRORHandler()
{

}

PRORHandler::PRORHandler(Handler* next)
    : Handler(next)
{

}

bool PRORHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PROR";
}

Handler::HANDLER_STATUS_T PRORHandler::process(SearchEng* eng, std::istream& instr,
    std::ostream& ostr){

    string name;
    string sort;
    vector<string> words;
    WebPageSet wbset;
    vector< pair<WebPage*, double> > pgRankList;

    //check for which sorting
    instr >> sort;
    if(sort != "r" && sort != "n")
        return HANDLER_ERROR;

    while(instr >> name){
        name = conv_to_lower(name);
        words.push_back(name);
    }

    WebPageSetCombiner* combiner = new ORWebPageSetCombiner();
    wbset = eng->search(words, combiner);


    AlphabetComp a;
    ProbabilityComp p;

    //get list with rank
    pgRankList = eng->pageRank(wbset);
    
    if(sort == "n")
        mergeSort(pgRankList, a);
    else
        mergeSort(pgRankList, p);

    //print list
    display_ranked_hits(pgRankList, ostr);

    delete combiner;
    return HANDLER_OK;


}

