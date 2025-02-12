#include <cmath>

class FiguresArea {
public:
    double DegToRad(double Deg)
    {
        return Deg * M_PI / 180;
    }

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
        return 0.5 * (d * d) * sin(DegToRad(angle));
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
        return a * a * sin(DegToRad(angle));
    }

    double ParallelogramAreaHeight(double a, double h)
    {
        return a * h;
    }

    double ParallelogramAreaDiagonals(double d1, double d2, double angle)
    {
        return 0.5 * d1 * d2 * sin(DegToRad(angle));
    }

    double ParallelogramAreaAdjacentSides(double a, double b, double angle)
    {
        return a * b * sin(DegToRad(angle));
    }

    double TriangleAreaHeight(double a, double h)
    {
        return 0.5 * a * h;
    }

    double TriangleAreaAdjacentSides(double a, double b, double angle)
    {
        return 0.5 * a * b * sin(DegToRad(angle));
    }

    double TriangleAreaThreeSides(double a, double b, double c)
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double TriangleAreaTwoAngles(double a, double firstAngle, double secondAngle)
    {
        return (a * a * sin(DegToRad(firstAngle)) * sin(DegToRad(secondAngle))) / (2 * sin(DegToRad(firstAngle + secondAngle)));
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
        return 0.5 * d1 * d2 * sin(DegToRad(angle));
    }

    double CircleArea(double r)
    {
        return M_PI * (r * r);
    }

    double SectorArea(double r, double angle)
    {
        return CircleArea(r) * DegToRad(angle) / DegToRad(360);
    }
};
