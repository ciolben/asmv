#ifndef BSPLINEFITTER_H
#define BSPLINEFITTER_H

#include "Wm5BSplineCurveFit.h"

namespace BSplineFitter {
using namespace Wm5;

const float* reduceKeys(int numSamples, const float* samples, int degree, int numCtrlPoints, bool printError = false) {
    // Create the curve from the current parameters.
    BSplineCurveFitf* spline = new0 BSplineCurveFitf(2, numSamples, samples,
                              degree, numCtrlPoints);
    // Compute error measurements.
    if (printError) {
        float avrError = 0.0f;
        float rmsError = 0.0f;
        for (int i = 0; i < numSamples; ++i) {
            float samplifiedPos;
            spline->GetPosition(i / (numSamples - 1), &samplifiedPos);
            float diff = samples[i] - samplifiedPos;
            float sqrLength = diff * diff;
            rmsError += sqrLength;
            float length = Mathf::Sqrt(sqrLength);
            avrError += length;
        }
        avrError /= (float)numSamples;
        rmsError /= (float)numSamples;
        rmsError = Mathf::Sqrt(rmsError);

        std::cout << "avr error : " << avrError
                  << " | rms error : " << rmsError;
    }

    const float* data = spline->GetControlData();
//    size_t size = sizeof(float) * spline->GetControlQuantity();
//    float* retData = (float*) malloc(size);
//    memcpy(retData, data, size);
    return data;
}

}

#endif // BSPLINEFITTER_H
