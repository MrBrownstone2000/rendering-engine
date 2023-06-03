#ifndef __MACROS_HPP__
#define __MACROS_HPP__

#define M_STR(expr) #expr

#define watch(expr) watchValue((expr), M_STR(expr))

#endif
