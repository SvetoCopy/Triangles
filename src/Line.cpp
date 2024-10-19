#include "Line.h"

bool Line3D::havePoint(const Point3D& point) {
    Vector3D vec {p - point};
    return vec.colleniarWith(dist);
}

Point3D Line3D::getPointByParameter(float param) {
    return p + (dist * param).vec_end;
}

void Line3D::print() { 
    std::cout << "Line3D vector:\n";
    dist.print();
    std::cout << "Line3D point:\n";
    p.print();
}


int orientation(const Point2D& p, const Point2D& q, const Point2D& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2;
}

bool onSegment(const Point2D& p, const Point2D& q, const Point2D& r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}


bool Line2D::intersectWith(const Line2D& line) {
    int o1 = orientation(p1, p2, line.p1);
    int o2 = orientation(p1, p2, line.p2);
    int o3 = orientation(line.p1, line.p2, p1);
    int o4 = orientation(line.p1, line.p2, p2);

    if (o1 != o2 && o3 != o4)
        return true;

    // Особые случаи
    // A, B и C коллинеарны и C лежит на отрезке AB
    if (o1 == 0 && onSegment(p1, line.p1, p2)) return true;

    // A, B и D коллинеарны и D лежит на отрезке AB
    if (o2 == 0 && onSegment(p1, line.p2, p2)) return true;

    // C, D и A коллинеарны и A лежит на отрезке CD
    if (o3 == 0 && onSegment(line.p1, p1, line.p2)) return true;

    // C, D и B коллинеарны и B лежит на отрезке CD
    if (o4 == 0 && onSegment(line.p1, p2, line.p2)) return true;

    // Не пересекаются
    return false;
}

void Line2D::print() { 
    std::cout << "Line2D p1:\n";
    p1.print();
    std::cout << "Line2D p2:\n";
    p2.print();
}
