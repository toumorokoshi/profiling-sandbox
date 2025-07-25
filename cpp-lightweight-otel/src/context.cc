#include "context.h"
#include "tracer.h"

namespace lightweight_otel
{

  TracerProvider &TracerProvider::GetInstance()
  {
    static TracerProvider instance;
    return instance;
  }

  std::shared_ptr<Tracer> TracerProvider::GetTracer(const std::string &name, const std::string &version)
  {
    std::string key = name + ":" + version;
    auto it = tracers_.find(key);
    if (it != tracers_.end())
    {
      return it->second;
    }
    auto tracer = std::make_shared<TracerImpl>(name, version);
    tracers_[key] = tracer;
    if (!global_tracer_)
    {
      global_tracer_ = tracer;
    }
    return tracer;
  }

  void TracerProvider::SetTracer(std::shared_ptr<Tracer> tracer)
  {
    global_tracer_ = tracer;
    tracers_["default:"] = tracer;
  }

} // namespace lightweight_otel