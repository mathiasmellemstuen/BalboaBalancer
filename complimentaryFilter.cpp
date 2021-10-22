#include "compimentaryFilter.h"

float complimentaryFilter(const float& accelerometerValue, const float& gyroscopeValue, const float& omega, const float& alpha, const float& deltaTime) {

    float gyroscopeIntergrate = gyroscopeValue + omega * deltaTime;

    return alpha * gyroscopeIntergrate + (1.0f - alpha) * accelerometerValue;
}