#include "ASNViz.hpp"


using namespace vizkit3d;

//VizkitQtPlugin(Asn1SccRigidBodyStateViz)
//VizkitQtPlugin(Asn1SccMotion2dViz)


//instanciate templated viz classes
//TODO use typedef?
typedef Asn1RockViz<asn1SccRigidBodyState,base::samples::RigidBodyState,vizkit3d::RigidBodyStateVisualization> Asn1SccRigidBodyStateViz;
typedef Asn1RockViz<asn1SccMotion2D,base::commands::Motion2D,vizkit3d::MotionCommandVisualization>  Asn1SccMotion2DViz;


ASNViz::ASNViz(){
    registerViz("Asn1SccRigidBodyStateViz",RigidBodyState);
    registerViz("Asn1SccMotion2DViz", Motion2D);
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
        case RigidBodyState:    return new Asn1SccRigidBodyStateViz();
        case Motion2D:          return new MotionCommandVisualization();
        default: return NULL;
    };
}

Q_EXPORT_PLUGIN2(ASNViz, ASNViz)