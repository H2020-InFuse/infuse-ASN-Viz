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

#include "MapViz.hpp"

//#include <vizkit3d/ColorConversionHelper.hpp>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>

//#include "ColorGradient.hpp"

using namespace vizkit3d;




    osg::Image* MapViz::createTextureImage()
    {
        osg::Image* image = new osg::Image(); 

        //convert double to uint16 
        int size = heightField->getNumRows() * heightField->getNumColumns() * 4;
        unsigned char* image_raw_data = new unsigned char[size];
        unsigned char* pos = image_raw_data;

        // float min = grid.getMin(false);
        // float max = grid.getMax(false);

        float min = 0;
        float max = 1;

        //scaling between SCALING_MIN_VALUE and SCALING_MAX_VALUE meters 
        double scaling = std::abs(max - min);

        if(scaling == 0)
            scaling = 1.0;

        // fill image with color
        for (unsigned int y = 0; y < heightField->getNumRows(); ++y)
        {
            for (unsigned int x = 0; x < heightField->getNumColumns(); ++x)
            {
                /** Get the cell value **/
                float cell_value = heightField->getHeight(x, y);

                //double normalize_value = (double)(cell_value - min)/scaling;
                osg::Vec4f col(1.0,1.0,0.6,1.0);
                //this->heatMapGradient.getColorAtValue(normalize_value, col.r(),col.g(),col.b());
                
                *pos++ = (unsigned char)(col.r() * 255.0);
                *pos++ = (unsigned char)(col.g() * 255.0);
                *pos++ = (unsigned char)(col.b() * 255.0);
                *pos++ = (unsigned char)(col.a() * 255.0);
            }
        }

        image->setImage(
                heightField->getNumColumns(),
                heightField->getNumRows(),
                1, // datadepth per channel
                GL_RGBA, 
                GL_RGBA, 
                GL_UNSIGNED_BYTE, // GLenum type, (GL_UNSIGNED_BYTE, 0x1401)
                (unsigned char*)(image_raw_data), // unsigned char* data
                osg::Image::USE_NEW_DELETE, // USE_NEW_DELETE, //osg::Image::NO_DELETE,// AllocationMode mode (shallow copy)
                1);      

        return image;
    }    


MapViz::MapViz():heightFieldCreated(false)
{
}

MapViz::~MapViz()
{
}

osg::ref_ptr<osg::Node> MapViz::createMainNode()
{
// osgTerrain::TerrainTile will be a better base to work from when
// rendering a HeightField.  There is a HeightFieldLayer class that
// allows you to attach your height field to the TerrainTile.  There is a
// brute for GeometryTechnique that will just rendering the data by
// sending down a vertex array and all the triangle primitives as
// DrawElement - so will efficiently use indices.   Using osgTerrain
// gives the ability to down sample the data, and also implement your own
// custom TerrainTechnique if and when you need it.



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

        // osg::ref_ptr<osg::Image> image = createTextureImage();   
        // osg::Texture2D* tex = new osg::Texture2D(image);
        // tex->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR_MIPMAP_LINEAR);
        // tex->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
        // tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
        // tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
        // state->setTextureAttributeAndModes(0, tex); 

        // geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON); 


    mainNode->addChild(geode.get());

    return mainNode;
}

void MapViz::updateMainNode ( osg::Node* node )
{
    geode->removeDrawables(0,geode->getNumDrawables());

    for (unsigned int r = 0; r < map.data.rows; r++) 
    {
        for (unsigned int c = 0; c < map.data.cols; c++) 
        {
            float value = 0;
            switch (map.data.depth){
                case asn1Sccdepth_8U: value = getValueByPos<uint8_t>(c,r);break;
                case asn1Sccdepth_8S: value = getValueByPos<int8_t>(c,r);break;
                case asn1Sccdepth_16U: value = getValueByPos<uint16_t>(c,r);break;
                case asn1Sccdepth_16S: value = getValueByPos<int16_t>(c,r);break;
                case asn1Sccdepth_32S: value = getValueByPos<int32_t>(c,r);break;
                case asn1Sccdepth_32F: value = getValueByPos<float>(c,r);break;
                case asn1Sccdepth_64F: value = getValueByPos<double>(c,r);break;
            }

            //debug
            // value = (r+c)/10.0;
            // std::cout << value << std::endl;

            osg::ref_ptr<osg::Box> newbox = new osg::Box(
                                osg::Vec3d(r*map.metadata.scale + map.metadata.scale/2.0,c*map.metadata.scale + map.metadata.scale/2.0,value/2.0),
                                map.metadata.scale,map.metadata.scale,value
                                );
            osg::ref_ptr<osg::ShapeDrawable> boxdrawable = new osg::ShapeDrawable(newbox);
            geode->addDrawable(boxdrawable);   
        }
    }

        //if (!heightFieldCreated){
            // heightField= new osg::HeightField();
            // heightFieldCreated = true;

            // // map
            // heightField->allocate(map.data.cols,map.data.rows);
            // heightField->setXInterval(map.metadata.scale);
            // heightField->setYInterval(map.metadata.scale);
            // //heightField->setXInterval(1.0f);
            // //heightField->setYInterval(1.0f);
            // heightField->setSkirtHeight(0.0f);
            // heightField->setBorderWidth(1);
            // heightField->setOrigin(osg::Vec3(0, 0, 0));

            // osg::ref_ptr<osg::ShapeDrawable> drawable = new osg::ShapeDrawable(heightField);
            // geode->addDrawable(drawable);   



            // // double min = grid.getMin(false);
            // // double default_value = grid.getDefaultValue();
       // }


        // for (unsigned int r = 0; r < map.data.rows; r++) 
        // {
        //     for (unsigned int c = 0; c < map.data.cols; c++) 
        //     {
        //         float value = 0;
        //         switch (map.data.depth){
        //             case asn1Sccdepth_8U: value = getValueByPos<uint8_t>(c,r);
        //             case asn1Sccdepth_8S: value = getValueByPos<int8_t>(c,r);
        //             case asn1Sccdepth_16U: value = getValueByPos<uint16_t>(c,r);
        //             case asn1Sccdepth_16S: value = getValueByPos<int16_t>(c,r);
        //             case asn1Sccdepth_32S: value = getValueByPos<int32_t>(c,r);
        //             case asn1Sccdepth_32F: value = getValueByPos<float>(c,r);
        //             case asn1Sccdepth_64F: value = getValueByPos<double>(c,r);
        //         }

        //         //GridT cell_value = grid.at(maps::grid::Index(c, r));
                
        //         //if( cell_value !=  default_value)
        //              heightField->setHeight(c, r, value);

        //         // else
        //         //     heightField->setHeight(c, r, min);    // min elevation
        //     }
        // }   

    //if(!p) return;

    // Draw map.
    //p->visualize(*geode);

    // Draw map extents.
    // visualizeMapExtents(p->getCellExtents(), p->getResolution());

    // Set local frame.
    // setLocalFrame(p->getLocalFrame());
}

void MapViz::updateDataIntern(asn1SccMap const& value)
{
    // p.reset(new DataHold<double>( value ));
    map = value;
}

//Macro that makes this plugin loadable in ruby, this is optional.
//VizkitQtPlugin(ElevationMapVisualization)
