#pragma once

#ifndef vec_utils
#define vec_utils

struct vec3
{
    float x = 0;
    float y = 0;
    float z = 0;

    vec3(float x1, float y1, float z1)
    {
        x = x1;
        y = y1;
        z = z1;
    }

    vec3() { x, y, z = 0; }

    vec3 operator + (vec3 const& obj)
    {
        vec3 res;

        res.x = x + obj.x;
        res.y = y + obj.y;
        res.z = z + obj.z;

        return res;
    }

    vec3 operator - (vec3 const& obj)
    {
        vec3 res;

        res.x = x - obj.x;
        res.y = y - obj.y;
        res.z = z - obj.z;

        return res;
    }

    vec3 operator * (vec3 const& obj)
    {
        vec3 res;

        res.x = x * obj.x;
        res.y = y * obj.y;
        res.z = z * obj.z;

        return res;
    }

    vec3 operator / (vec3 const& obj)
    {
        vec3 res;

        res.x = x / obj.x;
        res.y = y / obj.y;
        res.z = z / obj.z;

        return res;
    }

    vec3 operator * (float const& obj)
    {
        vec3 res;

        res.x = x * obj;
        res.y = y * obj;
        res.z = z * obj;

        return res;
    }

    vec3 operator / (float const& obj)
    {
        vec3 res;

        res.x = x / obj;
        res.y = y / obj;
        res.z = z / obj;

        return res;
    }
};

float vec3_dot(vec3& a, vec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

#endif