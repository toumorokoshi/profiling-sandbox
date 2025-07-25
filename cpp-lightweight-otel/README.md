# Lightweight OpenTelemetry C++ Library

A lightweight, header-only OpenTelemetry compliant tracing library for C++ applications. This library provides a simplified implementation of the OpenTelemetry tracing API that can be easily integrated into C++ projects.

## Features

- **OpenTelemetry Compliant**: Implements the core OpenTelemetry tracing API
- **Header-Only**: Easy to integrate with minimal dependencies
- **Lightweight**: Minimal overhead and memory footprint
- **Thread-Safe**: Safe for use in multi-threaded applications
- **Bazel Build System**: Uses Bazel for dependency management and building
- **Comprehensive Testing**: Full test suite with Google Test

## Quick Start

### Building with Bazel

```bash
# Build the library
bazel build //src:lightweight_otel

# Run the hello world example
bazel run //src:hello_world

# Run tests
bazel test //src:lightweight_otel_test
```

### Basic Usage

```cpp
#include "lightweight_otel.h"

using namespace lightweight_otel;

int main() {
    // Get a tracer
    auto tracer = GetTracer("my_service", "1.0.0");

    // Start a span
    auto span = tracer->StartSpan("my_operation");
    span->SetAttribute("user_id", 12345);
    span->SetAttribute("operation_type", "read");

    // Do some work...

    // Add events
    span->AddEvent("work_started", {{"status", "processing"}});

    // Set status and end span
    span->SetStatus("OK");
    span->End();

    return 0;
}
```

### Nested Spans

```cpp
auto parent_span = tracer->StartSpan("parent_operation");
auto parent_context = parent_span->GetContext();

// Create child span
auto child_span = tracer->StartSpan("child_operation", parent_context);
child_span->SetAttribute("child_id", "abc123");
child_span->End();

parent_span->End();
```

## API Reference

### Tracer

The `Tracer` class is the main entry point for creating spans:

```cpp
class Tracer {
public:
    virtual std::unique_ptr<Span> StartSpan(
        const std::string& name,
        const TraceContext& parent_context = TraceContext{}) = 0;

    virtual std::string GetName() const = 0;
    virtual std::string GetVersion() const = 0;
};
```

### Span

The `Span` class represents a unit of work:

```cpp
class Span {
public:
    // Set attributes
    virtual void SetAttribute(const std::string& key, const std::string& value) = 0;
    virtual void SetAttribute(const std::string& key, int64_t value) = 0;
    virtual void SetAttribute(const std::string& key, double value) = 0;
    virtual void SetAttribute(const std::string& key, bool value) = 0;

    // Add events
    virtual void AddEvent(const std::string& name,
                         const std::unordered_map<std::string, std::string>& attributes = {}) = 0;

    // Set status
    virtual void SetStatus(const std::string& code, const std::string& message = "") = 0;

    // End the span
    virtual void End() = 0;

    // Get context
    virtual TraceContext GetContext() const = 0;
};
```

### TraceContext

The `TraceContext` class represents trace and span identifiers:

```cpp
class TraceContext {
public:
    const std::string& GetTraceId() const;
    const std::string& GetSpanId() const;
    bool IsValid() const;

    static std::string GenerateTraceId();
    static std::string GenerateSpanId();
    static TraceContext Create();
};
```

## Examples

### Hello World Example

The `hello_world` example demonstrates:

- Creating tracers and spans
- Setting attributes and events
- Nested span relationships
- Status management

Run it with:
```bash
bazel run //src:hello_world
```

### Testing

The library includes comprehensive unit tests covering:

- Tracer creation and management
- Span lifecycle and attributes
- Context propagation
- Error handling

Run tests with:
```bash
bazel test //src:lightweight_otel_test
```

## Dependencies

- **Google Test**: For unit testing
- **Flatbuffers**: For data serialization (optional)
- **Perfetto**: For trace processing (optional)

## Build Configuration

The library uses Bazel for build management. Key dependencies are automatically downloaded and configured.

### Adding to Your Project

1. Add the library as a dependency in your `WORKSPACE`:
```python
local_repository(
    name = "lightweight_otel",
    path = "path/to/cpp-lightweight-otel",
)
```

2. Add to your `BUILD` file:
```python
cc_binary(
    name = "my_app",
    srcs = ["main.cc"],
    deps = ["@lightweight_otel//src:lightweight_otel"],
)
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Run the test suite
6. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.