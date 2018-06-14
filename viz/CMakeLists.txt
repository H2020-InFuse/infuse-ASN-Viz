

set(LIB ${CMAKE_PROJECT_NAME})

# ASN.1 types are imported and compiled locally to the project, but not installed
esrocos_asn1_types_package(${LIB}_local_types
    OUTDIR asn1
    IMPORT types/base types/sensor_samples)
    
rock_vizkit_plugin(ASN_Viz-viz
    ASNViz.cpp
    MOC LaserScanViz.hpp
    DEPS ASN_Viz
    DEPS_PKGCONFIG base-types base_support sensor_samples_support base-viz
    MOC ASNViz.hpp
    HEADERS ASNViz.hpp Conversion.hpp)

add_dependencies(ASN_Viz-viz asn_local_types_generate_c)
target_include_directories(ASN_Viz-viz PUBLIC ${CMAKE_BINARY_DIR})