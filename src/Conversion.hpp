#ifndef ASNViz_CONVERSION
#define ASNViz_CONVERSION

#include <base_support/asn1RigidBodyStateConvert.hpp>
#include <base_support/asn1Motion2DConvert.hpp>
#include <sensor_samples_support/asn1PointcloudConvert.hpp>
#include <sensor_samples_support/asn1LaserScanConvert.hpp>
#include <sensor_samples_support/asn1DepthMapConvert.hpp>


namespace ASNtoRock{

    static ::base::samples::RigidBodyState convertToRock(const asn1SccRigidBodyState& asnVal);

    static ::base::commands::Motion2D convertToRock(const asn1SccMotion2D& asnVal);

    static ::base::samples::Pointcloud convertToRock(const asn1SccPointcloud& asnVal);

    static ::base::samples::LaserScan convertToRock(const asn1SccLaserScan& asnVal);

    static ::base::samples::DepthMap convertToRock(const asn1SccDepthMap& asnVal);

}

#endif
