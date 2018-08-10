
#include "Conversion.hpp"

namespace ASNtoRock{

    ::base::samples::RigidBodyState convertToRock(const asn1SccRigidBodyState& asnVal){
        ::base::samples::RigidBodyState rocktype;
        RigidBodyState_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

    base::commands::Motion2D convertToRock(const asn1SccMotion2D& asnVal){
        base::commands::Motion2D rocktype;
        Motion2D_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

    base::samples::Pointcloud convertToRock(const asn1SccPointcloud& asnVal){
        base::samples::Pointcloud rocktype;
        Pointcloud_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

    base::samples::LaserScan convertToRock(const asn1SccLaserScan& asnVal){
        base::samples::LaserScan rocktype;
        LaserScan_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

    base::samples::DepthMap convertToRock(const asn1SccDepthMap& asnVal){
        base::samples::DepthMap rocktype;
        DepthMap_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

    base::Vector3d convertToRock(const asn1SccVector3d& asnVal){
        base::Vector3d rocktype;
        Vector3d_fromAsn1(rocktype,asnVal);
        return rocktype;
    }

}

