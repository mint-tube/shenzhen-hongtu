#include "common.hpp"


int main(int argc, char **argv) {
  // Setup the logging
#ifdef DEBUG
  mlog::timestamps = false;
  mlog::path = "shenzhen.log";
  mlog::level = mlog::Level::DEBUG;
  mlog::clear("shenzhen.log");
#else
  mlog::muted = true;
#endif

  if (argc != 2) {
    std::cout << "Usage: shenzhen <path>\n";
    exit(1);
  }

  state state = setup(argv[1]);
}