# Development

## Dependencies

- `flatc` from flatbuffers.
- `protoc` from protobuf.

## Building Schemas

[flatbuffers](https://flatbuffers.dev/) are used to store spans, tracks and
categories.

to rebuild schema, run:

```bash
flatc -o src/ --rust ./src/schema.fbs
```

## Generating Perfetto Trace Protos

Since perfetto is the expected UI to consume the output of these profiling
tools, the `perfetto_trace.proto` file is vendored over and used to generate a
library to write to that format.

To vendor, run:

```bash
cp "${PERFETTO_REPO_ROOT}/protos/perfetto/trace/perfetto_trace.proto" ./src/vendor/
```

The protos will be rebuilt as part of a bazel target.

## Rebuilding rust-analyzer bindings

```bash
bazel run @rules_rust//tools/rust_analyzer:gen_rust_project
```