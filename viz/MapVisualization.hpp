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
#ifndef MapVisualization_H
#define MapVisualization_H

#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <asn1/Map.h>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/Texture2D>


namespace vizkit3d
{
    class MapVisualization
        : public vizkit3d::Vizkit3DPlugin<asn1SccMap>
    {
        Q_OBJECT

        //Q_PROPERTY(bool showMapExtents READ areMapExtentsShown WRITE setShowMapExtents)

        public:
            MapVisualization();
            ~MapVisualization();

            Q_INVOKABLE void updateGridMapD(asn1SccMap const &sample)
            {vizkit3d::Vizkit3DPlugin<asn1SccMap>::updateData(sample);}   
            
        protected:
            virtual osg::ref_ptr<osg::Node> createMainNode();
            virtual void updateMainNode(osg::Node* node);
            virtual void updateDataIntern(asn1SccMap const& plan);
            
        private:
            asn1SccMap map;           

            osg::ref_ptr<osg::Geode> geode;
            osg::ref_ptr<osg::HeightField> heightField;
            bool heightFieldCreated;

            template<class T> float getByPos(const int &x,const int &y){
                asn1SccArray3D_data* dataptr = &(map.data.data);
                unsigned int posidx = (x+(y*map.data.rowSize));
                return *((T*)(dataptr+(posidx * sizeof(T))));
            }

        public slots:
    };
}
#endif
