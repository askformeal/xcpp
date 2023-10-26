#include<bits/stdc++.h>
    
using namespace std;

// Xgcc Version 1.1.0
// Author: @askformeal github.com
// Oh please! It's hard to register a user name on github 


// This program only work in Windows System
// compile this file using "g++ -o xgcc xgcc.cpp" and push xgcc.exe into C:\Windows\System32 folder



void show_help()
{
    // show help text
    // if the option is "-h" or there is no options at all, show the help text
    cout << "Xgcc Version 1.1.0\n";
    cout << "Usage: xgcc file-name [-options]\n";
    cout << "-c Only compile\n";
    cout << "-r Only run\n";
    cout << "-h Show help\n";
    cout << "-o2 Use o2 optimization when compile\n";
    cout << "-d Delete the .exe file after run it\n";
    cout << "Github: https://github.com/askformeal/xgcc";
    exit(0);
}

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
    //const int max_args = 5; // max CMD arguments allowed // remove argument number check for now

    string option;  
    
    bool if_compile = true; // whether to compile the .cpp file
    bool if_run = true; // whether to run the .exe file

    bool o2; // wether to use o2 optimization

    bool del_exe; // whether to delete the .exe file after run it

    string cmd_command; // CMD command to run

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
        show_help();
    }   
    
    /*if (argc > max_args)
    {
        // show an error massage is there's more than 3 arguments
        cout << "*Error:*\n\tToo many arguments\n";
        return 0;
    }*/

    else 
    {
        for (int i = 2; i < argc; i++)
        {
            option = argv[i];
            /*
            options about how to run the .cpp file
            -c only compile
            -r only run
            -h show help
            -o2 use o2 optimization when compile
            -d delete the .exe file after run it
            */
            if (option == "-c")
            {
                if_run = false;
            }
            else if (option == "-r")
            {
                if_compile = false;
            }
            else if (option == "-o2")
            {
                o2 = true;
            }
            else if (option == "-d")
            {
                del_exe = true;
            }
            else
            {
                // if the option isn't "-c" or "-r", show an error massage
                cout << "*Error:*\n\tWrong option, enter \"xgcc -h for help\"\n";
                return 0;
            }
        }
    }
        
    if ( (!if_run) && (!if_compile))
    {
        // if the user entered both the "-c" and "-r" options, then run and compile
        if_run = true;
        if_compile = true;
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

        cmd_command = ""; // there will be an odd BUG if I don't add this line, and I don't know why

        cmd_command += "g++ "; // generate CMD command
        if (o2)
        {
            // add -o2 to the compile command
            cmd_command += "-O2 ";
        }
        cmd_command += "-o ";
        cmd_command += filename.substr(0,filename.length()-4);
        cmd_command += " ";
        cmd_command += filename;
        
        return_code = system(cmd_command.c_str());
        // Note: system function don't accept strings
    
        if (return_code != 0)
        {
            // show an error massage if the return code is not 0
            cout << "\n*Error:*\n\tCompilation failed\n";
            return 0;
        }
        else if (o2)
        {
            cout << "*O2 Compilation passed*\n";
        }
        else
        {
            cout << "*Compilation passed*\n";
        }
    }

    if (if_run)
    {
        check_file_exist(filename_cutted + ".exe"); // check if the .exe file exists in the current folder

        cmd_command = "";
        cmd_command += ".\\";
        cmd_command += filename_cutted;
        cmd_command += ".exe";
        // generate CMD command to run the .exe file
        
        cout << "*Running started*\n--------------------\n\n";   

        start = clock(); // set start time
        system(cmd_command.c_str());
        end = clock(); // set end time

        elapsed_seconds = double(end-start) / CLOCKS_PER_SEC; //calculate the elapsed seconds
        
        cout << "\n--------------------\n*Running completed*\nTime used: " << elapsed_seconds << " seconds.\n";
        
        if (del_exe)
        {
            
            cmd_command = "";
            cmd_command += "del .\\";
            cmd_command += filename_cutted;
            cmd_command += ".exe";
            // generate CMD command to delete the .exe file
            system(cmd_command.c_str());
        }
    }
    return 0;
}
