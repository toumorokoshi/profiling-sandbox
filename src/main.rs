#![feature(test)]

extern crate flatbuffers;
extern crate perfetto_trace;
extern crate prost;
extern crate test;
// flatbuffers generates code that
// has unused imports sometimes.
mod perfetto;
#[allow(dead_code, unused_imports)]
mod schema_generated;

use flatbuffers::{FlatBufferBuilder, WIPOffset};
use prost::Message;
use std::io::Write;

fn main() {
    let mut builder: FlatBufferBuilder = FlatBufferBuilder::new();
    add_example_profile(&mut builder);
    let profile = flatbuffers::root::<schema_generated::Profile>(builder.finished_data()).unwrap();
    println!("{}", profile.spans().unwrap().len());
    println!("Hello, world!");
    let p = perfetto::to_prefetto_trace(profile);
    // write the proto object to a file foo.pb
    let mut file = std::fs::File::create("/tmp/foo.trace").unwrap();
    let mut buf = Vec::new();
    p.encode(&mut buf).unwrap();
    file.write_all(&buf).unwrap();
}

// generate_example_profile returns back an example Profile object.
fn add_example_profile(mut builder: &mut FlatBufferBuilder) {
    let mut spans = Vec::new();
    for i in 0..100000 {
        // let name = builder.create_string("foo");
        let span = schema_generated::Span::create(
            &mut builder,
            &schema_generated::SpanArgs {
                track_id: 1,
                name: None,
                start_time_ns: 0,
                end_time_ns: 1000,
            },
        );
        spans.push(span);
    }
    let spans = builder.create_vector(&spans);
    // let spans = builder.create_vector(&[span]);
    // builder.start_vector::<schema_generated::Span>(1);
    // builder.push(span);
    // let spans = builder.end_vector(1);
    let profile_offset = schema_generated::Profile::create(
        &mut builder,
        &schema_generated::ProfileArgs {
            categories: None,
            tracks: None,
            events: None,
            spans: Some(spans),
        },
    );
    builder.finish(profile_offset, None);
    // let category_offset = schema_generated::Category::create(&mut builder, &category_args);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[bench]
    fn bench_flatbuffer_serialize_deserialize(b: &mut test::Bencher) {
        b.iter(|| {
            let mut builder: FlatBufferBuilder = FlatBufferBuilder::new();
            add_example_profile(&mut builder);
            let profile =
                flatbuffers::root::<schema_generated::Profile>(builder.finished_data()).unwrap();
        });
    }

    #[bench]
    fn bench_flatbuffer(b: &mut test::Bencher) {
        b.iter(|| {
            let mut builder: FlatBufferBuilder = FlatBufferBuilder::new();
            add_example_profile(&mut builder);
        });
    }
}
