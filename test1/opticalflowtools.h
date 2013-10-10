#ifndef OPTICALFLOWTOOLS_H
#define OPTICALFLOWTOOLS_H

#endif // OPTICALFLOWTOOLS_H

#include <QString>
#include <QImage>

class OpticalFlowTools {

public:
    static QImage *computeCoarse2Fine(const QString& im1, const QString& im2);
};
