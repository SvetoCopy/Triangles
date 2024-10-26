#include "Triangle.h"
#include "GeomFunctions.h"

bool Triangle3D::isDegenerate() const {
    float first_fraq  = (v2.x - v0.x) / (v1.x - v0.x);
    float second_fraq = (v2.y - v0.y) / (v1.y - v0.y);
    float third_fraq  = (v2.z - v0.z) / (v1.z - v0.z);

    return (isEqual(first_fraq, second_fraq) && isEqual(second_fraq, third_fraq) && isEqual(first_fraq, third_fraq)) 
            || (v0 == v1) || (v0 == v2) || (v1 == v2);
}

void Triangle3D::print() {
    v0.print();
    v1.print();
    v2.print();
}

bool haveSameSign(float n1, float n2, float n3) {
    return ((n1 > 0 && n2 > 0 && n3 > 0) || (n1 < 0 && n2 < 0 && n3 < 0));
}

Interval calculateInterval(float v_pr_0, float v_pr_1, float v_pr_2,
                           float dist_v_0, float dist_v_1, float dist_v_2) {

    double t0  = v_pr_0 + (v_pr_1 - v_pr_0) * (dist_v_0 / (dist_v_0 - dist_v_1));
    double t1 = v_pr_0 + (v_pr_2 - v_pr_0) * (dist_v_0 / (dist_v_0 - dist_v_2));

    return Interval(t0, t1);
}

Interval calculateTriInterval(float v_pr_0, float v_pr_1, float v_pr_2,
                              float dist_v_0, float dist_v_1, float dist_v_2){ 

    if (dist_v_0 * dist_v_1 > 0)
        return calculateInterval(v_pr_2,  v_pr_0,  v_pr_1,
                               dist_v_2, dist_v_0, dist_v_1);
    else if (dist_v_0 * dist_v_2 > 0)
        return calculateInterval(v_pr_1,  v_pr_0,  v_pr_2,
                               dist_v_1, dist_v_0, dist_v_2);

    else if (dist_v_1 * dist_v_2 > 0 || !isEqual(dist_v_0, 0))
        return calculateInterval(v_pr_0,  v_pr_1,  v_pr_2,
                               dist_v_0, dist_v_1, dist_v_2);
    
    else if (!isEqual(dist_v_1, 0))
        return calculateInterval(v_pr_1,  v_pr_0,  v_pr_2,
                               dist_v_1, dist_v_0, dist_v_2);
    
    else if (!isEqual(dist_v_2, 0))
        return calculateInterval(v_pr_2,  v_pr_0,  v_pr_1,
                               dist_v_2, dist_v_0, dist_v_1);
}

bool Triangle3D::intersectWith(Triangle3D& triang) {
    if (this->isDegenerate() || triang.isDegenerate())
        return false;

    Plane tr0_plane = Plane(*this);
    Plane tr1_plane = Plane(triang);

    if (tr1_plane.parallelWith(tr0_plane)) {
        if (tr0_plane == tr1_plane) {
            if (!isEqual(tr0_plane.norm.vec_end.x, 0)) {
                Triangle2D tr1 {Point2D(this->v0.y, this->v0.z), Point2D(this->v1.y, this->v1.z), Point2D(this->v2.y, this->v2.z)};
                Triangle2D tr2 {Point2D(triang.v0.y, triang.v0.z), Point2D(triang.v1.y, triang.v1.z), Point2D(triang.v2.y, triang.v2.z)};

                return tr1.intersectWith(tr2);
            }
            else if (!isEqual(tr0_plane.norm.vec_end.y, 0)) {
                Triangle2D tr1 {Point2D(this->v0.x, this->v0.z), Point2D(this->v1.x, this->v1.z), Point2D(this->v2.x, this->v2.z)};
                Triangle2D tr2 {Point2D(triang.v0.x, triang.v0.z), Point2D(triang.v1.x, triang.v1.z), Point2D(triang.v2.x, triang.v2.z)};
                
                return tr1.intersectWith(tr2);
            }
            else if (!isEqual(tr0_plane.norm.vec_end.z, 0)) {
                Triangle2D tr1 {Point2D(this->v0.x, this->v0.y), Point2D(this->v1.x, this->v1.y), Point2D(this->v2.x, this->v2.y)};
                Triangle2D tr2 {Point2D(triang.v0.x, triang.v0.y), Point2D(triang.v1.x, triang.v1.y), Point2D(triang.v2.x, triang.v2.y)};
                
                return tr1.intersectWith(tr2);
            }
        }
        else return false;
    }    

    float dist_v_0_0 = tr1_plane.distanceFromPoint(this->v0);
    float dist_v_0_1 = tr1_plane.distanceFromPoint(this->v1);
    float dist_v_0_2 = tr1_plane.distanceFromPoint(this->v2);

    if (haveSameSign(dist_v_0_0, dist_v_0_1, dist_v_0_2))
        return false;

    float dist_v_1_0 = tr0_plane.distanceFromPoint(triang.v0);
    float dist_v_1_1 = tr0_plane.distanceFromPoint(triang.v1);
    float dist_v_1_2 = tr0_plane.distanceFromPoint(triang.v2);

    if (haveSameSign(dist_v_1_0, dist_v_1_1, dist_v_1_2))
        return false;

    Line3D line = getPlanesInterLine(tr0_plane, tr1_plane);
    
    float v_pr_0_0 = line.dist & Vector3D((*this).v0 - line.p);
    float v_pr_0_1 = line.dist & Vector3D((*this).v1 - line.p);
    float v_pr_0_2 = line.dist & Vector3D((*this).v2 - line.p);

    float v_pr_1_0 = line.dist & Vector3D(triang.v0 - line.p);
    float v_pr_1_1 = line.dist & Vector3D(triang.v1 - line.p);
    float v_pr_1_2 = line.dist & Vector3D(triang.v2 - line.p);

    Interval interval0 = calculateTriInterval(v_pr_0_0, v_pr_0_1, v_pr_0_2, dist_v_0_0, dist_v_0_1, dist_v_0_2);
    Interval interval1 = calculateTriInterval(v_pr_1_0, v_pr_1_1, v_pr_1_2, dist_v_1_0, dist_v_1_1, dist_v_1_2);

    return interval0.overlapWith(interval1);
}


// Triangle2D

void Triangle2D::print() {
    v0.print();
    v1.print();
    v2.print();
}

bool Triangle2D::hasPointInside(const Point2D& point) {
    Vector2D OA = Vector2D(v0 - point);
    Vector2D OB = Vector2D(v1 - point);
    Vector2D OC = Vector2D(v2 - point);

    float p = OA * Vector2D(v1 - v0);
    float q = OB * Vector2D(v2 - v1);
    float r = OC * Vector2D(v0 - v2);

    return (p <= 0 && q <= 0 && r <= 0) || (p >= 0 && q >= 0 && r >= 0);
}

inline double Det2D(const Triangle2D& triangle)
{
    return +triangle.v0.x* (triangle.v1.y- triangle.v2.y)
        + triangle.v1.x * (triangle.v2.y - triangle.v0.y)
        + triangle.v2.x * (triangle.v0.y - triangle.v1.y);
}

bool BoundaryCollideChk(const Triangle2D& t)
{
    return Det2D(t) < EPSILON;
}
 
bool BoundaryCollideChk(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
    Triangle2D t = {p1, p2, p3};
    return BoundaryCollideChk(t);
}

bool BoundaryCollideChk(const Point2D& p1, const Point2D& p2, const Triangle2D& t) {
    return BoundaryCollideChk(p1, p2, t.v0) && BoundaryCollideChk(p1, p2, t.v1) && BoundaryCollideChk(p1, p2, t.v2);
}

void Triangle2D::repairWinding() {
    double detTri = Det2D(*this);

    if (detTri < 0.0)
    {
        Point2D v0_old = v0;
        v0 = v2;
        v2 = v0_old;
    }
}

bool Triangle2D::intersectWith(Triangle2D& triang) {
    
    repairWinding();
    triang.repairWinding();

    if (BoundaryCollideChk(v0, v1, triang) ||
        BoundaryCollideChk(v1, v2, triang) ||
        BoundaryCollideChk(v2, v0, triang)) {
        return false;
    }

    if (BoundaryCollideChk(triang.v0, triang.v1, *this) ||
        BoundaryCollideChk(triang.v1, triang.v2, *this) ||
        BoundaryCollideChk(triang.v2, triang.v0, *this))
    {
        return false;
    }

    return true;
}