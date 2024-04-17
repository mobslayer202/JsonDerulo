#pragma once

#define LOGS_ON 1

#if LOGS_ON == 1
#include <iostream>
#define LOG(x) std::cout << x << "\n";
// no macro overloading
#define LOGC(x, c, y) std::cout << x << c << y << "\n";
#else 
#define LOG(x)
#define LOGC(x, c, y)
#endif