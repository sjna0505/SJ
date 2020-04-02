#include <iostream>
#include "gitint.h"
// Add any necessary headers
using namespace std;

void print_exception_message(const std::string& what_msg);

int main()
{

    GitInt g;
    string cmd_line;
    bool quit = false;
    const string PROMPT_STARTER = "$ ";

    g.print_menu();
    cout << PROMPT_STARTER;
    getline(cin, cmd_line);
    // Add your code here

    while(!quit){
        cout << PROMPT_STARTER;
        getline(cin, cmd_line);
        if (cmd_line != "") {
            try{
                quit = g.process_command(cmd_line);
            }
            catch (const runtime_error& what_msg)
            {
                print_exception_message(what_msg.what());
            }
            catch (const invalid_argument& what_msg)
            {
            print_exception_message(what_msg.what());
            }
        }
    }


    
    return 0;

}

void print_exception_message(const std::string& what_msg)
{
  cout << "Error - " << what_msg << endl;
}
