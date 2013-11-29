#ifndef IOCOMPRESSION_H
#define IOCOMPRESSION_H

#include <QString>
#include <QProcess>
#include <QDebug>

///
/// \brief gzipUncompress
///Simple method that calls gzip from shell
/// \param file
///
QByteArray gzipUncompress(const QString& file) {
    QProcess process;
    QByteArray buffer;
    QObject::connect(&process, &QProcess::readyRead, [&] () {
        buffer.append(process.readAllStandardOutput());
    });

    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("gzip -d -c \"" + file + "\"");
    process.waitForStarted();
    process.waitForFinished();

    return buffer;
}

#endif // IOCOMPRESSION_H
