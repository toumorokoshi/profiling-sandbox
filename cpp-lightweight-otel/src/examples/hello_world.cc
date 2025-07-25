#include "../lightweight_otel.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>

using namespace lightweight_otel;

void ProcessRequest(const std::string &request_id)
{
  auto span = StartSpan("ProcessRequest");
  span->SetAttribute("request_id", request_id);
  span->SetAttribute("user_id", static_cast<int64_t>(12345));
  span->SetAttribute("priority", "high");

  // Simulate some work
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  span->AddEvent("request_processed", {{"status", "success"}});
  span->SetStatus("OK");
  span->End();
}

void DatabaseQuery(const std::string &query)
{
  auto span = StartSpan("DatabaseQuery");
  span->SetAttribute("query", query);
  span->SetAttribute("database", "users_db");

  // Simulate database work
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  span->AddEvent("query_executed", {{"rows_returned", "10"}});
  span->SetStatus("OK");
  span->End();
}

void ExternalAPICall(const std::string &endpoint)
{
  auto span = StartSpan("ExternalAPICall");
  span->SetAttribute("endpoint", endpoint);
  span->SetAttribute("method", "GET");

  // Simulate API call
  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  span->AddEvent("api_response_received", {{"status_code", "200"}});
  span->SetStatus("OK");
  span->End();
}

int main()
{
  std::cout << "=== Lightweight OpenTelemetry C++ Tracing Example ===" << std::endl;

  // Get a tracer
  auto tracer = GetTracer("hello_world_example", "1.0.0");

  // Start a root span
  auto root_span = tracer->StartSpan("MainOperation");
  root_span->SetAttribute("operation_type", "user_request");
  root_span->SetAttribute("user_agent", "example-client");

  std::cout << "Starting main operation..." << std::endl;

  // Simulate a complex operation with multiple spans
  ProcessRequest("req-12345");

  // Get the context from the root span for child spans
  auto context = root_span->GetContext();

  // Create child spans
  auto db_span = tracer->StartSpan("DatabaseOperation", context);
  db_span->SetAttribute("operation", "read");

  DatabaseQuery("SELECT * FROM users WHERE id = 12345");

  auto api_span = tracer->StartSpan("ExternalAPIOperation", context);
  api_span->SetAttribute("service", "payment_gateway");

  ExternalAPICall("/api/v1/payments/validate");

  // End child spans
  db_span->SetStatus("OK");
  db_span->End();

  api_span->SetStatus("OK");
  api_span->End();

  // End root span
  root_span->SetStatus("OK");
  root_span->End();

  std::cout << "Operation completed successfully!" << std::endl;
  std::cout << "Trace ID: " << context.GetTraceId() << std::endl;
  std::cout << "Span ID: " << context.GetSpanId() << std::endl;

  return 0;
}