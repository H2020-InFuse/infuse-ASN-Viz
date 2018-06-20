#pragma once

#include <vizkit3d/PointcloudVisualization.hpp>
#include <sensor_samples_support/asn1PointcloudConvert.hpp>

namespace vizkit3d
{
  class PointcloudViz: public vizkit3d::PointcloudVisualization, public vizkit3d::VizPluginAddType< asn1SccPointcloud >
    {
        Q_OBJECT
        public:
            PointcloudViz(){};
            virtual ~PointcloudViz(){};
        Q_INVOKABLE void updateData( const asn1SccPointcloud &sample){
            base::samples::Pointcloud rocktype;
            Pointcloud_fromAsn1(rocktype,sample);
            vizkit3d::PointcloudVisualization::updateData(rocktype);
        }
        virtual void updateDataIntern(const asn1SccPointcloud &data){}
    };

}