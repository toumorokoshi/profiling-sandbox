#include "trace_context.h"
#include <chrono>

namespace lightweight_otel
{

  std::string TraceContext::GenerateTraceId()
  {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint64_t> dis;

    uint64_t value = dis(gen);
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << value;
    return ss.str();
  }

  std::string TraceContext::GenerateSpanId()
  {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint64_t> dis;

    uint64_t value = dis(gen);
    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << value;
    return ss.str();
  }

  TraceContext TraceContext::Create()
  {
    return TraceContext(GenerateTraceId(), GenerateSpanId());
  }

} // namespace lightweight_otel