#include <gtest/gtest.h>
#include "../lightweight_otel.h"
#include "../tracer.h"

using namespace lightweight_otel;

class TracerTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    tracer_ = std::make_shared<TracerImpl>("test_tracer", "1.0.0");
  }

  std::shared_ptr<TracerImpl> tracer_;
};

TEST_F(TracerTest, TracerCreation)
{
  EXPECT_EQ(tracer_->GetName(), "test_tracer");
  EXPECT_EQ(tracer_->GetVersion(), "1.0.0");
}

TEST_F(TracerTest, StartSpan)
{
  auto span = tracer_->StartSpan("test_span");
  EXPECT_NE(span, nullptr);

  auto context = span->GetContext();
  EXPECT_TRUE(context.IsValid());
  EXPECT_FALSE(context.GetTraceId().empty());
  EXPECT_FALSE(context.GetSpanId().empty());
}

TEST_F(TracerTest, StartSpanWithParent)
{
  auto parent_span = tracer_->StartSpan("parent_span");
  auto parent_context = parent_span->GetContext();

  auto child_span = tracer_->StartSpan("child_span", parent_context);
  auto child_context = child_span->GetContext();

  EXPECT_EQ(child_context.GetTraceId(), parent_context.GetTraceId());
  EXPECT_NE(child_context.GetSpanId(), parent_context.GetSpanId());
}

TEST_F(TracerTest, MultipleSpans)
{
  auto span1 = tracer_->StartSpan("span1");
  auto span2 = tracer_->StartSpan("span2");

  auto context1 = span1->GetContext();
  auto context2 = span2->GetContext();

  EXPECT_NE(context1.GetTraceId(), context2.GetTraceId());
  EXPECT_NE(context1.GetSpanId(), context2.GetSpanId());
}