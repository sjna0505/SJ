#include "cmdhandler.h"
#include "util.h"
using namespace std;

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

    if(words.size() == 0){
        return HANDLER_OK;
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

    if(words.size() == 0){
        return HANDLER_OK;
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

    if(words.size() == 0){
        return HANDLER_OK;
    }

    WebPageSetCombiner* combiner = new DIFFWebPageSetCombiner();
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

