#include<bits/stdc++.h>

using namespace std;

// Xgcc Version 0.0.0
// Author: @askformeal github.com
// Oh please! It's hard to register a user name on github 


// This program only work in Windows System
// compile this file using "g++ -o xgcc xgcc.cpp" and push xgcc.exe into C:\Windows\System32 folder

void check_file_exist(string filename)
// check if a file exists in the current folder
{
    ifstream exist_test(filename);

    if (!(exist_test.good()))
    {
        cout << "*Error:*\n\tNo such file: " << filename << '\n';
        exit(0);
    }
}

int main(int argc, char*argv[])
{
    string option;  
    /*
        options about how to run the .cpp file
        -c only compile
        -r only run
        -h show help
    */
    bool if_compile = true; // whether to compile the .cpp file
    bool if_run = true; // whether to run the .exe file

    string command_compile = ""; // CMD command to compile the .cpp file
    string command_run = ""; // CMD command to run the .exe file

    string filename; // full file name, such as example.cpp
    string filename_cutted; // file name without the .cpp suffix, such as example
    
    int return_code; // return code of the compilation command

    clock_t start,end; // record the start and end time of the running of the .exe file
    double elapsed_seconds; // time used to run the .exe file
    if (argc >= 2)
    {
        //only set the file name when there a parament is given in the terminal
        filename = argv[1];
    }

    if (filename == "-h" || argc < 2)
    {
        // if the option is "-h" or there is no options at all, show the help text
        cout << "Xgcc Version 0.0.0\n";
        cout << "Usage: xgcc file-name [-options]\n";
        cout << "-c only compile\n";
        cout << "-r only run\n";
        cout << "-h show help\n";
        cout << "Github: https://github.com/askformeal/xgcc";
        return 0;
    }
    
    if (argc > 3)
    {
        // show an error massage is there's more than 3 arguments
        cout << "*Error:*\n\tToo many arguments\n";
        return 0;
    }
    else if (argc == 3)
    {
        option = argv[2];
        
        if (option == "-c")
        {
            if_run = false;
        }
        else if (option == "-r")
        {
            if_compile = false;
        }
        else
        {
            // if the option isn't "-c" or "-r", show an error massage
            cout << "*Error:*\n\tWrong index, enter \"xgcc -h for help\"\n";
            return 0;
        }
    }

    if (filename.length() < 4 || filename.substr(filename.length()-4,4) != ".cpp")
    {
        //if the file name didn't include the .cpp suffix, add one to the end
        filename = filename + ".cpp";
    }

    filename_cutted = filename.substr(0,filename.length()-4); // generate file name without suffix

    if (if_compile)
    {
        
        check_file_exist(filename); // check if the .cpp file exist in the current folder

        command_compile = ""; // there will be an odd BUG if I don't add this line, and I don't know why

        command_compile += "g++ -o "; // generate CMD command
        command_compile += filename.substr(0,filename.length()-4);
        command_compile += " ";
        command_compile += filename;
        
        return_code = system(command_compile.c_str());
        // Note: system function don't accept strings
    
        if (return_code != 0)
        {
            // show an error massage if the return code is not 0
            cout << "\n*Error:*\n\tCompilation failed\n";
            return 0;
        }
        else
        {
            cout << "*Compilation passed*\n";
        }
    }

    if (if_run)
    {
        check_file_exist(filename_cutted + ".exe"); // check if the .exe file exists in the current folder

        command_run = "";
        command_run += ".\\";
        command_run += filename_cutted;
        command_run += ".exe";
        // generate CMD command to run the .exe file
        
        cout << "*Running started*\n--------------------\n\n";   

        start = clock(); // set start time
        system(command_run.c_str());
        end = clock(); // set end time

        elapsed_seconds = double(end-start) / CLOCKS_PER_SEC; //calculate the elapsed seconds
        
        cout << "\n--------------------\n*Running completed*\nTime used: " << elapsed_seconds << " seconds.\n";
    }
    return 0;
}