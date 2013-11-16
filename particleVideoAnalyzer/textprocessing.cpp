#include "textprocessing.h"

#include <QDebug>
#include <QStringList>
#include <QStringBuilder>

QString TextProcessing::readLine() const
{
    if (m_stream == NULL) { return QString(""); }
    std::string line;

    if(std::getline (*m_stream, line)) {
        return QString(line.data());
    } else  {
        return QString("");
    }
}

TextProcessing::TextProcessing() :
    m_stream(NULL)
  , m_filename("")
  , m_curId(0)
{
}

int TextProcessing::setContent(const QString& filename)
{
    if (m_stream != NULL) {
        m_stream->close();
        delete m_stream;
        m_curId = 0;
    }

    m_filename = filename.toStdString();
    m_stream = new std::ifstream(m_filename);
    QString firstLine = readLine();
    if (firstLine.isEmpty()) { return -1; }
    return firstLine.trimmed().toInt();
}

QString TextProcessing::particleToString(const TextProcessing::Particle &particle)
{
    QString representation;
    representation = "Particle : id : " % QString::number(particle.id);
    representation = representation % " startframe : " % QString::number(particle.start);
    representation = representation % " endframe : " % QString::number(particle.end);
    representation = representation % " count : " % QString::number(particle.count);
    representation = representation % " positions : \n";
    int max = particle.positionsCount - 1;
    for (int i = 0; i < max; i += 2) {
        representation = representation % "("
                % QString::number(particle.positions[i])
                % "," % QString::number(particle.positions[i+1])
                % ")\n";
    }
    return representation;

}

bool TextProcessing::getNextParticle(TextProcessing::Particle& particle) const
{
    QString line = readLine();
    if (line.isEmpty()) {
        return false;
    }

    QStringList parts = line.split(" ", QString::SkipEmptyParts);
    particle.id = m_curId++;
    particle.start = parts.at(0).toUInt();
    particle.end = parts.at(1).toUInt();
    particle.count = parts.at(2).toUInt();
    //we need to determine if the format is int float float int float float int float float
    //or int float float float float float float
    bool hasIntermediateCount = false;
    if (parts.size() > 6) {
        if (parts.at(5).indexOf(".") == -1) {
            hasIntermediateCount = true;
        }
    }
    particle.positionsCount = hasIntermediateCount ? ceil((parts.size() - 3) / 3.f) * 2 : parts.size() - 3;
    float* positions = (float*) malloc(sizeof(float) * particle.positionsCount);
    particle.positions = positions;
    for (int i = 0; i < particle.positionsCount; i++) {
        positions[i] = parts.at(i + 3 + (hasIntermediateCount ? floor((i+1) / 3.f) : 0)).toFloat();
    }
    return true;
}

void TextProcessing::resetToBegining()
{
    m_curId = 0;
    if (m_filename.empty()) { return; }
    setContent(QString(m_filename.data()));
}

bool TextProcessing::isSet()
{
    return m_stream != NULL;
}
