rock_library(ASN_Viz
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(ASN_Viz_bin Main.cpp
    DEPS ASN_Viz)

