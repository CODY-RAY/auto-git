//
//  main.cpp
//  auto-git
//
//  Created by Ray's macbook on 5/13/18.
//  Copyright © 2018 crank. All rights reserved.test
//
#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <algorithm>
namespace bp = boost::process;
namespace fs = boost::filesystem;
using namespace std;

void make_cron(vector<string> list){
    ofstream myfile;
    myfile.open(".com_cron_tmp_code");
    for(auto lis : list)
        myfile << lis +"\n";
    myfile.close();
    bp::child c("crontab .com_cron_tmp_code");
    c.wait_for(chrono::seconds(4));
    c.terminate();
    remove(".com_cron_tmp_code");
}
vector<string> read_outline()
{
    bp::ipstream is; //reading pipe-stream
    bp::child c("crontab -l", bp::std_out > is);
    vector<string> data;
    string line;
    while (c.running() && std::getline(is, line) && !line.empty())
        data.push_back(line);
    c.wait();
    return data;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    string x, name;
    bp::opstream in;
    bp::ipstream out;
    auto list = read_outline();
    if (argc > 1 && ((string(argv[1]) == "-removeOld") || (string(argv[1]) == "-r"))){
        for_each(list.begin(), list.end(), [&](const string& n) {
            auto x = n.find(" -C ") + 4;
            if(x < n.length()){
                if(!fs::is_directory(n.substr(x))){
                    list.erase(remove(list.begin(), list.end(), n), list.end());
                }
            }
        });
    make_cron(list);
    
    }else{
        // checks for cron
        if(bp::search_path("cron") != ""){
            fs::path _path = fs::current_path();
            _path =  _path / ".git";
            //main if
            if (is_directory(_path) ){
                list.push_back(  "0,16,31,46 * * * * git -C "+ fs::current_path().string() +" pull ");
                //remove doubles
                std::sort(list.begin(), list.end());
                auto last = std::unique(list.begin(), list.end());
                list.erase(last, list.end());
                //write to a cron
                make_cron(list);
            }else {
                cout<<"Fatal: Not a git repository: .git \n";
            }
        }
        else{
            cout<<"Fatal: Please add cron\n ";
        }
    }
    return 0;
}
