#ifndef LIGHTWEIGHT_OTEL_H
#define LIGHTWEIGHT_OTEL_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "trace_context.h"
#include "context.h"

namespace lightweight_otel
{

  // Forward declarations
  class Span;
  class Tracer;
  class TracerProvider;

  // OpenTelemetry-compliant Span interface
  class Span
  {
  public:
    virtual ~Span() = default;

    // Set span attributes
    virtual void SetAttribute(const std::string &key, const std::string &value) = 0;
    virtual void SetAttribute(const char *key, const char *value) = 0;
    virtual void SetAttribute(const std::string &key, int64_t value) = 0;
    virtual void SetAttribute(const std::string &key, double value) = 0;
    virtual void SetAttribute(const std::string &key, bool value) = 0;

    // Add events to span
    virtual void AddEvent(const std::string &name,
                          const std::unordered_map<std::string, std::string> &attributes = {}) = 0;

    // Set span status
    virtual void SetStatus(const std::string &code, const std::string &message = "") = 0;

    // End the span
    virtual void End() = 0;

    // Get span context
    virtual TraceContext GetContext() const = 0;
  };

  // OpenTelemetry-compliant Tracer interface
  class Tracer
  {
  public:
    virtual ~Tracer() = default;

    // Start a new span
    virtual std::unique_ptr<Span> StartSpan(
        const std::string &name,
        const TraceContext &parent_context = TraceContext{}) = 0;

    // Get the tracer name
    virtual std::string GetName() const = 0;

    // Get the tracer version
    virtual std::string GetVersion() const = 0;
  };

  // Convenience functions for OpenTelemetry compatibility
  std::shared_ptr<Tracer> GetTracer(const std::string &name, const std::string &version = "");
  std::unique_ptr<Span> StartSpan(const std::string &name, const TraceContext &parent_context = TraceContext{});

} // namespace lightweight_otel

#endif // LIGHTWEIGHT_OTEL_H