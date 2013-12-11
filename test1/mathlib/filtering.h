#ifndef FILTERING_H
#define FILTERING_H

#include <vector>
#include <iostream>

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
void movingAverage(const vector<float>& input, vector<float>& output, float ws) {
    if (input.size() < ws) { std::cout << "ws too big" << std::endl; return; }

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

    for(int i = bindex; i < ws; ++i) {
        csum += input.at(i);
    }

    for(int i = bindex; i <= eindex; ++i) {
        output.push_back(csum / ws);
        if (i == eindex) { break; }
        csum += input.at(i + hws + 1);
        csum -= input.at(i - hws);
    }

    for(int i = eindex + 1; i < size - 1; ++i) {
        output.push_back(sum(input, 2 * (i + 1) - size - 1, size - 1) / ((float)(2 * (size - i - 1) + 1)));
    }
    output.push_back(input.back());
}

}

#endif // FILTERING_H
