//
// Copyright (c) 2015-2017, Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.
// Copyright (c) 2015-2017, University of Bremen
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include <iostream>
#include <limits>

#include "MapViz.hpp"

//#include <vizkit3d/ColorConversionHelper.hpp>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>

#include <vizkit3d/ColorConversionHelper.hpp>

//#include "ColorGradient.hpp"

using namespace vizkit3d;


MapViz::MapViz()
: mapColor(osg::Vec4(1,1,1,1.0)),
  vizualizeMesh(true),
  cycleColorInterval(1.0),
  cycleColor(true),
  HEIGHT_SCALE(1.0)
{
}

MapViz::~MapViz()
{
}

osg::ref_ptr<osg::Node> MapViz::createMainNode()
{
    osg::ref_ptr<osg::Group> mainNode = new osg::Group;
    geode = new osg::Geode();


    // set material properties
    osg::StateSet* state = geode->getOrCreateStateSet();
    osg::ref_ptr<osg::Material> mat = new osg::Material;
    mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );

    mat->setAmbient( osg::Material::FRONT_AND_BACK,
            osg::Vec4( .5f, .5f, .3f, 1.0f ) );
    mat->setDiffuse( osg::Material::FRONT_AND_BACK,
            osg::Vec4( .5f, .5f, .3f, 1.0f ) );
    //mat->setSpecular( osg::Material::FRONT,
    //          osg::Vec4( 1.f, 1.f, 1.f, 1.0f ) );

    state->setAttribute( mat.get() );

    mainNode->addChild(geode.get());

    return mainNode;
}

float MapViz::getValue(const asn1SccMap &map, const int &c,const int &r, const int &channel){
    switch (map.data.depth){
        case asn1Sccdepth_8U:  return getValueByPos<uint8_t>(c,r,channel);
        case asn1Sccdepth_8S:  return getValueByPos<int8_t>(c,r,channel);
        case asn1Sccdepth_16U: return getValueByPos<uint16_t>(c,r,channel);
        case asn1Sccdepth_16S: return getValueByPos<int16_t>(c,r,channel);
        case asn1Sccdepth_32S: return getValueByPos<int32_t>(c,r,channel);
        case asn1Sccdepth_32F: return getValueByPos<float>(c,r,channel);
        case asn1Sccdepth_64F: return getValueByPos<double>(c,r,channel);
    }
    return 0;
}

void MapViz::addColor(osg::ref_ptr<osg::Vec4Array> colors, const float &height){
    if( cycleColor )
    {
        osg::Vec4 color;
        float sat = 1.0;
        float lum = 0.6;
        float hue = (height - std::floor(height / cycleColorInterval) * cycleColorInterval) / cycleColorInterval;
        vizkit3d::hslToRgb( hue, sat, lum , color.x(), color.y(), color.z());
        color.w() = mapColor.w();
        colors->push_back(osg::Vec4(color));
    }else{
        colors->push_back(osg::Vec4(mapColor));
    }
}

void MapViz::updateMainNode ( osg::Node* node )
{
    geode->removeDrawables(0,geode->getNumDrawables());

    double undefined = std::numeric_limits<double>::quiet_NaN();
    for(int i = 0; i < map.metadata.errValues.nCount; i++)
    {
        if(map.metadata.errValues.arr[i].type == asn1Sccerror_UNDEFINED)
        {
            undefined = map.metadata.errValues.arr[i].value;
            break;
        }
    }

    if (vizualizeMesh){
    
        osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
        osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

        osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
        float value;
        for (unsigned int r = 0; r < map.data.rows-1; r++) 
        {
            for (unsigned int c = 0; c < map.data.cols; c++) 
            {
                value = getValue(map,c,r);
                vertices->push_back(osg::Vec3d((r*map.metadata.scale),-(c*map.metadata.scale),value));
                addColor(colors,value);

                value = getValue(map,c,r+1);
                vertices->push_back(osg::Vec3d(((r+1)*map.metadata.scale),-(c*map.metadata.scale),value));
                addColor(colors,value);
            }

            // for the smoothing operator to work we need a single triangle mesh,
            // so now we move the next row backwards
            r++;
            if (r == map.data.rows - 1){
                // end reached, we only replicate the last column here
                r--;
            }
            for (int c = map.data.cols-1; c >= 0; c--) 
            {
                value = getValue(map,c,r);
                vertices->push_back(osg::Vec3d((r*map.metadata.scale),-(c*map.metadata.scale),value));
                addColor(colors,value);
                value = getValue(map,c,r+1);
                vertices->push_back(osg::Vec3d(((r+1)*map.metadata.scale),-(c*map.metadata.scale),value));
                addColor(colors,value);
            }
        }

        // geom->setColorArray(colors, osg::Array::BIND_OVERALL);
        geom->setColorArray(colors);
        geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

        geom->setVertexArray(vertices); 
        geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,map.data.rows*map.data.cols*2));
        geode->addDrawable(geom);

        osgUtil::SmoothingVisitor sv;
        geode->accept(sv); 
        

    }else{//visualizeMesh

        for (unsigned int r = 0; r < map.data.rows; r++) 
        {
            for (unsigned int c = 0; c < map.data.cols; c++) 
            {
                double value = 0.0;
                switch (map.data.depth){
                    case asn1Sccdepth_8U: value = getValueByPos<uint8_t>(c,r);break;
                    case asn1Sccdepth_8S: value = getValueByPos<int8_t>(c,r);break;
                    case asn1Sccdepth_16U: value = getValueByPos<uint16_t>(c,r);break;
                    case asn1Sccdepth_16S: value = getValueByPos<int16_t>(c,r);break;
                    case asn1Sccdepth_32S: value = getValueByPos<int32_t>(c,r);break;
                    case asn1Sccdepth_32F: value = getValueByPos<float>(c,r);break;
                    case asn1Sccdepth_64F: value = getValueByPos<double>(c,r);break;
                }

                if(value == HEIGHT_SCALE * undefined)
                    continue;

                osg::ref_ptr<osg::Box> newbox = new osg::Box(
                                    osg::Vec3d(r*map.metadata.scale + map.metadata.scale/2.0,
                                               -(c*map.metadata.scale + map.metadata.scale/2.0),
                                               value/2.0),
                                    map.metadata.scale,
                                    map.metadata.scale,
                                    value
                                    );
                osg::ref_ptr<osg::ShapeDrawable> boxdrawable = new osg::ShapeDrawable(newbox);
                boxdrawable->setColor(mapColor);
                geode->addDrawable(boxdrawable);
            }
        }
    }
}

void MapViz::updateDataIntern(asn1SccMap const& value)
{
    // p.reset(new DataHold<double>( value ));
    map = value;
}


bool MapViz::getMeshVisualized() const
{
    return vizualizeMesh;
}
void MapViz::setMeshVisualized(bool enabled){
    vizualizeMesh = enabled;
}
QColor MapViz::getMapColor() const
{
    QColor color;
    color.setRgbF(mapColor.x(), mapColor.y(), mapColor.z(), mapColor.w());
    return color;
}
void MapViz::setMapColor(QColor color)
{
    mapColor.x() = color.redF();
    mapColor.y() = color.greenF();
    mapColor.z() = color.blueF();
    mapColor.w() = color.alphaF();
}
bool MapViz::getCycleColor() const
{
    return cycleColor;
}
void MapViz::setCycleColor(bool enabled)
{
    cycleColor = enabled;
}
double MapViz::getCycleColorInterval() const
{
    return cycleColorInterval;
}
void MapViz::setCycleColorInterval(double interval)
{
    cycleColorInterval = interval;
}

//Macro that makes this plugin loadable in ruby, this is optional.
//VizkitQtPlugin(ElevationMapVisualization)

