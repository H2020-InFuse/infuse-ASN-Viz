
set(LIB ${CMAKE_PROJECT_NAME})

# ASN.1 types are imported and compiled locally to the project, but not installed
esrocos_asn1_types_package(${LIB}_local_types
    OUTDIR asn1
    IMPORT types/base types/sensor_samples)


rock_library(ASN_Viz
    SOURCES Conversion.cpp
    HEADERS Conversion.hpp
    DEPS_PKGCONFIG base-types base_support sensor_samples_support)

add_dependencies(ASN_Viz ${LIB}_local_types_generate_c)
target_include_directories(ASN_Viz PUBLIC ${CMAKE_BINARY_DIR})


