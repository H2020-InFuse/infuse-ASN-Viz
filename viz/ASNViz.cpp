#include <iostream>
#include "ASNViz.hpp"

using namespace vizkit3d;

struct ASNViz::Data {
    // Copy of the value given to updateDataIntern.
    //
    // Making a copy is required because of how OSG works
     data;
};


ASNViz::ASNViz()
    : p(new Data)
{
}

ASNViz::~ASNViz()
{
    delete p;
}

osg::ref_ptr<osg::Node> ASNViz::createMainNode()
{
    // Geode is a common node used for vizkit3d plugins. It allows to display
    // "arbitrary" geometries
    return new osg::Geode();
}

void ASNViz::updateMainNode ( osg::Node* node )
{
    osg::Geode* geode = static_cast<osg::Geode*>(node);
    // Update the main node using the data in p->data
}

void ASNViz::updateDataIntern( const& value)
{
    p->data = value;
    std::cout << "got new sample data" << std::endl;
}

//Macro that makes this plugin loadable in ruby, this is optional.
VizkitQtPlugin(ASNViz)

