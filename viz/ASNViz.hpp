#ifndef ASN_Viz_ASNViz_H
#define ASN_Viz_ASNViz_H


#include <vizkit3d/Vizkit3DPlugin.hpp>

namespace vizkit3d
{
  
    /**
     * The Plugin Factory
     */

    class ASNViz : public vizkit3d::VizkitPluginFactory {
        public:
        
        enum ASNPlugins {RigidBodyState, Motion2D, Pointcloud, LaserScan, DepthMap};

        ASNViz();      


        /**
	* Returns a list of all available visualization plugins.
	* @return list of plugin names
	*/
        virtual QStringList* getAvailablePlugins() const;
	
        virtual QObject* createPlugin(QString const& pluginName);


        private:
        void registerViz(const std::string& name, int index);
        int regindex;
        std::map<std::string, int> nameindex;
    };

}


#endif
