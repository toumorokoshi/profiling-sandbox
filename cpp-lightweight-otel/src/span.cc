#include "span.h"
#include <sstream>

namespace lightweight_otel
{

  SpanImpl::SpanImpl(const std::string &name, const TraceContext &context, const TraceContext &parent_context)
      : name_(name), context_(context), parent_context_(parent_context), start_time_(std::chrono::steady_clock::now()), ended_(false)
  {
  }

  void SpanImpl::SetAttribute(const std::string &key, const std::string &value)
  {
    attributes_.push_back({key, value, "string"});
  }

  void SpanImpl::SetAttribute(const std::string &key, int64_t value)
  {
    attributes_.push_back({key, std::to_string(value), "int64"});
  }

  void SpanImpl::SetAttribute(const std::string &key, double value)
  {
    std::ostringstream oss;
    oss << value;
    attributes_.push_back({key, oss.str(), "double"});
  }

  void SpanImpl::SetAttribute(const std::string &key, bool value)
  {
    attributes_.push_back({key, value ? "true" : "false", "bool"});
  }

  void SpanImpl::SetAttribute(const char *key, const char *value)
  {
    SetAttribute(std::string(key), std::string(value));
  }

  void SpanImpl::AddEvent(const std::string &name,
                          const std::unordered_map<std::string, std::string> &attributes)
  {
    SpanEvent event;
    event.name = name;
    event.timestamp = std::chrono::steady_clock::now();
    event.attributes = attributes;
    events_.push_back(event);
  }

  void SpanImpl::SetStatus(const std::string &code, const std::string &message)
  {
    status_code_ = code;
    status_message_ = message;
  }

  void SpanImpl::End()
  {
    if (!ended_)
    {
      end_time_ = std::chrono::steady_clock::now();
      ended_ = true;
    }
  }

} // namespace lightweight_otel