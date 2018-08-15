


rock_vizkit_plugin(ASN_Viz-viz
    ASNViz.cpp
    MOC ASNViz.hpp
        LaserScanViz.hpp 
        RigidBodyStateViz.hpp
        PointcloudViz.hpp
        DepthMapViz.hpp
        TrajectoryViz.hpp
    DEPS ASN_Viz
    DEPS_PKGCONFIG base-types base_support sensor_samples_support base-viz asn1
    HEADERS ASNViz.hpp)
