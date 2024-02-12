load("@rules_rust//rust:defs.bzl", "rust_binary")
load("@rules_rust//proto/prost:defs.bzl", "rust_prost_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

rust_binary(
    name = "profiling_sandbox",
    srcs = glob(["src/*.rs"]),
    edition = "2021",
    version = "0.1.0",
    deps = [
        "@crates_io//:flatbuffers",
    ],
)

proto_library(
    name = "perfetto_trace",
    srcs = ["src/vendor/perfetto_trace.proto"],
)

rust_prost_library(
    name = "perfetto_trace_rust",
    proto = ":perfetto_trace",
)
