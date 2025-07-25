#ifndef TRACER_H
#define TRACER_H

#include "lightweight_otel.h"
#include "span.h"
#include <memory>
#include <string>

namespace lightweight_otel
{

  class TracerImpl : public Tracer
  {
  public:
    TracerImpl(const std::string &name, const std::string &version = "");
    ~TracerImpl() override = default;

    // Tracer interface implementation
    std::unique_ptr<Span> StartSpan(
        const std::string &name,
        const TraceContext &parent_context = TraceContext{}) override;

    std::string GetName() const override { return name_; }
    std::string GetVersion() const override { return version_; }

  private:
    std::string name_;
    std::string version_;
  };

} // namespace lightweight_otel

#endif // TRACER_H