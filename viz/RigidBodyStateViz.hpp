#pragma once

#include <vizkit3d/RigidBodyStateVisualization.hpp>
#include <base_support/asn1RigidBodyStateConvert.hpp>
#include <base_support/asn1TransformWithCovarianceConvert.hpp>


Q_DECLARE_METATYPE(asn1SccRigidBodyState);

namespace vizkit3d
{
  class RigidBodyStateViz: public vizkit3d::RigidBodyStateVisualization, public vizkit3d::VizPluginAddType< asn1SccRigidBodyState >
    {
        Q_OBJECT
        public:
            RigidBodyStateViz(){qRegisterMetaType<asn1SccRigidBodyState>();};
            virtual ~RigidBodyStateViz(){};
        Q_INVOKABLE void updateData( const asn1SccRigidBodyState &sample){
            base::samples::RigidBodyState rocktype;
            RigidBodyState_fromAsn1(rocktype,sample);
            vizkit3d::RigidBodyStateVisualization::updateData(rocktype);
        }
        Q_INVOKABLE void updateData( const asn1SccTransformWithCovariance &sample){
            base::TransformWithCovariance rocktype;
            TransformWithCovariance_fromAsn1(rocktype,sample);
            vizkit3d::RigidBodyStateVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccRigidBodyState &data){}
    };

}