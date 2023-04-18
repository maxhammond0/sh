#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/asio/ip/host_name.hpp>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void prompt() {
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char cwd[FILENAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    getcwd(cwd, FILENAME_MAX);
    
    cout << "\033[1;32m" << username << "@" << hostname << "\033[0m";
    cout << " ";
    cout << "\033[1;36m" << cwd << "\033[0m";
    cout << " >> ";
}


int main(void) {
    
    string response;

    while (true) {
        prompt();
        cin >> response;

        if (response == "exit") {
            return 0;
        }
    }

    return 0;
}
