#pragma once

#include <sstream>

constexpr int DEBUG = 0;
constexpr int INFO = 1;
constexpr int WARNING = 2;
constexpr int ERROR = 3;

class Logger {
 public:
  explicit Logger(int level, const std::string &file, int line,
                  const std::string &function);

  template <class T>
  Logger &operator<<(const T &t) {
    get_underlying() << t;
    return *this;
  }

  ~Logger() noexcept;

 private:
  const int level_;
  const int line_;
  const std::string file_;
  const std::string function_;
  std::stringstream stream_;

  bool used_;

  std::stringstream &get_underlying();

  std::string format_level() const;
  std::string get_color() const;
};

#define LOG(level) \
  if (LOG_VERBOSITY <= level) Logger(level, __FILE__, __LINE__, __FUNCTION__)
