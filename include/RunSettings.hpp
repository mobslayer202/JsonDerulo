#pragma once

#define HANDLER_LOGS_ON 0
#define JSON_LOGS_ON 1

#if HANDLER_LOGS_ON == 1
#include <iostream>
#define LOG(x) std::cout << x << "\n";
// no macro overloading
#define LOGC(x, c, y) std::cout << x << c << y << "\n";
#else 
#define LOG(x)
#define LOGC(x, c, y)
#endif

#if JSON_LOGS_ON == 1
#include <iostream>
#define JLOG(x) std::cout << x << "\n";
// no macro overloading
#define JLOGC(x, c, y) std::cout << x << c << y << "\n";
#else 
#define JLOG(x)
#define JLOGC(x, c, y)
#endif