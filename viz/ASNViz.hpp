#ifndef ASN_Viz_ASNViz_H
#define ASN_Viz_ASNViz_H

#include <boost/noncopyable.hpp>
#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <osg/Geode>
#include <ASN.1/BaseTypes.hpp>
#include <ASN.1/Pose.hpp>

namespace vizkit3d
{
    template <ASNTYPE,ROCKTYPE> class ASNViz
        : public vizkit3d::Vizkit3DPlugin< ASNTYPE >
        , boost::noncopyable
    {
    Q_OBJECT
    public:
        ASNViz();
        ~ASNViz();

    Q_INVOKABLE void updateData( const ASNTYPE &sample)
    {vizkit3d::Vizkit3DPlugin< ASNTYPE >::updateData(sample);}

    protected:
        virtual osg::ref_ptr<osg::Node> createMainNode();
        virtual void updateMainNode(osg::Node* node);
        virtual void updateDataIntern( const& plan);
        
    private:
        struct Data;
        Data* p;
    };
}
#endif
