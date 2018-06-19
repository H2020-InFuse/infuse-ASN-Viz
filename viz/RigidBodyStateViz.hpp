#pragma once

#include <vizkit3d/RigidBodyStateVisualization.hpp>
#include <base_support/asn1RigidBodyStateConvert.hpp>

namespace vizkit3d
{
  class RigidBodyStateViz: public vizkit3d::RigidBodyStateVisualization, public vizkit3d::VizPluginAddType< asn1SccRigidBodyState >
    {
        Q_OBJECT
        public:
            RigidBodyStateViz(){};
            virtual ~RigidBodyStateViz(){};
        Q_INVOKABLE void updateData( const asn1SccRigidBodyState &sample){
            base::samples::RigidBodyState rocktype;
            RigidBodyState_fromAsn1(rocktype,sample);
            vizkit3d::RigidBodyStateVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccRigidBodyState &data){}
    };

}