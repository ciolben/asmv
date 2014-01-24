#ifndef BSPLINEFITTER_H
#define BSPLINEFITTER_H

#include "Wm5BSplineCurveFit.h"

namespace BSplineFitter {
using namespace Wm5;

std::pair<float*, char*> reduceKeys(int numSamples, const float* samples, int degree, int numCtrlPoints, bool printError = false) {
    // Create the curve from the current parameters.
    BSplineCurveFitf* spline = new0 BSplineCurveFitf(2, numSamples, samples,
                              degree, numCtrlPoints);

    std::pair<float*, char*> output;

    // Compute error measurements (rms and avg diff)
    if (printError) {

        float* data = (float*) malloc(sizeof(float) * numSamples * 2);
        float mult = 1.f / (numSamples - 1);
        for (int i = 0; i < numSamples; ++i) {
            float* f = (float *) malloc(sizeof(float) * 2);
            spline->GetPosition(mult * i, f);
            data[2*i] = f[0]; data[2*i+1] = f[1];
            delete []f;
        }

        float avrError = 0.0f;
        float rmsError = 0.0f;
        for (int i = 0; i < numSamples; ++i) {
            float diff = samples[i] - data[i];
            float sqrLength = diff * diff;
            rmsError += sqrLength;
            float length = Mathf::Sqrt(sqrLength);
            avrError += length;
        }
        avrError /= (float)numSamples;
        rmsError /= (float)numSamples;
        rmsError = Mathf::Sqrt(rmsError);

        char* descr = (char*) malloc(sizeof(char) * 2 * 12 + 1 + 1);
        std::sprintf(descr, "%f,%f", avrError, rmsError);
        output.second = descr;

        delete []data;

    } else { output.second = NULL; }

    const float* ctrlData = spline->GetControlData();

    //unconst ctrlData
    size_t size = sizeof(float) * spline->GetControlQuantity() * 2;
    float* retData = (float*) malloc(size);
    memcpy(retData, ctrlData, size);

    output.first = retData;

    return output;
}

}

#endif // BSPLINEFITTER_H
