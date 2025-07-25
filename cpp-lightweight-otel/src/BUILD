cc_library(
    name = "lightweight_otel",
    srcs = [
        "tracer.cc",
        "span.cc",
        "context.cc",
        "trace_context.cc",
        "lightweight_otel.cc",
    ],
    hdrs = [
        "tracer.h",
        "span.h",
        "context.h",
        "trace_context.h",
        "lightweight_otel.h",
    ],
    includes = ["."],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "hello_world",
    srcs = ["examples/hello_world.cc"],
    deps = [
        ":lightweight_otel",
    ],
)

cc_test(
    name = "lightweight_otel_test",
    srcs = [
        "tests/tracer_test.cc",
        "tests/span_test.cc",
        "tests/context_test.cc",
    ],
    deps = [
        ":lightweight_otel",
        "@googletest//:gtest_main",
    ],
)