import jtrace
from test_helpers import isclose


def test_properties():
    import random
    random.seed(5)
    for i in range(100):
        A = random.gauss(0.7, 0.8)
        B = random.gauss(0.8, 1.2)
        para = jtrace.Paraboloid(A, B)
        assert para.A == A
        assert para.B == B


def test_call():
    import random
    random.seed(57)
    for i in range(100):
        A = random.gauss(0.2, 0.3)
        B = random.gauss(0.4, 0.2)
        para = jtrace.Paraboloid(A, B)
        for j in range(10):
            x = random.gauss(0.0, 1.0)
            y = random.gauss(0.0, 1.0)
            assert isclose(para(x, y), A*(x*x + y*y)+B)


def test_intersect():
    import random
    random.seed(577)
    for i in range(100):
        A = random.gauss(0.05, 0.01)
        B = random.gauss(0.4, 0.2)
        para = jtrace.Paraboloid(A, B)
        for j in range(10):
            x = random.gauss(0.0, 1.0)
            y = random.gauss(0.0, 1.0)

            # If we shoot rays straight up, then it's easy to predict the
            # intersection points.
            r = jtrace.Ray(x, y, -1000, 0, 0, 1, 0)
            isec = para.intersect(r)
            assert isclose(isec.point.x, x)
            assert isclose(isec.point.y, y)
            assert isclose(isec.point.z, para(x, y), rel_tol=0, abs_tol=1e-9)

            # We can also check just for mutual consistency of the paraboloid,
            # ray and intersection.

            vx = random.gauss(0.0, 0.1)
            vy = random.gauss(0.0, 0.1)
            vz = 1.0
            v = jtrace.Vec3(vx, vy, vz).UnitVec3()
            r = jtrace.Ray(jtrace.Vec3(x, y, -10), v, 0)
            isec = para.intersect(r)
            p1 = r(isec.t)
            p2 = isec.point
            assert isclose(p1.x, p2.x)
            assert isclose(p1.y, p2.y)
            assert isclose(p1.z, p2.z)
            assert isclose(para(p1.x, p2.y), p1.z, rel_tol=0, abs_tol=1e-6)


if __name__ == '__main__':
    test_properties()
    test_call()
    test_intersect()