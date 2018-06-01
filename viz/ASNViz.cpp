#include "ASNViz.hpp"


using namespace vizkit3d;

//VizkitQtPlugin(Asn1SccRigidBodyStateViz)
//VizkitQtPlugin(Asn1SccMotion2dViz)


//instanciate templated viz classes
//TODO use typedef?
typedef Asn1RockViz<asn1SccRigidBodyState,base::samples::RigidBodyState,vizkit3d::RigidBodyStateVisualization> Asn1SccRigidBodyStateViz;
typedef Asn1RockViz<asn1SccMotion2D,base::commands::Motion2D,vizkit3d::MotionCommandVisualization>  Asn1SccMotion2dViz;




/**
	* Returns a list of all available visualization plugins.
	* @return list of plugin names
	*/
    QStringList* ASNViz::getAvailablePlugins() const
	{
	    QStringList *pluginNames = new QStringList();
	    pluginNames->push_back("Asn1SccRigidBodyStateViz");
	    pluginNames->push_back("Asn1SccMotion2dViz");
	    return pluginNames;
	}
	
    QObject* ASNViz::createPlugin(QString const& pluginName){
	    vizkit3d::VizPluginBase* plugin = 0;
	    if (pluginName == "Asn1SccRigidBodyStateViz")
	    {
		    plugin = new Asn1SccRigidBodyStateViz();
	    }
	    else if (pluginName == "Asn1SccMotion2dViz")
	    {
    		plugin = new MotionCommandVisualization();
	    }
	    
        if (plugin) 
	    {
		    return plugin;
	    }
	    return NULL;
        };
Q_EXPORT_PLUGIN2(ASNViz, ASNViz)