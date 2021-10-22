#ifndef BALBOA_BALANCER_COMPLIMENTARY_FILTER
#define BALBOA_BALANCER_COMPLIMENTARY_FILTER

// Omega is the rotational velocity from the gyroscope.
float complimentaryFilter(const float& accelerometerValue, const float& gyroscopeValue, const float& omega, const float& alpha, const float& deltaTime);

#endif