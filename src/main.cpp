#include "common.hpp"


int main() {
#ifdef DEBUG
  mlog::timestamps = false;
  mlog::path = "hongtu.log";
  mlog::level = mlog::Level::DEBUG;
  mlog::clear("shenzhen.log");
#else
  mlog::muted = true;
#endif


}