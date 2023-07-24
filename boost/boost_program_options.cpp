#ifdef TEST_BOOST_RTREE

    #include <boost/program_options.hpp>
//#include <fstream>

using namespace std;
using namespace boost::program_options;

// namespace po = boost::program_options;
// boost::program_options和boost::property_tree

int po_commandline(int argc, char* argv[]);

int po_commandline_options_description(int argc, char* argv[]);

void po_config_file();

// VS设置命令行参数：项目—>属性—>配置属性—>调试—>命令参数
int boost_program_options(int argc, char* argv[])
{
    if (false)
        po_commandline(argc, argv); // 这里没有设置短名，-h会抛出异常

    po_commandline_options_description(argc, argv);

    po_config_file();

    return 0;
}

/*
格式说明：
--help
--filename a.txt 或者--filename = a.txt
*/
int po_commandline(int argc, char* argv[])
{
    // option_description ?
    options_description opts("demo options");

    // 1 添加选项
    // 语法：add_options返回一个对象,再调用此对象的operator(),operator()返回自身引用,如此往复
    opts.add_options()("help", "just a help info")("filename", value<string>(), "to find a file");

    // 2 解析并存储选项-值
    variables_map vm; // 继承std::map
    store(parse_command_line(argc, argv, opts), vm);

    // 3
    if (vm.count("help")) // 打印所有选项的帮助(2)
    {
        cout << opts << endl;
        return 0;
    }

    if (vm.count("filename"))
    {
        cout << vm["filename"].as<string>() << endl;
    }

    if (vm.empty())
    {
        cout << "no options" << endl;
    }

    return 0;
}

// 选项描述器
// -f readme.txt --dir d1 d2 --depth
int po_commandline_options_description(int argc, char* argv[])
{
    options_description opts("demo options");

    string filename;

    opts.add_options()("help,h", "help message\n	a bit of long text")
        // 默认值
        ("filename,f", value<string>(&filename)->default_value("test"), "to find a file")
        // 可多次出现，接受多个记号
        ("dir,D", value<vector<string>>()->multitoken(), "search dir")
        // 隐含值
        ("depth,d", value<int>()->implicit_value(5), "search depth");

    variables_map vm;
    store(parse_command_line(argc, argv, opts), vm);

    // 通知variables_map更新所有关联的外部变量
    notify(vm);

    // print_vm(opts, vm);
    {
        if (vm.empty())
        {
            cout << opts << endl;
            return 0;
        }

        if (vm.count("help"))
        {
            cout << opts << endl;
            return 0;
        }

        // 有默认值
        cout << "filename opt: " << vm["filename"].as<string>() << endl;

        //
        if (vm.count("dir"))
        {
            cout << "dir opt: ";
            for (auto& str : vm["dir"].as<vector<string>>())
            {
                cout << str << ",";
            }
            cout << endl;
        }

        //
        if (vm.count("depth"))
            cout << "depth opt: " << vm["depth"].as<int>() << endl;
    }

    return 0;
}

// 解析配置文件
// 配置文件中：采用Key=Value形式，必须用长名，多个记号可以用","或空格分开
void po_config_file()
{
    options_description opts("demo options");

    string filename;

    opts.add_options()("help,h", "help message\n	a bit of long text")
        // 默认值
        ("filename,f", value<string>(&filename)->default_value("test"), "to find a file")
        // 可多次出现，接受多个记号
        ("dir,D", value<vector<string>>()->multitoken(), "search dir");

    //
    variables_map vm;
    try
    {
        store(parse_config_file<char>("C:\\Users\\Administrator\\Desktop\\Test.ini", opts, true), vm);
    } catch (const std::exception& e)
    {
        cout << e.what() << endl;
        return;
    }

    if (vm.count("filename"))
    {
        cout << "filename opt: " << vm["filename"].as<string>() << endl;
    }

    if (vm.count("dir"))
    {
        cout << "dir opt: ";
        for (auto& str : vm["dir"].as<vector<string>>())
        {
            cout << str << ",";
        }
        cout << endl;
    }
}
#endif // TEST_BOOST_RTREE