use super::schema_generated;
use perfetto_trace::perfetto::protos;

// generate_example_trace returns back a protos::Trace object.
pub fn to_prefetto_trace(profile: schema_generated::Profile) -> protos::Trace {
    return protos::Trace { packet: vec![] };
}
