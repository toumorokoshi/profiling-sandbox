// Auto-generated FlatBuffer schema for trace data
// This is a simplified version for the lightweight OpenTelemetry library

#ifndef FLATBUFFER_SCHEMA_GENERATED_H
#define FLATBUFFER_SCHEMA_GENERATED_H

#include "flatbuffers/flatbuffers.h"

namespace lightweight_otel
{

  // Simple trace event structure
  struct TraceEvent
  {
    std::string name;
    std::string trace_id;
    std::string span_id;
    std::string parent_span_id;
    uint64_t start_time_ns;
    uint64_t end_time_ns;
    std::unordered_map<std::string, std::string> attributes;
  };

  // Trace data container
  struct TraceData
  {
    std::vector<TraceEvent> events;
    std::string service_name;
    std::string service_version;
  };

} // namespace lightweight_otel

#endif // FLATBUFFER_SCHEMA_GENERATED_H