#pragma once

#include <vizkit3d/LaserScanVisualization.hpp>
#include <sensor_samples_support/asn1LaserScanConvert.hpp>

namespace vizkit3d
{
  class LaserScanViz: public vizkit3d::LaserScanVisualization, public vizkit3d::VizPluginAddType< asn1SccLaserScan >
    {
        Q_OBJECT
        public:
            LaserScanViz(){};
            virtual ~LaserScanViz(){};
        Q_INVOKABLE void updateData( const asn1SccLaserScan &sample){
            base::samples::LaserScan rocktype;
            LaserScan_fromAsn1(rocktype,sample);
            vizkit3d::LaserScanVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccLaserScan &data){}
    };

}