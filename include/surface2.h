#ifndef batoid_surface2_h
#define batoid_surface2_h

#include <vector>
#include <memory>
#include <utility>
#include "rayVector2.h"
#include "medium2.h"
//#include "coating.h"

#include <Eigen/Dense>

using Eigen::Vector3d;

namespace batoid {
    class Surface2 {
    public:
        virtual ~Surface2() {}

        virtual double sag(double, double) const = 0;
        virtual void normal(double, double, double&, double&, double&) const = 0;
        virtual bool timeToIntersect(double, double, double, double, double, double, double& t) const = 0;

        virtual void intersectInPlace(RayVector2&) const = 0;
        virtual void reflectInPlace(RayVector2&) const = 0;
        virtual void refractInPlace(RayVector2&, const Medium2&, const Medium2&) const = 0;
    };

    template<typename T>
    class Surface2CRTP : public Surface2 {
    public:
        virtual double sag(double, double) const override;
        virtual void normal(double, double, double&, double&, double&) const override;
        virtual bool timeToIntersect(double, double, double, double, double, double, double& t) const override;

        virtual void intersectInPlace(RayVector2&) const override;
        virtual void reflectInPlace(RayVector2&) const override;
        virtual void refractInPlace(RayVector2&, const Medium2&, const Medium2&) const override;
    };

    // Declare specializations
    class Plane2;
    template<> void Surface2CRTP<Plane2>::intersectInPlace(RayVector2&) const;
    template<> void Surface2CRTP<Plane2>::reflectInPlace(RayVector2&) const;
    template<> void Surface2CRTP<Plane2>::refractInPlace(RayVector2&, const Medium2&, const Medium2&) const;
}
#endif