//
//  main.cpp
//  auto-git
//
//  Created by Ray's macbook on 5/13/18.
//  Copyright © 2018 crank. All rights reserved.
//

#include <iostream>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include <string>

namespace bp = boost::process;
namespace fs = boost::filesystem;

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    bp::opstream in;
    bp::ipstream out;
    fs::path _path = fs::current_path();
    _path =  _path / ".git";
    //main if
    if (is_directory(_path) ){
        bp::child c("crontab ", bp::std_out > out, bp::std_in < in);
        in << "0,16,31,46 * * * * git -C "+ fs::current_path().string() +"pull"<< endl ;
        c.terminate();
    }else {
        cout<<"fatal: Not a git repository: .git \n";
    }
    return 0;
}

