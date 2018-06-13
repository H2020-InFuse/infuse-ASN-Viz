#ifndef ASN_Viz_ASNViz_H
#define ASN_Viz_ASNViz_H

#include <vizkit3d/Vizkit3DPlugin.hpp>


namespace vizkit3d
{
    template <class ASNTYPE, class ROCKTYPE, class ROCKVIS> class Asn1RockViz: public ROCKVIS, public vizkit3d::VizPluginAddType< ASNTYPE >
    {
        
        public:
            Asn1RockViz(){};
            virtual ~Asn1RockViz(){};

        Q_INVOKABLE void updateData( const ASNTYPE &sample){
            //convert
            ROCKTYPE rocktype = convertToRock(sample);
            //RigidBodyState_fromAsn1(rbs,sample);
            // dynamic_cast<vizkit3d::RigidBodyStateVisualization*>(plugin)->updateData(rbs);
            ROCKVIS::updateData(rocktype);
        }

        virtual void updateDataIntern(const ASNTYPE &data){
             //not used or convert??
            ROCKTYPE rocktype = convertToRock(data);
            //RigidBodyState_fromAsn1(rbs,data);
            ROCKVIS::updateDataIntern(rocktype);

         }

    };

    /**
     * The Plugin Factory
     */

    class ASNViz : public vizkit3d::VizkitPluginFactory {
        public:
        
        enum ASNPlugins {RigidBodyStateViz, Motion2DViz, PointcloudViz, LaserScanViz};

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
