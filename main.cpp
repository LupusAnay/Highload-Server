//
// Created by LupusAnay on 25.08.17.
//

#include <iostream>
#include "Server.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Checking for arguments
    if (argc != 3) {
        cerr << "Usage: Highload_Server <port> <thread count>" << endl;
        return 2;
    } else {
        Server server(static_cast<unsigned short>(stoi(argv[1])), static_cast<unsigned short>(stoi(argv[2])));
        cin.get();
    }
    return 0;
}