//gcc -E viz/test_define.cpp

#define ASN1_WRAP_ROCK_VIS(ASN_PREFIX,ASNTYPE,ROCKTYPE,VIZ) \
    class ASN_PREFIX ## ASNTYPE ## Viz: public VIZ, public vizkit3d::VizPluginAddType< ASN_PREFIX ## ASNTYPE > \
    { \
        Q_OBJECT \
        public: \
            ASN_PREFIX ## ASNTYPE Viz(){}; \
            virtual ~ASN_PREFIX ## ASNTYPE Viz(){}; \
        Q_INVOKABLE void updateData( const ASN_PREFIX ## ASNTYPE &sample){ \
            ROCKTYPE rocktype; \
            ASNTYPE ## _fromAsn1(rocktype,sample); \
            VIZ::updateData(rocktype); \
        } \
        virtual void updateDataIntern(const ASN_PREFIX ## ASNTYPE &data){} \
    };

    ASN1_WRAP_ROCK_VIS(Asn1Scc,LaserScan,::base::samples::LaserScan,vizkit3d::LaserScanVisualization)