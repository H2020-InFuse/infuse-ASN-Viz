#include <iostream>
#include "ASNViz.hpp"

#include <vizkit3d/Vizkit3DWidget.hpp>

using namespace vizkit3d;

Asn1SccRigidBodyStateViz::Asn1SccRigidBodyStateViz(){

    // Create and add plugin
    plugin = dynamic_cast<VizPluginBase*>(getWidget()->loadPlugin("base", "RigidBodyStateVisualization"));
    if (NULL == plugin)
    {
        throw std::runtime_error("loading plugin BodyStateVisualization from base failed");
        }

};
//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(Asn1SccRigidBodyStateViz)

// osg::ref_ptr<osg::Node> ASNViz::createMainNode()
// {
//     // Geode is a common node used for vizkit3d plugins. It allows to display
//     // "arbitrary" geometries
//     return new osg::Geode();
// }

// void ASNViz::updateMainNode ( osg::Node* node )
// {
//     osg::Geode* geode = static_cast<osg::Geode*>(node);
//     // Update the main node using the data in p->data
// }

// void ASNViz::updateDataIntern( const PoseWrapper::Pose3D &value)
// {
//     p->data = value;
//     std::cout << "got new sample data" << std::endl;
// }



