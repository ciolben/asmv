find_package(ProtoBuf REQUIRED)

set(DEPENDENT_PACKAGES assert_log)

set(DEPENDENT_INCLUDES ${PROTOBUF_INCLUDE_DIR})

set(DEPENDENT_LIBRARIES ${PROTOBUF_LIBRARY})

set(CREATED_PACKAGES segment_util)
