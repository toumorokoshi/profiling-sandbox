#include <gtest/gtest.h>
#include "../lightweight_otel.h"
#include "../span.h"
#include "../trace_context.h"
#include <cstdint>

using namespace lightweight_otel;

class SpanTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    context_ = TraceContext::Create();
    span_ = std::make_unique<SpanImpl>("test_span", context_);
  }

  TraceContext context_;
  std::unique_ptr<SpanImpl> span_;
};

TEST_F(SpanTest, SpanCreation)
{
  EXPECT_EQ(span_->GetName(), "test_span");
  EXPECT_EQ(span_->GetContext().GetTraceId(), context_.GetTraceId());
  EXPECT_EQ(span_->GetContext().GetSpanId(), context_.GetSpanId());
  EXPECT_FALSE(span_->IsEnded());
}

TEST_F(SpanTest, SetStringAttribute)
{
  span_ = std::make_unique<SpanImpl>("test_span", context_); // ensure clean instance
  span_->SetAttribute("key1", "value1");
  span_->SetAttribute("key2", "value2");

  const auto &attributes = span_->GetAttributes();
  EXPECT_EQ(attributes.size(), 2);
  EXPECT_EQ(attributes[0].key, "key1");
  EXPECT_EQ(attributes[0].value, "value1");
  EXPECT_EQ(attributes[0].type, "string");
  EXPECT_EQ(attributes[1].key, "key2");
  EXPECT_EQ(attributes[1].value, "value2");
  EXPECT_EQ(attributes[1].type, "string");
}

TEST_F(SpanTest, SetInt64Attribute)
{
  span_->SetAttribute("user_id", static_cast<int64_t>(12345));
  span_->SetAttribute("count", static_cast<int64_t>(-100));

  const auto &attributes = span_->GetAttributes();
  EXPECT_EQ(attributes.size(), 2);
  EXPECT_EQ(attributes[0].key, "user_id");
  EXPECT_EQ(attributes[0].value, "12345");
  EXPECT_EQ(attributes[0].type, "int64");
  EXPECT_EQ(attributes[1].key, "count");
  EXPECT_EQ(attributes[1].value, "-100");
  EXPECT_EQ(attributes[1].type, "int64");
}

TEST_F(SpanTest, SetDoubleAttribute)
{
  span_->SetAttribute("score", 95.5);
  span_->SetAttribute("ratio", -0.75);

  const auto &attributes = span_->GetAttributes();
  EXPECT_EQ(attributes.size(), 2);
  EXPECT_EQ(attributes[0].key, "score");
  EXPECT_EQ(attributes[0].type, "double");
  EXPECT_EQ(attributes[1].key, "ratio");
  EXPECT_EQ(attributes[1].type, "double");
}

TEST_F(SpanTest, SetBoolAttribute)
{
  span_->SetAttribute("enabled", true);
  span_->SetAttribute("debug", false);

  const auto &attributes = span_->GetAttributes();
  EXPECT_EQ(attributes.size(), 2);
  EXPECT_EQ(attributes[0].key, "enabled");
  EXPECT_EQ(attributes[0].value, "true");
  EXPECT_EQ(attributes[0].type, "bool");
  EXPECT_EQ(attributes[1].key, "debug");
  EXPECT_EQ(attributes[1].value, "false");
  EXPECT_EQ(attributes[1].type, "bool");
}

TEST_F(SpanTest, AddEvent)
{
  std::unordered_map<std::string, std::string> attrs = {
      {"status", "success"},
      {"count", "10"}};

  span_->AddEvent("test_event", attrs);

  const auto &events = span_->GetEvents();
  EXPECT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].name, "test_event");
  EXPECT_EQ(events[0].attributes.size(), 2);
  EXPECT_EQ(events[0].attributes.at("status"), "success");
  EXPECT_EQ(events[0].attributes.at("count"), "10");
}

TEST_F(SpanTest, AddEventWithoutAttributes)
{
  span_->AddEvent("simple_event");

  const auto &events = span_->GetEvents();
  EXPECT_EQ(events.size(), 1);
  EXPECT_EQ(events[0].name, "simple_event");
  EXPECT_EQ(events[0].attributes.size(), 0);
}

TEST_F(SpanTest, SetStatus)
{
  span_->SetStatus("OK", "Operation completed successfully");

  EXPECT_EQ(span_->GetStatusCode(), "OK");
  EXPECT_EQ(span_->GetStatusMessage(), "Operation completed successfully");
}

TEST_F(SpanTest, SetStatusWithoutMessage)
{
  span_->SetStatus("ERROR");

  EXPECT_EQ(span_->GetStatusCode(), "ERROR");
  EXPECT_EQ(span_->GetStatusMessage(), "");
}

TEST_F(SpanTest, EndSpan)
{
  EXPECT_FALSE(span_->IsEnded());

  auto start_time = span_->GetStartTime();
  span_->End();

  EXPECT_TRUE(span_->IsEnded());
  EXPECT_GT(span_->GetEndTime(), start_time);
}

TEST_F(SpanTest, EndSpanMultipleTimes)
{
  span_->End();
  auto end_time1 = span_->GetEndTime();

  // Second call should not change the end time
  span_->End();
  auto end_time2 = span_->GetEndTime();

  EXPECT_EQ(end_time1, end_time2);
}

TEST_F(SpanTest, ParentContext)
{
  auto parent_context = TraceContext::Create();
  auto child_span = std::make_unique<SpanImpl>("child_span", context_, parent_context);

  EXPECT_EQ(child_span->GetParentContext().GetTraceId(), parent_context.GetTraceId());
  EXPECT_EQ(child_span->GetParentContext().GetSpanId(), parent_context.GetSpanId());
}