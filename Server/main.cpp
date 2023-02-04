// -----------------------------
// - IMPORT THE MAIN LIBRARIES -
// -----------------------------
#include <iostream>     // 
#include <stdio.h>      // 
// -----------------------------
// CUSTOM LIBRARIES AND SOURCE -
// -----------------------------

#define __LIBMODE_SERVER_

#include "src/Sv_Gvars.h"
#include "includes/Sv_waffledb.h"
// the main function which manages the server
int main(int argc, char *argv[]){
    std::cout<<" _ _ _     ___ ___ _           _ _   "<<std::endl;
    std::cout<<"| | | |___|  _|  _| |___ ___ _| | |_ "<<std::endl;
    std::cout<<"| | | | .'|  _|  _| | -_|___| . | . |"<<std::endl;
    std::cout<<"|_____|__,|_| |_| |_|___|   |___|___|"<<std::endl;
    std::cout<<"-------------------------------------"<<std::endl;
    std::cout<<"server version: "<<version<<std::endl;
    std::cout<<"-------------------------------------"<<std::endl;
    return 0;
}