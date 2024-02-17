# Performance

## Usage of Flatbuffers

Flatbuffers should enable an overall savings when one serializes and
deserialized a message once, even over protobuf as a fairly lightweight protocol.

See the following benchmarks:

```
# 1000 spans
test perfetto::tests::bench_protobuf                       ... bench:     151,362 ns/iter (+/- 62,880)
test perfetto::tests::bench_protobuf_serialize             ... bench:     496,830 ns/iter (+/- 76,756)
test perfetto::tests::bench_protobuf_serialize_deserialize ... bench:   3,223,113 ns/iter (+/- 1,624,191)
test tests::bench_flatbuffer                               ... bench:     554,712 ns/iter (+/- 28,256)
test tests::bench_flatbuffer_serialize_deserialize         ... bench:     912,636 ns/iter (+/- 173,679)
```

it looks like the time savings are significant when you look at much larger span counts:

```
# 100000 spans
running 5 tests
test perfetto::tests::bench_protobuf                       ... bench: 135,067,978 ns/iter (+/- 75,189,195)
test perfetto::tests::bench_protobuf_serialize             ... bench: 177,414,165 ns/iter (+/- 56,362,947)
test perfetto::tests::bench_protobuf_serialize_deserialize ... bench: 348,342,652 ns/iter (+/- 25,930,071)
test tests::bench_flatbuffer                               ... bench:  56,207,343 ns/iter (+/- 13,824,450)
test tests::bench_flatbuffer_serialize_deserialize         ... bench:  88,270,168 ns/iter (+/- 20,599,690)
```

nearly 3x for just creating the structs (which basically includes serialization) for ser-de it's 4x savings.