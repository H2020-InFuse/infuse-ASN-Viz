#ifndef ASN_Viz_ASNViz_H
#define ASN_Viz_ASNViz_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/RigidBodyStateVisualization.hpp>
#include <osg/Geode>
//#include <ASN.1/BaseTypes.hpp>
//#include <ASN.1/Pose.hpp>

#include "asn1/RigidBodyState.h"
#include <base_support/asn1RigidBodyStateConvert.hpp>

#include "PluginNames.hpp"

//#define ADD_TYPES()

namespace vizkit3d
{
    class Asn1SccRigidBodyStateViz: public vizkit3d::Vizkit3DPlugin< asn1SccRigidBodyState >, boost::noncopyable
    {
        Q_OBJECT
        public:
            Asn1SccRigidBodyStateViz();
            virtual ~Asn1SccRigidBodyStateViz(){};

        Q_INVOKABLE void updateData( const asn1SccRigidBodyState &sample){
            //convert
            base::samples::RigidBodyState rbs;
            RigidBodyState_fromAsn1(rbs,sample);
            dynamic_cast<vizkit3d::RigidBodyStateVisualization*>(plugin)->updateData(rbs);
        }

        virtual void updateDataIntern(const asn1SccRigidBodyState &data){
            //not used or convert??
            //base::samples::RigidBodyState rbs;
            //dynamic_cast<vizkit3d::RigidBodyStateVisualization*>(plugin)->updateDataIntern(rbs);

        }

        virtual void updateMainNode(osg::Node* node){
            //vizkit3d::RigidBodyStateVisualization::updateMainNode(node);
        }

        // virtual osg::ref_ptr<osg::Node> createMainNode()
        // {
        //     // Geode is a common node used for vizkit3d plugins. It allows to display
        //     // "arbitrary" geometries
        //     return plugin->createMainNode();
        // }

        // virtual void updateMainNode ( osg::Node* node )
        // {
        //     return plugin->updateMainNode(node);
        // }

        private:

            VizPluginBase* plugin;

    };
}
#endif
