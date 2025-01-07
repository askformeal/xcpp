#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>

using namespace std;

string version = "2.0.2";

filesystem::path file_path;
filesystem::path exe_path;

string compile_command;
string run_command;
string del_command;

vector<string> ops;  // the options
vector<string> args; // the arguments and file name

bool o1 = false;
bool o2 = false;
bool o3 = false;
bool retain = false;
bool run = true;

void print_help();

void print_version();

bool check_gpp();

string get_lower(string s);

int handle_op(int i);

int main(int argc, char *argv[])
{
    if (!check_gpp())
    {
        return -1;
    }

    if (argc == 1) //no argument passed to main, show help info
    {
        print_help();
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-') // all options starts with -
        {
            ops.push_back(argv[i]);
        }
        else if (i != 1) // file name will not be take as arguments
        {
            args.push_back(argv[i]);
        }
    }

    for (int i = 0; i < ops.size(); i++)
    {
        int code = handle_op(i);
        if (code == -1)
        {
            return -1;
        }
        else if (code == 1)
        {
            return 0;
        }
    }

    string tmp = argv[1];
    if (tmp[0] == '-') // if the first string after xgcc is an option, then there's no file name
    {
        cout << "No input file given\n";
        return -1;
    }
    tmp = get_lower(tmp);
    size_t pos = tmp.find(".cpp");
    
    if (pos != tmp.size() - 4 || tmp.size() <= 4) // check if the file name has a .cpp suffix
    {
        tmp = tmp + ".cpp";
    }
    file_path = tmp;

    if (!filesystem::exists(file_path))
    {
        cout << "File \"" << file_path.string() << "\" does not exist\n";
        return -1;
    }

    tmp = tmp.replace(tmp.size() - 4, 4, ".exe"); // replace the suffix
    exe_path = tmp;

    string tmp1, tmp2;
    tmp1 = file_path.string();
    tmp2 = exe_path.string();

    compile_command = "g++ -o " + tmp2 + " " + tmp1;
    if (o3)
    {
        compile_command += " -O3";
    }
    else if (o2)
    {
        compile_command += " -O2";
    }
    else if (o1)
    {
        compile_command += " -O1";
    }

    run_command = tmp2;
    for (int i = 0; i < args.size(); i++)
    {
        run_command += (" " + args[i]);
    }
        
    del_command = "del " + tmp2;


    /*cout << "compile command: " << compile_command << '\n';
    cout << "run command: " << run_command << '\n';
    cout << "del command: " << del_command << '\n';*/

    int code1, code2, code3;
    cout << "Compiling......\n";

    auto start = chrono::high_resolution_clock::now();

    code1 = system(compile_command.c_str());
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    if (code1 == 0)
    {
        cout << "Compilation completed in " << duration.count() << " seconds\n";
    }
    else
    {
        cout << "Compilation failed\n\n";
        return -1;
    }
    if (run)
    {
        string exe_name = exe_path.filename().string();
        cout << "Executing \"" << exe_name <<"\"...\n----------------\n";

        start = chrono::high_resolution_clock::now();

        code2 = system(run_command.c_str());

        end = chrono::high_resolution_clock::now();
        duration = end - start;

        if (code2 == 0)
        {
            cout << "\n----------------\nSuccessfully finished in " << duration.count() << " seconds\n";
        }
        else
        {
            cout << "\n----------------\nRuntime error, return value: " << code2 << '\n';
            return -1;
        }
        if (!retain)
        {
            code3 = system(del_command.c_str());
            if (code3 != 0)
            {
                cout << "Failed to delete executable file";
                return -1;
            }
        }
    }
    return 0;
}

string get_lower(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

void print_help()
{
    cout << "Usage\n";
    cout << "    xgcc [file name] [argument 1, argument 2...]\n";
    cout << "    xgcc -h\n";
    cout << "    xgcc -help\n";
    cout << "arguments starts with \"-\" will be taken as \"options\", while others will be passed into the executable file";
    cout << "Available options:\n";
    cout << "    -R Do not delete executable file after executing\n";
    cout << "    -O1 Use O1 optimization\n";
    cout << "    -O2 Use O2 optimization\n";
    cout << "    -O3 Use O3 optimization\n";
    cout << "    -C  Compile only\n";
    cout << "    -V/-VERSION show version information\n";
    cout << "    -H/-HELP show this help information\n";
}

void print_version()
{
    cout << "XGCC version " << version << "\n";
    cout << "    By Demons1014\n";
    cout << "Github repository: https://github.com/askformeal/xgcc\n\n";
    cout << "If you want to report a problem or give a suggestion, please connect me by:\n";
    cout << "    connect @demons1014 at https://www.luogu.com.cn/chat?uid=787042\n";
    cout << "    send an E-mail to zeus1014_2023@163.com\n";
    cout << "    create an issue at https://github.com/askformeal/xgcc/issues\n\n";
    cout << "I'll be most grateful for your feedback, and thank you for using XGCC\n";
}

bool check_gpp()
{
    int code = system("g++ --version > nul");
    if (code != 0)
    {
        cout << "No g++ compiler installed\n";
        return false;
    }
    else
    {
        return true;
    }
}

int handle_op(int i)
/*
return values:
0 = No error, continue
1 = No error, terminate
-1 = Error, terminate
*/
{
    ops[i] = get_lower(ops[i]);
    if (ops[i] == "-o1")
    {
        o1 = true;
        return 0;
    }
    else if (ops[i] == "-o2")
    {
        o2 = true;
        return 0;
    }
    else if (ops[i] == "-o3")
    {
        o3 = true;
        return 0;
    }
    else if (ops[i] == "-r")
    {
        cout << "Executable file will be retained\n";
        retain = true;
        return 0;
    }
    else if (ops[i] == "-c")
    {
        run = false;
        return 0;
    }
    else if (ops[i] == "-h" || ops[i] == "-help")
    {
        print_help();
        return 1;
    }
    else if (ops[i] == "-v" || ops[i] == "-version")
    {
        print_version();
        return 1;
    }
    else
    {
        cout << "Invalid option: \"" << ops[i] << "\"\n";
        return -1;
    }
}