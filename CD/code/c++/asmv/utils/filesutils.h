#ifndef FILESUTILS_H
#define FILESUTILS_H

#include <QFileInfo>

///
/// \brief sortFiles
///     Sort the files according to their filename.
///     The sort will output from a1, a10, a2, b1a0, b10, b1a1
///     to a1, a2, a10, b10, b1a0, b1a1 for example
/// \param list
///
inline void sortFiles(QFileInfoList &list) {

    auto sortfun = []
    (const QFileInfo f1, const QFileInfo f2) -> bool {
        QString s1 = f1.fileName();
        QString s2 = f2.fileName();
        int l1 = s1.length();
        int l2 = s2.length();
        int l = std::min(l1, l2);
        QString nums1;
        QString nums2;
        for (int i = 0; i < l; ++i) {
            QChar c(s1.at(i));
            QChar c2(s2.at(i));
            if (c.isDigit()) {
                if (c2.isDigit()) {
                    nums1.push_back(c);
                    nums2.push_back(c2);
                } else {
                    return false;
                }
            } else if (c < c2) {
                return true;
            } else if (c > c2) {
                return false;
            }
        }
        return nums1.compare(nums2) < 0;
    };

    qSort(list.begin(), list.end(), sortfun);
}

///
/// \brief getNameOfFile
///     Returns the name of the file (between last '/' and last '.')
/// \param filename
/// \return
///
inline QString getNameOfFile(const QString &filename) {
    if (filename.isEmpty()) { return ""; }
    int id1 = filename.lastIndexOf("/");
    if (id1 == -1) { id1 = filename.lastIndexOf("\\"); }
    if (id1 == -1) { id1 = 0; }
    int id2 = filename.lastIndexOf(".");
    return filename.mid(id1 + 1, id2 - id1 - 1);
}

///
/// \brief getSupportedImagesFilter
///     Returns filter for images
/// \return
///
inline QStringList getSupportedImagesFilter() {
    QStringList filterImg;
    filterImg << "*.png" << "*.jpg" << "*.jpeg";
    return QStringList(filterImg);
}

#endif // FILESUTILS_H
