#pragma once

#include <base_support/asn1RigidBodyStateConvert.hpp>

    //additional copy constructor for base::samples::RigidBodyState
    ::base::samples::RigidBodyState convertToRock(const asn1SccRigidBodyState& asnVal){
        ::base::samples::RigidBodyState rocktype;
        RigidBodyState_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

#include <base_support/asn1Motion2DConvert.hpp>

    base::commands::Motion2D convertToRock(const asn1SccMotion2D& asnVal){
        base::commands::Motion2D rocktype;
        Motion2D_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

#include <sensor_samples_support/asn1PointcloudConvert.hpp>
    base::samples::Pointcloud convertToRock(const asn1SccPointcloud& asnVal){
        base::samples::Pointcloud rocktype;
        Pointcloud_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

#include <sensor_samples_support/asn1LaserScanConvert.hpp>

    base::samples::LaserScan convertToRock(const asn1SccLaserScan& asnVal){
        base::samples::LaserScan rocktype;
        LaserScan_fromAsn1(rocktype,asnVal);
        return rocktype;
    }