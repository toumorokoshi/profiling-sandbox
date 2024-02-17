use super::schema_generated;
use perfetto_trace::perfetto::protos;
use prost::Message;

// generate_example_trace returns back a protos::Trace object.
pub fn to_prefetto_trace(profile: schema_generated::Profile) -> protos::Trace {
    return protos::Trace { packet: vec![] };
}

// create an example perfetto trace
pub fn create_example_trace() -> protos::Trace {
    let mut packets = vec![];
    for i in 0..100000 {
        let packet = protos::TracePacket {
            timestamp: Some(0),
            timestamp_clock_id: None,
            trusted_pid: None,
            interned_data: None,
            sequence_flags: None,
            incremental_state_cleared: None,
            trace_packet_defaults: None,
            previous_packet_dropped: Some(false),
            first_packet_on_sequence: None,
            machine_id: None,
            data: None,
            optional_trusted_uid: None,
            optional_trusted_packet_sequence_id: None,
        };
        packets.push(packet);
    }
    let mut trace = protos::Trace { packet: packets };
    return trace;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[bench]
    fn bench_protobuf_serialize(b: &mut test::Bencher) {
        b.iter(|| {
            let trace = create_example_trace();
            let mut buf = vec![];
            trace.encode(&mut buf).unwrap();
        });
    }

    #[bench]
    fn bench_protobuf(b: &mut test::Bencher) {
        b.iter(|| {
            let trace = create_example_trace();
        });
    }

    #[bench]
    fn bench_protobuf_serialize_deserialize(b: &mut test::Bencher) {
        b.iter(|| {
            let trace = create_example_trace();
            let mut buf = vec![];
            trace.encode(&mut buf).unwrap();
            let trace2 = protos::Trace::decode(&*buf).unwrap();
        });
    }
}
