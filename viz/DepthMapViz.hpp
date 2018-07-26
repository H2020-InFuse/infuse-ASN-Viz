#pragma once

#include <vizkit3d/DepthMapVisualization.hpp>
#include <sensor_samples_support/asn1DepthMapConvert.hpp>

namespace vizkit3d
{
  class DepthMapViz: public vizkit3d::DepthMapVisualization, public vizkit3d::VizPluginAddType< asn1SccDepthMap >
    {
        Q_OBJECT
        public:
            DepthMapViz(){};
            virtual ~DepthMapViz(){};
        Q_INVOKABLE void updateData( const asn1SccDepthMap &sample){
            base::samples::DepthMap rocktype;
            DepthMap_fromAsn1(rocktype,sample);
            vizkit3d::DepthMapVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccDepthMap &data){}
    };

}
