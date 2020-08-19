#ifndef batoid_coordtransform2_h
#define batoid_coordtransform2_h

#include "coordsys.h"
#include "rayVector2.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Matrix3d;

namespace batoid {
    class CoordTransform2 {
    public:
        CoordTransform2(const CoordSys& source, const CoordSys& destination);
        CoordTransform2(const Vector3d& dr, const Matrix3d& rot);

        void applyForwardInPlace(RayVector2& rv) const;
        void applyReverseInPlace(RayVector2& rv) const;

        const Matrix3d& getRot() const { return _rot; }
        const Vector3d& getDr() const { return _dr; }

        std::string repr() const {
            std::ostringstream oss;
            oss << "CoordTransform2(" << _source << ", " << _destination << ")";
            return oss.str();
        }

        CoordSys getSource() const { return _source; }
        CoordSys getDestination() const { return _destination; }

    private:
        const Vector3d _dr;
        const Matrix3d _rot;
        const CoordSys _source;
        const CoordSys _destination;
    };
}

#endif