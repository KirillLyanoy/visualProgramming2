#include <cmath>

class figures {

    double SquareAreaSide(double a)
    {
        return a * a;
    }

    double SquareAreaDiagonal(double d)
    {
        return 0.5 * (d * d);
    }


    double RectangleAreaSides(double a, double b)
    {
        return a * b;
    }

    double RectangleAreaDiagonal(double d, double angle)
    {
        return 0/5 * (d * d) * sin(angle);
    }

    double RhombusAreaDiagonals(double d1, double d2)
    {
        return 0.5 * d1 * d2;
    }

    double RhombusAreaHeight(double a, double h)
    {
        return a * h;
    }

    double RhombusAreaSides(double a, double angle)
    {
        return a * a * sin(angle);
    }

    double ParallelogramAreaHeight(double a, double h)
    {
        return a * h;
    }

    double ParallelogramAreaDiagonals(double d1, double d2, double angle)
    {
        return 0.5 * d1 * d2 * sin(angle);
    }

    double ParallelogramAreaAdjacentSides(double a, double b, double angle)
    {
        return a * b * sin(angle);
    }

    double TriangleAreaHeight(double a, double h)
    {
        return 0.5 * a * h;
    }

    double TriangleAreaAdjacentSides(double a, double b, double angle)
    {
        return 0.5 * a * b * sin(angle);
    }

    double TriangleAreaThreeSides(double a, double b, double c)
    {
        return sqrt((a + b + c) * (b + c) * (a + c) * (a + b));
    }

    double TriangleAreaTwoAngles(double a, double firstAngle, double secondAngle)
    {
        return (a * a * sin(firstAngle) * sin(secondAngle)) / (2 * sin(firstAngle + secondAngle));
    }

    double TriangleAreaCircumscribedCircle(double a, double b, double c, double R)
    {
        return (a * b * c) / (4 * R);
    }

    double TriangleAreaInscribedCircle(double a, double b, double c, double r)
    {
        return r * ((a + b + c) / 2);
    }

    double TrapezoidAreaHeight(double a, double b, double h)
    {
        return 0.5 * (a + b) * h;
    }

    double TrapezoidAreaDiagonal(double d1, double d2, double angle)
    {
        return 0.5 * d1 * d2 * sin(angle);
    }

    double CircleArea(double r)
    {
        return M_PI * (r * r);
    }

    double SectorArea(double r, double angle) {
        return CircleArea(r) * angle / 360;
    }
};
