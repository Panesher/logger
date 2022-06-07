#include "log.h"

void call_loger(int a) {
  for (int i = 0; i < 10; ++i) {
    LOG(DEBUG) << "Some debug log " << i << " | " << a;
    LOG(INFO) << "Some info " << i << " | " << a;
    LOG(WARNING) << "Some warning log " << i << " | " << a;
    LOG(ERROR) << "Some error " << i << " | " << a;
  }
}

int main() {
  SET_LOG_LEVEL_VERBOSITY(DEBUG);
  // SET_LOG_LEVEL_VERBOSITY(155); would LOG(ERROR)
  // SET_LOG_LEVEL_VERBOSITY(DEBUG); would LOG(ERROR)
  call_loger(1);
}
