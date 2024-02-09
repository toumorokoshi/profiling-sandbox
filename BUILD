load("@rules_rust//rust:defs.bzl", "rust_binary")

package(default_visibility = ["//visibility:public"])

rust_binary(
    name = "profiling_sandbox",
    srcs = glob(["src/*.rs"]),
    edition = "2021",
    version = "0.1.0",
    deps = [
        "@crate_index//:flatbuffers",
    ],
)
