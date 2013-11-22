#ifndef MSVCCOMPAT_H
#define MSVCCOMPAT_H

#define popen   _popen
#define pclose  _pclose
#define exec _exec
static inline double
round(double x) {
    return x >= 0.0 ? floor(x + 0.5) : ceil(x - 0.5);
}

static inline float
roundf(float x) {
    return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}

#endif // MSVCCOMPAT_H
