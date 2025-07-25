load("@rules_rust//rust:defs.bzl", "rust_binary", "rust_test")
load("@rules_rust//proto/prost:defs.bzl", "rust_prost_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

rust_binary(
    name = "profiling_sandbox",
    srcs = glob(["src/*.rs"]),
    edition = "2021",
    version = "0.1.0",
    deps = [
        ":perfetto_trace_rust",
        "@crates_io//:flatbuffers",
        "@crates_io//:libbpf-rs",
        "@crates_io//:prost",
    ],
)

rust_test(
    name = "profiling_sandbox_test",
    crate = ":profiling_sandbox",
)

proto_library(
    name = "perfetto_trace",
    srcs = ["src/vendor/perfetto_trace.proto"],
)

rust_prost_library(
    name = "perfetto_trace_rust",
    proto = ":perfetto_trace",
)
