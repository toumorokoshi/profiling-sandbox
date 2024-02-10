extern crate flatbuffers;
use flatbuffers::{FlatBufferBuilder, WIPOffset};
mod schema_generated;

fn main() {
    let mut builder = FlatBufferBuilder::new();
    let mut category_args = schema_generated::CategoryArgs {
        id: 1,
        name: Some(builder.create_string("foo")),
    };
    let category_offset = schema_generated::Category::create(&mut builder, &category_args);
    builder.finish(category_offset, None);
    let buf = builder.finished_data();
    let category = flatbuffers::root::<schema_generated::Category>(&buf).unwrap();
    println!("{}", category.name().unwrap());
    println!("Hello, world!");
}
