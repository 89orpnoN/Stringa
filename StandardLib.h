//
// Created by Nonpro98 on 03/12/2023.
//

#ifndef SABAKUS_CPP_SUPERLIB_STANDARDLIB_H
#define SABAKUS_CPP_SUPERLIB_STANDARDLIB_H
#include <iostream>


template<class... Args>
void print(Args... args)
{
    (std::cout << ... << args) << "\n";
}

template<class... Args>
std::string input(Args... args)
{
    (std::cout << ... << args) << "\n";
    std::string pollo;
    char ch;
    loop1:
        if((ch = getchar()) == '\n') return pollo;
        pollo+=ch;
    goto loop1;

}



#endif //SABAKUS_CPP_SUPERLIB_STANDARDLIB_H
