#pragma once

#include <vizkit3d/TrajectoryVisualization.hpp>
#include <base_support/asn1Vector3dConvert.hpp>

Q_DECLARE_METATYPE(asn1SccVector3d);

namespace vizkit3d
{
  class TrajectoryViz: public vizkit3d::TrajectoryVisualization, public vizkit3d::VizPluginAddType< asn1SccVector3d >
    {
        Q_OBJECT
        public:
            TrajectoryViz(){qRegisterMetaType<asn1SccVector3d>();};
            virtual ~TrajectoryViz(){};
        Q_INVOKABLE void updateData( const asn1SccVector3d &sample){
            base::Vector3d rocktype;
            Vector3d_fromAsn1(rocktype,sample);
            vizkit3d::TrajectoryVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccVector3d &data){}
    };

}
