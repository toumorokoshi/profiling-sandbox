#ifndef CONTEXT_H
#define CONTEXT_H

#include "lightweight_otel.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace lightweight_otel
{

  class Tracer;
  class TracerImpl;

  class TracerProvider
  {
  public:
    static TracerProvider &GetInstance();
    // Get or create a tracer
    std::shared_ptr<Tracer> GetTracer(const std::string &name, const std::string &version = "");
    // Set the global tracer
    void SetTracer(std::shared_ptr<Tracer> tracer);

  private:
    TracerProvider() = default;
    std::unordered_map<std::string, std::shared_ptr<Tracer>> tracers_;
    std::shared_ptr<Tracer> global_tracer_;
  };

} // namespace lightweight_otel

#endif // CONTEXT_H