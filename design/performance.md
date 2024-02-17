# Performance

## Usage of Flatbuffers

Flatbuffers should enable an overall savings when one serializes and
deserialized a message once, even over protobuf as a fairly lightweight protocol.

See the following benchmarks:

```
test perfetto::tests::bench_protobuf                       ... bench:     151,362 ns/iter (+/- 62,880)
test perfetto::tests::bench_protobuf_serialize             ... bench:     496,830 ns/iter (+/- 76,756)
test perfetto::tests::bench_protobuf_serialize_deserialize ... bench:   3,223,113 ns/iter (+/- 1,624,191)
test tests::bench_flatbuffer                               ... bench:     554,712 ns/iter (+/- 28,256)
test tests::bench_flatbuffer_serialize_deserialize         ... bench:     912,636 ns/iter (+/- 173,679)
```