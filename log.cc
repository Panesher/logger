#include "log.h"
#include <iostream>

namespace {

#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_BOLD_RED "\033[1m\033[31m"
#define COLOR_BOLD_MAGENTA "\033[1m\033[35m"

#ifndef LOG_VERBOSITY
constexpr int LOG_VERBOSITY = INFO;
#endif

}  // namespace

Logger::Logger(int level, const std::string &file, int line,
               const std::string &function)
    : level_(level),
      file_(file),
      line_(line),
      function_(function),
      used_(false) {}

Logger::~Logger() noexcept {
  try {
#ifndef NO_LOGER_COLOR
    stream_ << COLOR_RESET;
#endif
    stream_ << std::endl;
    std::cerr << stream_.str();
  } catch (...) {
    // ¯\_(ツ)_/¯
  }
}

std::stringstream &Logger::get_underlying() {
  if (!used_) {
    used_ = true;
#ifndef NO_LOGER_COLOR
    stream_ << get_color();
#endif
    stream_ << "[" << format_level() << ":" << file_ << "(" << line_
            << "):" << function_ << "] ";
  }
  return stream_;
}

std::string Logger::format_level() const {
  switch (level_) {
    case DEBUG:
      return "DEBUG";
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case ERROR:
      return "ERROR";
    default:
      return "UNKNOWN";
  }
}

std::string Logger::get_color() const {
  switch (level_) {
    case DEBUG:
      return COLOR_GREEN;
    case INFO:
      return COLOR_BLUE;
    case WARNING:
      return COLOR_BOLD_MAGENTA;
    case ERROR:
      return COLOR_BOLD_RED;
    default:
      return COLOR_RESET;
  }
}
