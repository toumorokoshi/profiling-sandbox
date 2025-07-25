#ifndef TRACE_CONTEXT_H
#define TRACE_CONTEXT_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

namespace lightweight_otel
{

  class TraceContext
  {
  public:
    TraceContext() = default;
    TraceContext(const std::string &trace_id, const std::string &span_id)
        : trace_id_(trace_id), span_id_(span_id) {}

    const std::string &GetTraceId() const { return trace_id_; }
    const std::string &GetSpanId() const { return span_id_; }

    void SetTraceId(const std::string &trace_id) { trace_id_ = trace_id; }
    void SetSpanId(const std::string &span_id) { span_id_ = span_id; }

    bool IsValid() const { return !trace_id_.empty() && !span_id_.empty(); }

    // Generate a new trace ID
    static std::string GenerateTraceId();

    // Generate a new span ID
    static std::string GenerateSpanId();

    // Create a new context with generated IDs
    static TraceContext Create();

  private:
    std::string trace_id_;
    std::string span_id_;
  };

} // namespace lightweight_otel

#endif // TRACE_CONTEXT_H