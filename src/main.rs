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
    let c = flatbuffers::get_root::<schema_generated::Category>(&category);
    println!("{}", c.name());
    println!("Hello, world!");
}
