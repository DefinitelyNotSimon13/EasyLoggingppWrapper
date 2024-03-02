/**
 * \author Simon Blum
 * \biref A simple wrapper for easylogging++.
 * \details
 * This wrapper handles simultaneous outputs to the console and to a log file.
 * It also allows to easily log at different levels. The compiled library
 * also includes the easylogging++ library.
 * Both headers need to be added to the project, however only this header needs
 * to be included to allow for logging.
 * Easylogging++ will not be configured or initialised in this library.
 *
 * \todo
 * - More easily allow for verbosity options.
 * - Check performance -> Especially compare to std::cout.
 *
 * \copyright MIT License 2024
 **/

#include "LoggingWrapper.hpp"

namespace utils {
LoggingWrapper::~LoggingWrapper() {
  switch (this->level) {
  case LogLevel::OUT:
    std::cout << this->buffer.str();
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::INFO:
    if (this->verbose) {
      std::cout << this->prefix << this->buffer.str();
    }
    LOG(INFO) << this->prefix << this->buffer.str();
    break;
  case LogLevel::WARNING:
    std::cout << cli::YELLOW_FG << this->buffer.str() << cli::RESET;
    LOG(WARNING) << this->prefix << this->buffer.str();
    break;
  case LogLevel::ERROR:
    std::cerr << cli::ERROR << this->prefix << this->buffer.str() << cli::RESET;
    LOG(ERROR) << this->prefix << this->buffer.str();
    break;
  case LogLevel::FATAL:
    std::cerr << cli::BLACK_FG << cli::RED_BG << this->prefix
              << this->buffer.str() << cli::RESET;
    LOG(FATAL) << this->prefix << this->buffer.str();
    break;
  case LogLevel::DEBUG:
    std::cout << cli::ITALIC << cli::CYAN_FG << this->prefix
              << this->buffer.str() << cli::RESET;
    LOG(DEBUG) << this->prefix << this->buffer.str();
    break;
  }
}
LoggingWrapper &LoggingWrapper::operator<<(Manipulator manipulator) {
  manipulator(std::cout);
  this->buffer << manipulator;
  return *this;
}
} // namespace utils
