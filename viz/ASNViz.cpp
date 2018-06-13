#include "ASNViz.hpp"
#include "Conversion.hpp"

using namespace vizkit3d;

#include <vizkit3d/RigidBodyStateVisualization.hpp>
#include <vizkit3d/MotionCommandVisualization.hpp>
#include <vizkit3d/PointcloudVisualization.hpp>
#include <vizkit3d/LaserScanVisualization.hpp>



const asn1SccT_UInt32 maxSize_T_String = 256;

//typedefs for viz classes
typedef Asn1RockViz<asn1SccRigidBodyState,base::samples::RigidBodyState,vizkit3d::RigidBodyStateVisualization> Asn1SccRigidBodyStateViz;
typedef Asn1RockViz<asn1SccMotion2D,base::commands::Motion2D,vizkit3d::MotionCommandVisualization>  Asn1SccMotion2DViz;
typedef Asn1RockViz<asn1SccPointcloud,base::samples::Pointcloud,vizkit3d::PointcloudVisualization>  Asn1SccPointcloudViz;
typedef Asn1RockViz<asn1SccLaserScan,base::samples::LaserScan,vizkit3d::LaserScanVisualization>  Asn1SccLaserScanViz;


ASNViz::ASNViz(){
    registerViz("Asn1SccRigidBodyStateViz",RigidBodyStateViz);
    registerViz("Asn1SccMotion2DViz", Motion2DViz);
    registerViz("asn1SccPointcloudViz", PointcloudViz);
    registerViz("asn1SccLaserScanViz", LaserScanViz);
    
}



void ASNViz::registerViz(const std::string& name, int index){

    nameindex[name] = index;
}

/**
* Returns a list of all available visualization plugins.
* @return list of plugin names
*/
QStringList* ASNViz::getAvailablePlugins() const
{

    QStringList *pluginNames = new QStringList();
    
    for (auto it = nameindex.begin();it != nameindex.end();it++){
        pluginNames->push_back(QString::fromStdString(it->first));
    }
    return pluginNames;
}

QObject* ASNViz::createPlugin(QString const& pluginName){
    int index = nameindex[pluginName.toStdString()];
    switch (index){
        case RigidBodyStateViz:    return new Asn1SccRigidBodyStateViz();
        case Motion2DViz:          return new Asn1SccMotion2DViz();
        case PointcloudViz:        return new Asn1SccPointcloudViz();
        case LaserScanViz:         return new Asn1SccLaserScanViz();
        default: return NULL;
    };
}

Q_EXPORT_PLUGIN2(ASNViz, ASNViz)