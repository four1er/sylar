#include "log.h"
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <time.h>

namespace sylar {

const char *LogLevel::ToString(LogLevel::Level level) {
  switch (level) {
#define XX(name)                                                               \
  case LogLevel::name:                                                         \
    return #name;                                                              \
    break;
    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
  default:
    return "UNKNOW";
  }
  return "UNKNOW";
}

LogEventWrap::LogEventWrap(LogEvent::ptr e) : m_event(e) {}

LogEventWrap::~LogEventWrap() {
  m_event->getLogger()->log(m_event->getLevel(), m_event);
}

void LogEvent::format(const char *fmt, ...) {
  va_list al;
  va_start(al, fmt);
  format(fmt, al);
  va_end(al);
}

void LogEvent::format(const char *fmt, va_list al) {
  char *buf = nullptr;
  int len = vasprintf(&buf, fmt, al);
  if (len != -1) {
    m_ss << std::string(buf, len);
    free(buf);
  }
}

std::stringstream &LogEventWrap::getSS() { return m_event->getSS(); }

class MessageFormatItem : public LogFormatter::FormatItem {};

} // namespace sylar