#include <gtest/gtest.h>
#include "../lightweight_otel.h"
#include "../context.h"
#include "../tracer.h"

using namespace lightweight_otel;

class ContextTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    provider_ = &TracerProvider::GetInstance();
  }

  TracerProvider *provider_;
};

TEST_F(ContextTest, GetTracer)
{
  auto tracer = provider_->GetTracer("test_tracer", "1.0.0");
  EXPECT_NE(tracer, nullptr);
  EXPECT_EQ(tracer->GetName(), "test_tracer");
  EXPECT_EQ(tracer->GetVersion(), "1.0.0");
}

TEST_F(ContextTest, GetSameTracer)
{
  auto tracer1 = provider_->GetTracer("same_tracer", "1.0.0");
  auto tracer2 = provider_->GetTracer("same_tracer", "1.0.0");

  EXPECT_EQ(tracer1, tracer2);
}

TEST_F(ContextTest, GetDifferentTracers)
{
  auto tracer1 = provider_->GetTracer("tracer1", "1.0.0");
  auto tracer2 = provider_->GetTracer("tracer2", "1.0.0");

  EXPECT_NE(tracer1, tracer2);
  EXPECT_EQ(tracer1->GetName(), "tracer1");
  EXPECT_EQ(tracer2->GetName(), "tracer2");
}

TEST_F(ContextTest, GetTracerWithDifferentVersions)
{
  auto tracer1 = provider_->GetTracer("versioned_tracer", "1.0.0");
  auto tracer2 = provider_->GetTracer("versioned_tracer", "2.0.0");

  EXPECT_NE(tracer1, tracer2);
  EXPECT_EQ(tracer1->GetVersion(), "1.0.0");
  EXPECT_EQ(tracer2->GetVersion(), "2.0.0");
}

TEST_F(ContextTest, SetTracer)
{
  auto custom_tracer = std::make_shared<TracerImpl>("custom_tracer", "1.0.0");
  provider_->SetTracer(custom_tracer);

  // The global tracer should now be the custom tracer
  auto global_tracer = provider_->GetTracer("default");
  EXPECT_EQ(global_tracer->GetName(), "custom_tracer");
}

TEST_F(ContextTest, GetTracerWithoutVersion)
{
  auto tracer = provider_->GetTracer("no_version_tracer");
  EXPECT_NE(tracer, nullptr);
  EXPECT_EQ(tracer->GetName(), "no_version_tracer");
  EXPECT_EQ(tracer->GetVersion(), "");
}

TEST_F(ContextTest, TracerSingleton)
{
  auto &provider1 = TracerProvider::GetInstance();
  auto &provider2 = TracerProvider::GetInstance();

  EXPECT_EQ(&provider1, &provider2);
}

TEST_F(ContextTest, TracerSpans)
{
  auto tracer = provider_->GetTracer("span_test_tracer");
  auto span = tracer->StartSpan("test_span");

  EXPECT_NE(span, nullptr);
  auto context = span->GetContext();
  EXPECT_TRUE(context.IsValid());
}

TEST_F(ContextTest, MultipleTracersWithSpans)
{
  auto tracer1 = provider_->GetTracer("tracer1");
  auto tracer2 = provider_->GetTracer("tracer2");

  auto span1 = tracer1->StartSpan("span1");
  auto span2 = tracer2->StartSpan("span2");

  auto context1 = span1->GetContext();
  auto context2 = span2->GetContext();

  // Different tracers should create different trace contexts
  EXPECT_NE(context1.GetTraceId(), context2.GetTraceId());
}