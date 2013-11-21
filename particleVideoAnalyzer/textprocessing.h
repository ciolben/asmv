#ifndef TEXTPROCESSING_H
#define TEXTPROCESSING_H

#include <iostream>
#include <fstream>

#include <QString>

///
/// \brief  Class for reading a sps file.
///
class TextProcessing
{

private:
    std::ifstream* m_stream;
    std::string m_filename;
    mutable unsigned m_curId;

    QString readLine() const;

public:
    TextProcessing();
    ~TextProcessing() {
        if (m_stream != NULL) {
            m_stream->close();
            delete m_stream;
        }
    }

    typedef struct Particle {
        unsigned id; //particle number
        unsigned start; //start frame
        unsigned end;   //end frame
        unsigned count; //point count
        unsigned positionsCount;  //number of positions
        float* positions;    //position coordinates x1,y1,x2,y2...
    } Particle ;

    bool isSet();
    int setContent(const QString &filename);
    static QString particleToString(const Particle& particle);

    bool getNextParticle(Particle &particle) const;
    void resetToBegining();
};

#endif // TEXTPROCESSING_H
