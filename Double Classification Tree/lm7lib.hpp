//
//  lm7lib.hpp
//  tetris
//
//  Created by LegitMichel777 on 12/12/18.
//  Copyright © 2018 LegitMichel777. All rights reserved.
//

#ifndef lm7lib_hpp
#define lm7lib_hpp

#include <stdio.h>
#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <bitset>
#include <functional>
#include <utility>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <memory>
#include <scoped_allocator>
#include <climits>
#include <cfloat>
#include <cstdint>
#include <cinttypes>
#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cfenv>
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <iomanip>
#include <streambuf>
#include <locale>
#include <codecvt>
#include <regex>
#include <atomic>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>
#include <time.h>
typedef long long ll;
using namespace std;
void nein(char &in); //No Enter INput
void nein(string &in);
void nein(ll &in);
bool isprime(ll x);
void clearfile(string path);
void mswait(ll x);
string add(string in,string in2);
string multiply(string in,string in2);
string factorial(ll x);
string power(ll x,unsigned long long y);
unsigned long long uhash(string x,ll base);
string uinfhash(string x,ll base);
#endif /* lm7lib_hpp */
