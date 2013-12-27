#ifndef FILTERING_H
#define FILTERING_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <QString>
using namespace std;
namespace filter {

///
/// \brief sum
/// \param input
/// \param from (index)
/// \param to (index)
/// \return
///
inline float sum(const vector<float>& input, int from = 0, int to = -1) {
    float sum(0);
    if (to == -1) { to = input.size() - 1; }
    for (int i = from; i <= to; ++i) {
        sum += input.at(i);
    }
    return sum;
}

///
/// \brief movingAverage
/// Compute the moving average on input vector.
/// \param input
/// \param output
/// \param ws Window size, better is an odd number because it fits the way the
/// function is designed (the border of the input array are computed with odd
/// window size).
///
static void movingAverage(const vector<float>& input, vector<float>& output, float ws) {
    if (input.size() < ws) { cout << "ws too big" << endl; return; }

    int hws = floor(ws / 2.f);
    int bindex = hws;
    int size = input.size();
    int eindex = size - bindex - 1;

    float csum(0);
    output.push_back(input.front());
    for(int i = 1; i < bindex; ++i) {
        output.push_back(sum(input, 0, i * 2) / ((float)(i * 2 + 1)));
        csum += input.at(i);
    }

    for(int i = bindex; i <= ws; ++i) {
        csum += input.at(i);
    }

    for(int i = bindex; i <= eindex; ++i) {
        output.push_back(csum / ws);
        if (i == eindex) { break; }
        csum += input.at(i + hws + 1);
        csum -= input.at(i - hws + 1);
    }

    for(int i = eindex + 1; i < size - 1; ++i) {
        output.push_back(sum(input, 2 * (i + 1) - size - 1, size - 1) / ((float)(2 * (size - i - 1) + 1)));
    }
    output.push_back(input.back());
}

///
/// Find the maximum absolute value in an array
///
template <typename NType>
inline NType findAbsMax(vector<NType> array) {
    NType max = 0;
    foreach (NType n, array) {
        NType absN = abs(n);
        if (absN > max) {
            max = absN;
        }
    }
    return max;
}

///
/// \brief The Chauvenet class
/// ref : http://read.pudn.com/downloads22/sourcecode/internet/71927/Jiggle/org/trinet/util/Ztable.java__.htm
class Chauvenet {
private:
    double maxSdev;
    double* sDev;
    double* below;
    int sDev_size, below_size;
    double m_cutoff;

public:
    Chauvenet() : maxSdev(3.50), m_cutoff(0.5)
    {
        double sDevTmp[] = {
        0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11,
        0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23,
        0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.30, 0.31, 0.32, 0.33, 0.34, 0.35,
        0.36, 0.37, 0.38, 0.39, 0.40, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47,
        0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59,
        0.60, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.70, 0.71,
        0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.80, 0.81, 0.82, 0.83,
        0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95,
        0.96, 0.97, 0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07,
        1.08, 1.09, 1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19,
        1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.30, 1.31,
        1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.40, 1.41, 1.42, 1.43,
        1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.50, 1.51, 1.52, 1.53, 1.54, 1.55,
        1.56, 1.57, 1.58, 1.59, 1.60, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67,
        1.68, 1.69, 1.70, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79,
        1.80, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.90, 1.91,
        1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2.00, 2.01, 2.02, 2.03,
        2.04, 2.05, 2.06, 2.07, 2.08, 2.09, 2.10, 2.11, 2.12, 2.13, 2.14, 2.15,
        2.16, 2.17, 2.18, 2.19, 2.20, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27,
        2.28, 2.29, 2.30, 2.31, 2.32, 2.33, 2.34, 2.35, 2.36, 2.37, 2.38, 2.39,
        2.40, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47, 2.48, 2.49, 2.50, 2.51,
        2.52, 2.53, 2.54, 2.55, 2.56, 2.57, 2.58, 2.59, 2.60, 2.61, 2.62, 2.63,
        2.64, 2.65, 2.66, 2.67, 2.68, 2.69, 2.70, 2.71, 2.72, 2.73, 2.74, 2.75,
        2.76, 2.77, 2.78, 2.79, 2.80, 2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87,
        2.88, 2.89, 2.90, 2.91, 2.92, 2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99,
        3.00, 3.01, 3.02, 3.03, 3.04, 3.05, 3.06, 3.07, 3.08, 3.09, 3.10, 3.11,
        3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.20, 3.21, 3.22, 3.23,
        3.24, 3.25, 3.26, 3.27, 3.28, 3.29, 3.30, 3.31, 3.32, 3.33, 3.34, 3.35,
        3.36, 3.37, 3.38, 3.39, 3.40, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47,
        3.48, 3.49, 3.50};
        double belowTmp[] = {
        0.5000, 0.5040, 0.5080, 0.5120, 0.5160, 0.5199, 0.5239, 0.5279, 0.5319, 0.5359, 0.5398, 0.5438,
        0.5478, 0.5517, 0.5557, 0.5596, 0.5636, 0.5675, 0.5714, 0.5753, 0.5793, 0.5832, 0.5871, 0.5910,
        0.5948, 0.5987, 0.6026, 0.6064, 0.6103, 0.6141, 0.6179, 0.6217, 0.6255, 0.6293, 0.6331, 0.6368,
        0.6406, 0.6443, 0.6480, 0.6517, 0.6554, 0.6591, 0.6628, 0.6664, 0.6700, 0.6736, 0.6772, 0.6808,
        0.6844, 0.6879, 0.6915, 0.6950, 0.6985, 0.7019, 0.7054, 0.7088, 0.7123, 0.7157, 0.7190, 0.7224,
        0.7257, 0.7291, 0.7324, 0.7357, 0.7389, 0.7422, 0.7454, 0.7486, 0.7517, 0.7549, 0.7580, 0.7611,
        0.7642, 0.7673, 0.7703, 0.7734, 0.7764, 0.7794, 0.7823, 0.7852, 0.7881, 0.7910, 0.7939, 0.7967,
        0.7995, 0.8023, 0.8051, 0.8078, 0.8106, 0.8133, 0.8159, 0.8186, 0.8212, 0.8238, 0.8264, 0.8289,
        0.8315, 0.8340, 0.8365, 0.8389, 0.8413, 0.8438, 0.8461, 0.8485, 0.8508, 0.8531, 0.8554, 0.8577,
        0.8599, 0.8621, 0.8643, 0.8665, 0.8686, 0.8708, 0.8729, 0.8749, 0.8770, 0.8790, 0.8810, 0.8830,
        0.8849, 0.8869, 0.8888, 0.8907, 0.8925, 0.8944, 0.8962, 0.8980, 0.8997, 0.9015, 0.9032, 0.9049,
        0.9066, 0.9082, 0.9099, 0.9115, 0.9131, 0.9147, 0.9162, 0.9177, 0.9192, 0.9207, 0.9222, 0.9236,
        0.9251, 0.9265, 0.9279, 0.9292, 0.9306, 0.9319, 0.9332, 0.9345, 0.9357, 0.9370, 0.9382, 0.9394,
        0.9406, 0.9418, 0.9429, 0.9441, 0.9452, 0.9463, 0.9474, 0.9484, 0.9495, 0.9505, 0.9515, 0.9525,
        0.9535, 0.9545, 0.9554, 0.9564, 0.9573, 0.9582, 0.9591, 0.9599, 0.9608, 0.9616, 0.9625, 0.9633,
        0.9641, 0.9649, 0.9656, 0.9664, 0.9671, 0.9678, 0.9686, 0.9693, 0.9699, 0.9706, 0.9713, 0.9719,
        0.9726, 0.9732, 0.9738, 0.9744, 0.9750, 0.9756, 0.9761, 0.9767, 0.9772, 0.9778, 0.9783, 0.9788,
        0.9793, 0.9798, 0.9803, 0.9808, 0.9812, 0.9817, 0.9821, 0.9826, 0.9830, 0.9834, 0.9838, 0.9842,
        0.9846, 0.9850, 0.9854, 0.9857, 0.9861, 0.9864, 0.9868, 0.9871, 0.9875, 0.9878, 0.9881, 0.9884,
        0.9887, 0.9890, 0.9893, 0.9896, 0.9898, 0.9901, 0.9904, 0.9906, 0.9909, 0.9911, 0.9913, 0.9916,
        0.9918, 0.9920, 0.9922, 0.9925, 0.9927, 0.9929, 0.9931, 0.9932, 0.9934, 0.9936, 0.9938, 0.9940,
        0.9941, 0.9943, 0.9945, 0.9946, 0.9948, 0.9949, 0.9951, 0.9952, 0.9953, 0.9955, 0.9956, 0.9957,
        0.9959, 0.9960, 0.9961, 0.9962, 0.9963, 0.9964, 0.9965, 0.9966, 0.9967, 0.9968, 0.9969, 0.9970,
        0.9971, 0.9972, 0.9973, 0.9974, 0.9974, 0.9975, 0.9976, 0.9977, 0.9977, 0.9978, 0.9979, 0.9979,
        0.9980, 0.9981, 0.9981, 0.9982, 0.9982, 0.9983, 0.9984, 0.9984, 0.9985, 0.9985, 0.9986, 0.9986,
        0.9987, 0.9987, 0.9987, 0.9988, 0.9988, 0.9989, 0.9989, 0.9989, 0.9990, 0.9990, 0.9990, 0.9991,
        0.9991, 0.9991, 0.9992, 0.9992, 0.9992, 0.9992, 0.9993, 0.9993, 0.9993, 0.9993, 0.9994, 0.9994,
        0.9994, 0.9994, 0.9994, 0.9995, 0.9995, 0.9995, 0.9995, 0.9995, 0.9995, 0.9996, 0.9996, 0.9996,
        0.9996, 0.9996, 0.9996, 0.9997, 0.9997, 0.9997, 0.9997, 0.9997, 0.9997, 0.9997, 0.9997, 0.9997,
        0.9997, 0.9998, 0.9998};

        //Recopy values into fields
        size_t sDevSize = sizeof(sDevTmp);
        sDev_size = sDevSize / sizeof(double);
        sDev = (double*) malloc(sDevSize);
        memcpy(sDev, sDevTmp, sDevSize);
        size_t belowSize = sizeof(belowTmp);
        below_size = belowSize / sizeof(double);
        below = (double*) malloc(belowSize);
        memcpy(below, belowTmp, belowSize);
    }

    void setCutOff(double p) {
        m_cutoff = p;
    }

    /** Lookup the fraction of the set that is expected to be below this many standard
     * deviations away from the mean. */
     double getBelow (double stdDev) {

         if (stdDev > maxSdev) return 1.0;
         if (stdDev < 0.0) return getBelow(-stdDev);

         double* idx = lower_bound(sDev, sDev + sDev_size, stdDev);
         if (*idx == stdDev) {
             return *idx;
         }
         if (idx - below == 0) {
             return below[0];
         } else {
             //interpolate the border values
             return (*idx + *(--idx)) / 2.0;
         }
     }

    /** Lookup the fraction of the set that is expected to be above this many standard
    * deviations away from the mean. */
    double getAbove(double stdDev) {
        return 1.0 - getBelow(stdDev);
    }

    ///
    /// \brief reject
    ///     Apply Chauvenet's criterion to determine if the value is
    ///     with p probability an outlier.
    /// \param stdDevDist
    /// \param count
    /// \return true if it is considered as an outlier, false otherwise.
    ///
    bool reject(double stdDevDist, int count) {
        return 2.0 * getAbove(stdDevDist) * count < m_cutoff; //p = Chauvenet cutoff
    }
};

///
/// \brief rescaleExcentricValues
///     Apply Chauvenet's criterion to identify outliers.
///     An outlier is interpolated with its two non-outlier neighbors.
///     http://en.wikipedia.org/wiki/Chauvenet%27s_criterion
/// \param array
/// \param precomputedAverage
///
static QString rescaleExcentricValues(vector<float>& array
                                      , float tolerance = 0.f
                                      , double p = 0.5
                                      , float precomputedAverage = 0) {
    if (precomputedAverage == 0) {
        precomputedAverage = sum(array) / (float) array.size();
    }

    if (tolerance == 0) {
        tolerance = -FLT_MAX;
    }

    //mean and standard deviation
    double mean(precomputedAverage);
    double stdDev(0.0);
    foreach (float f, array) {
        double diff = f - mean;
        stdDev += diff * diff;
    }
    stdDev /= array.size();
    stdDev = sqrt(stdDev);

    Chauvenet rejectTest;
    if (p > 0 && p < 1) {
        rejectTest.setCutOff(p);
    }

    //identify outliers
    vector<int> rejected;
    int count = array.size();
    QString dbg;
//    dbg += "size " + QString::number(array.size());
//    dbg += " , p = " + QString::number(p) + "\n";
    //avoid borders
    for (int i(0); i < count; ++i) {
        double distance (mean - array[i]);
        if (abs(distance) < tolerance) { continue; } //we tolerate values below that distance
        double stdDevDist(distance / stdDev);
        if (rejectTest.reject(stdDevDist, count)) {
            rejected.push_back(i);

//           dbg += "rejected : " + QString::number(i) + "(" + QString::number(array[i]) + ")\n";
        } else {
//            dbg += "keep : " + QString::number(i) + "(" + QString::number(array[i]) + ")\n";
        }
    }

    //interpolation
    for (int i(0); i < rejected.size(); ++i) {
        int curIndex(rejected.at(i));
        int nextIndex(rejected.at(i == rejected.size() - 1 ? i : i+1));
        int oldNextIndex(curIndex);

        //check if consecutive indices
        while (oldNextIndex == nextIndex - 1) {
            if (i >= rejected.size() - 1) {
                break;
            }
            ++i;
            oldNextIndex = nextIndex;
            nextIndex = rejected.at(i == rejected.size() - 1 ? i : i + 1);
        }

        //interpolate
        float meanValue;
        if (curIndex == 0) {
            //oldNextIndex might never overflow, because at least one
            //element is < 1/pn
            meanValue = array.at(oldNextIndex + 1);
        } else if (oldNextIndex == array.size() - 1) {
            meanValue = array.at(curIndex - 1);
        } else {
            meanValue = (array.at(curIndex - 1) + array.at(oldNextIndex + 1)) / 2.f;
        }

        for (int j(curIndex); j <= oldNextIndex; ++j) {
            array[j] = meanValue;
        }
    }
 return dbg;
}

///
/// \brief cloche
///     Cloche (~Bell) function
/// \param x
/// \param length
/// \param center
/// \return
///
inline float cloche (float x, int length, float center) {
    float pi = 3.14159265359;
    return sin(x * 2.f * pi / length - pi / 2.f) * center / 2.f + (center / 2.f);
}

///
/// \brief applyClocheFilter
///     The value that is right under the center of the filter will be amplify the most.
///     The farthest it is from the center, the less the amplification it is.
///     The fit factor adjusts the effect of the filter.
///     The mods are the following :
///         - 1 : Amplify the most where there is most motion only.
///         - 2 : Relative difference from the filter is used to amplify the values.
///         - 3 : Adaptive amplification with fit factor.
///     Note : designed for being applied correctly when filter center y is negative.
/// \param array
/// \param center_x (index in the array)
/// \param center_y
/// \param mod
/// \param fitFactor
/// \return hint depending on the mod
///
static float applyClocheFilter(vector<float>& array, const int& center_x
                              , const int& center_y, const int& mod, const float& fitFactor, const bool& highpass) {

    int size(array.size());
    auto& X = array;
    auto& Y = array;

    if (center_x <= 0 || center_x >= size) {
        return 0.f;
    }

    for (int part(1); part <= 2; ++part) {
        //range param init
        int start; // [start, ...
        int end;   //   ... , end]
        int length;
        int offset;
        switch (part) {
        //first half
        /*
         *       *
         *     .
         *    .
         *   .
         * .
         * _____________________
         */
        case 1:
            start = 0;
            end = center_x;
            length = (center_x + 1) * 2;
            offset = 0;
            break;
        //second half
        /*
         *       *
         *         .
         *           .
         *              .
         *                  .
         * _____________________
         */
        case 2:
            start = center_x + 1;
            end = size - 1;
            length = (size - center_x - 1) * 2;
            offset = - center_x + length / 2;
            break;
        }
//        qDebug() << "s : " << start << " e : " << end << " length : " << length << " of : " << offset;
//        qDebug() << "fit : " << fitFactor << " mod : " << mod;
        //filter loop
        for (int i(start); i <= end; ++i) {
            float Fi = cloche(i + offset, length, center_y);
            switch (mod) {
            case 1: //preserve motion
                Y[i] = X[i] * -Fi;
                break;
            case 2: //diff * amp
                Y[i] = X[i] + (Fi - X[i]) * ((part==1) ? ((float) i / (float) end) : ((float) start / (float) i));
                break;
            case 3: //adaptive
                Y[i] = X[i] + Fi;
                break;
            default:
                return 0.f;
            }

            Y[i] = Y[i] / fitFactor;

            //if needed, cut values outide the filter
            if (highpass) {
                if (Y[i] < Fi) {
                    Y[i] = Fi;
                }
            }
        }
    }

    return 0.f;

}

}

#endif // FILTERING_H
