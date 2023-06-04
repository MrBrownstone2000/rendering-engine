#ifndef __MACROS_HPP__
#define __MACROS_HPP__

#define M_STR(expr) #expr
#define M_BIT(n) (1 << n)

#define watch(expr) watchValue((expr), M_STR(expr))

#endif
