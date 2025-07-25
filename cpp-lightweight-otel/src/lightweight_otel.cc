#include "lightweight_otel.h"
#include "context.h"

namespace lightweight_otel
{

  std::shared_ptr<Tracer> GetTracer(const std::string &name, const std::string &version)
  {
    return TracerProvider::GetInstance().GetTracer(name, version);
  }

  std::unique_ptr<Span> StartSpan(const std::string &name, const TraceContext &parent_context)
  {
    auto tracer = GetTracer("default");
    return tracer->StartSpan(name, parent_context);
  }

} // namespace lightweight_otel