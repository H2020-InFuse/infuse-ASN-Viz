#include "ASNViz.hpp"

//#include "Conversion.hpp"
using namespace vizkit3d;

#include <vizkit3d/MotionCommandVisualization.hpp>
#include <vizkit3d/PointcloudVisualization.hpp>

#include "LaserScanViz.hpp"
#include "RigidBodyStateViz.hpp"




const asn1SccT_UInt32 maxSize_T_String = 256;
const asn1SccT_UInt32 frameMaxBytes = 2359296;


//typedefs for viz classes
// typedef Asn1RockViz<asn1SccRigidBodyState,base::samples::RigidBodyState,vizkit3d::RigidBodyStateVisualization> Asn1SccRigidBodyStateViz;
// typedef Asn1RockViz<asn1SccMotion2D,base::commands::Motion2D,vizkit3d::MotionCommandVisualization>  Asn1SccMotion2DViz;
// typedef Asn1RockViz<asn1SccPointcloud,base::samples::Pointcloud,vizkit3d::PointcloudVisualization>  Asn1SccPointcloudViz;
//typedef Asn1RockViz<asn1SccLaserScan,base::samples::LaserScan,vizkit3d::LaserScanVisualization>  Asn1SccLaserScanViz;





ASNViz::ASNViz(){
    registerViz("RigidBodyStateViz",RigidBodyState);
    registerViz("LaserScanViz", LaserScan);
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
       // printf("pname : %s\n",it->first.c_str());
    }
    return pluginNames;
}

QObject* ASNViz::createPlugin(QString const& pluginName){
    int index = nameindex[pluginName.toStdString()];

    switch (index){
        case RigidBodyState:    return new RigidBodyStateViz();
        case Motion2D:          return nullptr;
        case Pointcloud:        return nullptr;
        case LaserScan:         return new LaserScanViz();
        default: return nullptr;
    };
}

Q_EXPORT_PLUGIN2(ASNViz, ASNViz)