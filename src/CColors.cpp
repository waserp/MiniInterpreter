#include "CColors.h"

#ifdef __LINUX__
  const char Colors::red[]= {"\033[1;31m"};
  const char Colors::green[]= {"\033[1;32m"};
  const char Colors::yellow[]= {"\033[1;33m"};
  const char Colors::white[] = {"\033[0m"};
  const char Colors::blue[]= {"\033[1;34m"};
  const char Colors::violet[]= {"\033[1;35m"};
  const char Colors::Iblue[]= {"\e[44m"};
#else
  const char Colors::red[]= {""};
  const char Colors::green[]= {""};
  const char Colors::yellow[]= {""};
  const char Colors::white[] = {""};
  const char Colors::blue[]= {""};
  const char Colors::violet[]= {""};
  const char Colors::Iblue[]= {""};


#endif
