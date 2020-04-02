#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"
#include "searcheng.h"
#include "combiners.h"

using namespace std;

/**
 * Handles the QUIT command - COMPLETED in cmdhandler.cpp
 */
class QuitHandler : public Handler
{
public:
    QuitHandler();
    QuitHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/*********** OTHER CLASSES WILL NEED TO BE COMPLETED IN cmdhandler.cpp *******/
/***********  You will also need to declare the classes for handling   *******/
/***********          the AND, OR, and DIFF command handlers           *******/

/**
 * Handles the PRINT command
 */
class PrintHandler : public Handler
{
public:
    PrintHandler();
    PrintHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the INCOMING command
 */
class IncomingHandler : public Handler
{
public:
    IncomingHandler();
    IncomingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the OUTGOING command
 */
class OutgoingHandler : public Handler
{
public:
    OutgoingHandler();
    OutgoingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/****************************************************************************/
/* Declare the handler classes for AND, OR, and DIFF here                   */
/****************************************************************************/


class ANDHandler : public Handler
{
public:
    ANDHandler();
    ANDHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

};

class ORHandler : public Handler
{
public:
    ORHandler();
    ORHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

};

class DIFFHandler : public Handler
{
public:
    DIFFHandler();
    DIFFHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

};


class PRANDHandler : public Handler
{
public:
    PRANDHandler();
    PRANDHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

};


class PRORHandler : public Handler
{
public:
    PRORHandler();
    PRORHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

};

template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp )
{
    if(list.size() <= 1)
        return;
    list = split(list, 0, list.size() -1, comp);
};

template <class T, class Compare>
std::vector<T> split(std::vector<T>& list, int i, int j, Compare comp)
{
    int newI, newJ;
    vector<T> rslt;
    vector<T> left;
    vector<T> right;
    if(i == j)
        rslt.push_back(list[i]);
    else{
        newI = int((i+j+1)/2);
        newJ = newI - 1;
        left = split(list,i,newJ,comp);
        right = split(list,newI,j,comp);
        rslt = merge(left,right,comp);
        left.clear();
        right.clear();
    }

    return rslt;
};

template <class T, class Compare>
std::vector<T> merge(std::vector<T>& left, std::vector<T>& right, Compare comp)
{
    vector<T> rslt;
    int i = 0;
    int j = 0;
    while(i < (int)left.size() && j < (int)right.size())
    {
        if(comp(left[i], right[j])){
            rslt.push_back(left[i]);
            i++;
        }
        else{
            rslt.push_back(right[j]);
            j++;
        }
    }

    if(i == (int)left.size() && j < (int)right.size())
    {
        for(int k = j; k < (int)right.size(); k++){
            rslt.push_back(right[k]);
        }
    }
    if(j == (int)right.size() && i < (int)left.size())
    {
        for(int k = i; k < (int)left.size(); k++){
            rslt.push_back(left[k]);
        }
    }
    return rslt;
};






#endif
