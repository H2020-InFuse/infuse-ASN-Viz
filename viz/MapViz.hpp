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
#ifndef MapViz_H
#define MapViz_H

#include <vizkit3d/Vizkit3DPlugin.hpp>
#include <asn1/Map.h>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/Texture2D>

Q_DECLARE_METATYPE(asn1SccMap);

namespace vizkit3d
{
    class MapViz : public vizkit3d::Vizkit3DPlugin<asn1SccMap>
    {
        Q_OBJECT

        //Q_PROPERTY(bool showMapExtents READ areMapExtentsShown WRITE setShowMapExtents)

        Q_PROPERTY(bool vizualize_mesh READ getMeshVisualized WRITE setMeshVisualized)
        Q_PROPERTY(QColor map_color READ getMapColor WRITE setMapColor)
        Q_PROPERTY(bool cycleColor READ getCycleColor WRITE setCycleColor)
        Q_PROPERTY(double  cycleColorInterval READ getCycleColorInterval WRITE setCycleColorInterval)

        public slots:
            bool getMeshVisualized() const;
            void setMeshVisualized(bool enabled);
            QColor getMapColor() const;
            void setMapColor(QColor color);
            bool getCycleColor() const;
            void setCycleColor(bool enabled);
            double getCycleColorInterval() const;
            void setCycleColorInterval(double interval);

        public:
            MapViz();
            ~MapViz();

            Q_INVOKABLE void updateData(asn1SccMap const &sample)
            {vizkit3d::Vizkit3DPlugin<asn1SccMap>::updateData(sample);}   

        protected:
            virtual osg::ref_ptr<osg::Node> createMainNode();
            virtual void updateMainNode(osg::Node* node);
            virtual void updateDataIntern(asn1SccMap const& plan);

        private:
            asn1SccMap map;           

            osg::ref_ptr<osg::Geode> geode;
            
            osg::Vec4 mapColor;
            bool vizualizeMesh;
            double cycleColorInterval;
            bool cycleColor;

            const double HEIGHT_SCALE;

            void addColor(osg::ref_ptr<osg::Vec4Array> colors, const float &height);

            float getValue(const asn1SccMap &map, const int &c,const int &r, const int &channel = 0);

            template<class T> float getValueByPos(const int &c,const int &r, const int &channel = 0){
                byte* dataptr = map.data.data.arr;
                //calulate memory position
                //position in single channel Array3D byte*
                unsigned int posidx = (c+(r*map.data.cols));
                // printf("%i ",posidx);
                //account for the data size
                posidx *= sizeof(T);
                //account for the number of existing channels, now points to first channel
                posidx *= map.data.channels;
                //select channel
                posidx += (channel*sizeof(T));
                return *((T*)(dataptr+posidx)) * HEIGHT_SCALE;
            }

        public slots:
    };
}
#endif
