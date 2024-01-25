#pragma once
#include <mutex>

std::mutex mutex;
int normaliseINT(float n, float start1, float stop1, float start2, float stop2) {
    return round(((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2);
}
int paletteLength = 1;