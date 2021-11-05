#ifndef BALBOA_BALANCER_VEC3
#define BALBOA_BALANCER_VEC3

#include <LSM6.h>

template <class T>
struct vec3 {
    T x=0,y=0,z=0;

    vec3() {

    };

    vec3(T nx, T ny, T nz) {
        x = nx;
        y = ny;
        z = nz;
    };

    // Overloading
    vec3& operator+=(const vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }

    vec3& operator+=(const LSM6::vector<int16_t>& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }

    vec3& operator/(const int& other) {
        this->x / other;
        this->y / other;
        this->z / other;

        return *this;
    }

    vec3& operator=(const vec3& other) {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;

        return *this;
    }

    // Functions
    T power(const vec3& other, int power) {
        return pow(other.x,power) + pow(other.y,power) + pow(other.z,power);
    }
};

#endif