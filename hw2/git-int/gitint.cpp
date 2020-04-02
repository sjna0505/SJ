#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string INVALID_WRONG_FILE  = ": file doesn't exist";
const std::string INVALID_FILE_EXIST= ": file aleardy exists";
const std::string INVALID_NO_FILE= "no file exists";
const std::string INVALID_TAG_NAME = ": tag name already exists";
const std::string LOG_COMMIT_STARTER = "Commit: ";



// Class implementation

GitInt::GitInt()
{
    map<string, int> diff;
    CommitObj g("", diff, -1);
    head = 0;
    commits_.push_back(g);
}


void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);

    if (cmd == "quit") {
        quit = true;
    }
    // Continue checking/processing commands

    else if(cmd == "create"){
        string filename;
        int value;
        ss >> filename;
        ss >> value;
        if(ss.fail())
            throw std::runtime_error(INVALID_OPTION);
        create(filename, value);
    }

    else if(cmd == "edit"){
        string filename;
        int value;
        ss >> filename;
        ss >> value;
        if(ss.fail())
            throw std::runtime_error(INVALID_OPTION);
        edit(filename, value);
    }

    else if(cmd == "display"){
        int commitNumber;
        stringstream ss2;
        

        //if the cmd has nothing
        if(ss.eof()){
            display_all();
        }

        else{

            ss >> commitNumber;

            //if the integer is not detected

            if(!ss.fail())
                display_commit(commitNumber);

            else{
                string filename;
                ss2 << ss.rdbuf();
                ss2 >> filename;
                display(filename);
            }
        }
    }

    else if (cmd == "add")
    {
        string filename;
        ss >> filename;

        if(ss.fail()) 
            throw std::runtime_error(INVALID_OPTION);
        
        while(!ss.fail()){
            add(filename);
            ss >> filename;
        }
    }

    else if (cmd == "commit"){
        string logmsg;

        //get the whole string into logmsg
        getline(ss, logmsg);
        string valid_logmsg = "";

        if(logmsg.length() > 0){
            int k = 0;

            //loop for advancing the index by counting spaces for later to remove them
            while(logmsg[k] == ' '){
                k++;
            }

            //for removing quotation makrs
            if(logmsg[k] == '"'){
                for(unsigned int i = k+1; i < logmsg.length(); i++){
                    if(logmsg[i] != '"' )
                        valid_logmsg += logmsg[i];
                    else
                        break;

                }
            }

            else
            {
                for(unsigned int i = k+1; i < logmsg.length(); i++)
                {
                    valid_logmsg += logmsg[i];
                    if(logmsg[i] == ' ')
                        throw std::runtime_error(INVALID_OPTION);
                }
            }
        }

        else
            throw std::runtime_error(INVALID_OPTION);

        commit(valid_logmsg);
    }
    else if (cmd == "tag"){


        string dummy = "";
        string tagnm;
        ss >> dummy;
        ss >> tagnm;

        //for disaccounting -a
        if(dummy == "-a"){
            if(tagnm != ""){
                create_tag(tagnm, head);
            }
            else{
                throw std::runtime_error(INVALID_OPTION);
            }
        }
        else if(dummy == ""){
            tags();
        }

        else if(dummy != "-a"){
            throw std::runtime_error(INVALID_OPTION);
        }
        else if(tagnm == ""){
            throw std::runtime_error(INVALID_OPTION);
        }

    }

    else if(cmd == "log"){
        log();
    }

    else if(cmd == "checkout"){
        int checkoutNumber;
        stringstream ss2;
        ss >> checkoutNumber;

        //if the integer is not detected
        if(!ss.fail())
            checkout(checkoutNumber);

        else{
            string filename;
            ss2 << ss.rdbuf();
            ss2 >> filename;
            if(ss2.fail())
                throw std::runtime_error(INVALID_OPTION);
            checkout(filename);
        }
    }

    else if(cmd == "diff"){
        if(ss.eof()){
            diff(head);
        }
        else{
            int to;
            int from;
            ss >> to;
            if(ss.fail())
                throw std::runtime_error(INVALID_OPTION);
            ss >> from;
            stringstream ss2;
            string dummy = "";
            ss2 << ss.rdbuf();
            ss2 >> dummy;
            if(ss.fail()){
                if(dummy == "")
                    diff(to);
                else
                    throw std::runtime_error(INVALID_OPTION);
            } 
            else
                diff(to,from);
        }
    }

    else{
        throw std::runtime_error(INVALID_COMMAND);
    }         
    
    return quit;
}

void GitInt::create(const std::string& filename, int value)
{
    //first check to see if the file already exists
    map<string,int>::iterator it = filesMap.find(filename);

    if(it != filesMap.end())
        throw std::invalid_argument(filename + INVALID_FILE_EXIST);


    //add in the map
    filesMap.insert(make_pair(filename, value));

}


void GitInt::edit(const std::string& filename, int value)
{
    map<string, int>::iterator it = filesMap.find(filename);

    if(it != filesMap.end())
        //edit the value once the file has been found
        it -> second = value;
    else
        throw std::invalid_argument(filename +INVALID_WRONG_FILE);
}

void GitInt::display(const std::string& filename) const
{
    map<string, int>::const_iterator it = filesMap.find(filename);

    if(it != filesMap.end())
        cout << it -> first << " : " << it -> second << endl;
    else
        throw std::invalid_argument(filename + INVALID_WRONG_FILE);

}

void GitInt::display_all() const
{
    display_helper(filesMap);
}


void GitInt::display_commit(CommitIdx commit) const
{
    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    display_helper(commits_[commit].diffs_);
}

void GitInt::add(string filename)
{
    map<string, int>::iterator it = filesMap.find(filename);
    if(it != filesMap.end())
        //stage the file to later use it for commit
        addSet.insert(filename);
    else
        throw std::invalid_argument(filename + INVALID_WRONG_FILE);

}

void GitInt::commit(string message)
{

    map<string, int> diff;
    map<string, int>::iterator diff_it;
    CommitObj g(message, diff, head);
    set<string>::iterator innerIt;

    //check if there is nothing to commit
    if(addSet.empty())
        throw std::runtime_error(INVALID_OPTION);
    if(message == "") throw std::runtime_error(INVALID_OPTION);

    for(innerIt = addSet.begin(); innerIt != addSet.end(); ++innerIt)
    {
        int difference = 0;
        for(long unsigned int i = 0; i < commits_.size(); i++)   
        {
            //add all the diffs
            diff_it = commits_[i].diffs_.find(*innerIt);
            if (diff_it != commits_[i].diffs_.end()) {
                difference += commits_[i].diffs_.find(*innerIt)->second;
            }

        }
        //minus the diff from current
        int realDiff = filesMap.find(*innerIt)->second - difference;
        g.diffs_.insert(make_pair(*innerIt, realDiff) );

        
    }

    addSet.clear();
    head = commits_.size();
    commits_.push_back(g);

}   


void GitInt::create_tag(const string& tagname, CommitIdx commit)
{

    map<string, int>::iterator it = tagsMap.find(tagname);
    if(it != tagsMap.end())
        throw std::invalid_argument(tagname + INVALID_TAG_NAME);

    //add it in both data structures, one more printing, one
    //for processing
    tagsMap.insert(make_pair(tagname, commit));
    tagsList.push_back(tagname);
}

void GitInt::tags() const
{
    for (long unsigned int i = 0; i < tagsList.size(); i++){
        cout << tagsList[tagsList.size() - 1 - i] << endl;
    }

}

bool GitInt::checkout(CommitIdx commitIndex)
{
    map<string, int> tempFiles;
    bool isCheckout = false;
    if(valid_commit(commitIndex)){
        tempFiles= buildState(0, commitIndex);

        if(tempFiles.empty())
            throw std::invalid_argument(INVALID_NO_FILE);

        //update the head index
        head = commitIndex;
        filesMap = tempFiles;
    }
    else
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);

    isCheckout = true;
    return isCheckout;
 
}

bool GitInt::checkout(string tag)
{
    int index = 0;
    bool isCheckout = false;
    map<string,int> tempFiles;

    //find which index to checkout
    map<string, int>::iterator it = tagsMap.find(tag);



    if(it != tagsMap.end())
        index = it->second;
    else 
        throw std::invalid_argument(tag + INVALID_TAG_NAME);

    if(!valid_commit(index))
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);

    //make it back to the of which the tag was tagged on
    tempFiles = buildState(0,index);

    if(tempFiles.empty())
        throw std::invalid_argument(INVALID_NO_FILE);
    head = index;
    isCheckout = true;
    filesMap = tempFiles;

    return isCheckout;
}

void GitInt::log() const
{
    for(long unsigned int i = head; i > 0; i = commits_[i].parent_){
        log_helper(i, commits_[i].msg_);
    }

}

void GitInt::diff(CommitIdx to) const
{
    map<string, int>::const_iterator filesIt;

    if(valid_commit(to)){

        for(filesIt = filesMap.begin(); filesIt != filesMap.end(); ++filesIt){
            //reset the difference to zero every time new file is calculated
            int difference = 0;

            //add the differences from to to 0
            for(long int i = to; i >= 0; i = commits_[i].parent_){
                if(commits_[i].diffs_.find(filesIt->first) != commits_[i].diffs_.end()){
                    difference += commits_[i].diffs_.find(filesIt-> first)->second;
                }
            }

            if((filesIt-> second - difference) != 0)
                cout <<filesIt->first << " : " << filesIt -> second - difference << endl;


        }
    }
    else
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
}

void GitInt::diff(CommitIdx end, CommitIdx start) const
{
    if(start > end)
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);

    if(valid_commit(end) && valid_commit(start)){

        map<string, int>::const_iterator filesIt;
        

        //account for all the files until the "end" commit
        for(filesIt = commits_[end].diffs_.begin(); filesIt != commits_[end].diffs_.end(); ++filesIt)
        {

            int difference = 0;

            //go down the branch to add up all the diffs
            for(long int i = end; i > start; i = commits_[i].parent_){
                if (commits_[i].diffs_.find(filesIt->first) != commits_[i].diffs_.end()) {
        
                    difference += commits_[i].diffs_.find(filesIt->first)->second;
                }
            }

            if(difference != 0)

                cout << filesIt-> first << " : " << difference << endl;
            }

    }
    else
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
}

bool GitInt::valid_commit(CommitIdx commit) const
{
    if(commit >= commits_.size() || commit < 0)
        return false;
    else
        return true;
}


map<string, int> GitInt::buildState(CommitIdx from, CommitIdx to) const
{
    map<string, int>::const_iterator filesIt;
    map<string, int> checkoutFiles;

    //check if all the indexes are valid
    if(valid_commit(from) && valid_commit(to)){

        //double loop to create the state of the files at the time of the
        //commitindexes given as arguments
        for(long int i = to; i >= from; i = commits_[i].parent_){
            for(filesIt = commits_[i].diffs_.begin(); filesIt != commits_[i].diffs_.end(); ++filesIt){

                if(checkoutFiles.find(filesIt -> first) == checkoutFiles.end())
                    checkoutFiles.insert(make_pair(filesIt->first , filesIt -> second));
                else
                    checkoutFiles.find(filesIt->first) -> second += filesIt-> second;
            }
        }
    }

    return checkoutFiles;

}

void GitInt::display_helper(const std::map<std::string, int>& dat) const
{
    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}


void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}

