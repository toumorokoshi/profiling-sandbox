#include "tracer.h"
#include "trace_context.h"

namespace lightweight_otel
{

  TracerImpl::TracerImpl(const std::string &name, const std::string &version)
      : name_(name), version_(version)
  {
  }

  std::unique_ptr<Span> TracerImpl::StartSpan(
      const std::string &name,
      const TraceContext &parent_context)
  {
    TraceContext context;
    if (parent_context.IsValid())
    {
      // Use parent's trace ID, generate new span ID
      context.SetTraceId(parent_context.GetTraceId());
      context.SetSpanId(TraceContext::GenerateSpanId());
    }
    else
    {
      // Create new trace and span IDs
      context = TraceContext::Create();
    }
    return std::make_unique<SpanImpl>(name, context, parent_context);
  }

} // namespace lightweight_otel