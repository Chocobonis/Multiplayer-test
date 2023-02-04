#include <iostream>

int main (){
    std::cout<<"This is a file loading test from emscripten:"<<std::endl;
    emscripten_async_wget_data("test.txt", 0, onLoad, onError);
    
    return 0;
}