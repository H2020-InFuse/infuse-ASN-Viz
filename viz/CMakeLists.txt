

set(LIB ${CMAKE_PROJECT_NAME})

# ASN.1 types are imported and compiled locally to the project, but not installed
esrocos_asn1_types_package(${LIB}_local_types
    OUTDIR asn1
    IMPORT types/base)
    
rock_vizkit_plugin(ASN_Viz-viz
    ASNViz.cpp
    DEPS ASN_Viz 
    DEPS_PKGCONFIG base-types base_support
    MOC ASNViz.hpp
    HEADERS ASNViz.hpp Conversion.hpp)

target_include_directories(ASN_Viz-viz PUBLIC ${CMAKE_BINARY_DIR})