#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <fstream>

using namespace std;

string version = "2.0.2"; //中文版

filesystem::path file_path;
filesystem::path exe_path;

string compile_command;
string run_command;
string del_command;

vector<string> ops;
vector<string> args;

vector<string> config;

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
    system("chcp 65001 > nul")
    if (!check_gpp())
    {
        return -1;
    }

    if (argc == 1)
    {
        print_help();
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            ops.push_back(argv[i]);
        }
        else if (i != 1)
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
    if (tmp[0] == '-')
    {
        cout << "未找到输入文件\n";
        return -1;
    }
    tmp = get_lower(tmp);
    size_t pos = tmp.find(".cpp");
    
    if (pos != tmp.size() - 4 || tmp.size() <= 4)
    {
        tmp = tmp + ".cpp";
    }
    file_path = tmp;

    if (!filesystem::exists(file_path))
    {
        cout << "文件\"" << file_path.string() << "\"不存在\n";
        return -1;
    }

    tmp = tmp.replace(tmp.size() - 4, 4, ".exe");
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
    cout << "编译中...\n";

    auto start = chrono::high_resolution_clock::now();

    code1 = system(compile_command.c_str());
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    if (code1 == 0)
    {
        cout << "编译通过，用时" << duration.count() << "秒\n";
    }
    else
    {
        cout << "编译失败\n\n";
        return -1;
    }
    if (run)
    {
        string exe_name = exe_path.filename().string();
        cout << "正在执行\"" << exe_name <<"\"...\n----------------\n";

        start = chrono::high_resolution_clock::now();

        code2 = system(run_command.c_str());

        end = chrono::high_resolution_clock::now();
        duration = end - start;

        if (code2 == 0)
        {
            cout << "\n----------------\n执行成功，用时" << duration.count() << "秒\n";
        }
        else
        {
            cout << "\n----------------\n运行时错误，返回值：" << code2 << '\n';
            return -1;
        }
        if (!retain)
        {
            code3 = system(del_command.c_str());
            if (code3 != 0)
            {
                cout << "未能删除可执行文件";
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
    cout << "格式\n";
    cout << "    xgcc [文件名] [参数1，参数2……]\n";
    cout << "    xgcc -h\n";
    cout << "    xgcc -help\n";
    cout << "“-”开头的参数会被视作选项，其余的会被传入可执行文件。";
    cout << "选项\n";
    cout << "    -R 运行后保留可执行文件\n";
    cout << "    -O1 使用O1优化\n";
    cout << "    -O2 使用O2优化\n";
    cout << "    -O3 使用O3优化\n";
    cout << "    -C 仅编译\n";
    cout << "    -V/-VERSION 显示版本信息\n";
    cout << "    -H/-HELP 显示帮助信息\n";
}

void print_version()
{
    cout << "XGCC版本" << version << "\n";
    cout << "    by Demons1014\n";
    cout << "Github仓库：https://github.com/askformeal/xgcc\n\n";
    cout << "如需反馈，请通过以下方式联系我：\n";
    cout << "    在洛谷上私信@demons1014：https://www.luogu.com.cn/chat?uid=787042\n";
    cout << "    发邮件到zeus1014_2023@163.com\n";
    cout << "    创建一个新Issue：https://github.com/askformeal/xgcc/issues\n\n";
    cout << "感谢您的反馈，感谢您使用XGCC\n";
}

bool check_gpp()
{
    int code = system("g++ --version > nul");
    if (code != 0)
    {
        cout << "未安装g++编译器\n";
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
        cout << "可执行文件将被保留\n";
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
        cout << "未找到选项：\"" << ops[i] << "\"\n";
        return -1;
    }
}