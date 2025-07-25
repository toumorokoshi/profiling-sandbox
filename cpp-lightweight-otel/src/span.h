#ifndef SPAN_H
#define SPAN_H

#include "lightweight_otel.h"
#include "trace_context.h"
#include <chrono>
#include <unordered_map>
#include <vector>

namespace lightweight_otel
{

  struct SpanEvent
  {
    std::string name;
    std::chrono::steady_clock::time_point timestamp;
    std::unordered_map<std::string, std::string> attributes;
  };

  struct SpanAttribute
  {
    std::string key;
    std::string value;
    std::string type; // "string", "int64", "double", "bool"
  };

  class SpanImpl : public Span
  {
  public:
    SpanImpl(const std::string &name, const TraceContext &context, const TraceContext &parent_context = TraceContext{});
    ~SpanImpl() override = default;

    // Span interface implementation
    void SetAttribute(const std::string &key, const std::string &value) override;
    void SetAttribute(const char *key, const char *value) override;
    void SetAttribute(const std::string &key, int64_t value) override;
    void SetAttribute(const std::string &key, double value) override;
    void SetAttribute(const std::string &key, bool value) override;

    void AddEvent(const std::string &name,
                  const std::unordered_map<std::string, std::string> &attributes = {}) override;

    void SetStatus(const std::string &code, const std::string &message = "") override;
    void End() override;

    TraceContext GetContext() const override { return context_; }

    // Additional methods for internal use
    const std::string &GetName() const { return name_; }
    const TraceContext &GetParentContext() const { return parent_context_; }
    bool IsEnded() const { return ended_; }
    std::chrono::steady_clock::time_point GetStartTime() const { return start_time_; }
    std::chrono::steady_clock::time_point GetEndTime() const { return end_time_; }
    const std::vector<SpanAttribute> &GetAttributes() const { return attributes_; }
    const std::vector<SpanEvent> &GetEvents() const { return events_; }
    const std::string &GetStatusCode() const { return status_code_; }
    const std::string &GetStatusMessage() const { return status_message_; }

  private:
    std::string name_;
    TraceContext context_;
    TraceContext parent_context_;
    std::chrono::steady_clock::time_point start_time_;
    std::chrono::steady_clock::time_point end_time_;
    std::vector<SpanAttribute> attributes_;
    std::vector<SpanEvent> events_;
    std::string status_code_;
    std::string status_message_;
    bool ended_;
  };

} // namespace lightweight_otel

#endif // SPAN_H