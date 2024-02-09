# Development

## Building Schemas

[flatbuffers](https://flatbuffers.dev/) are used to store spans, tracks and
categories.

to rebuild schema, run:

```bash
flatc -o src/ --rust ./src/schema.fbs
```