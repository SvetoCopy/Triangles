#include "Triangle.h"
#include "Vector.h"
#include <list>
#include <vector>

struct BoundingBox {
    // object diags vectors
    Vector3D min;
    Vector3D max; 
    BoundingBox() : min{0, 0, 0}, max{0, 0, 0} {};  
    BoundingBox(Vector3D min, Vector3D max) : min{min}, max{max} {};  

    bool contains(const Triangle3D& tri) const;
    bool contains(const Point3D& p) const;
};

class OctTree {
public:
    BoundingBox region;
    std::list<Triangle3D> region_elems;

    std::vector<OctTree> childNodes;
    OctTree* parent;

    OctTree(const BoundingBox& region, const std::list<Triangle3D>& region_elems) : region {region}, region_elems{region_elems} {};
    void BuildTree();

    OctTree CreateNode(const BoundingBox& region, const std::list<Triangle3D>& objList);
    size_t getTreeIntersectNum() const;
    size_t getAllTreeIntersectNum() const;
};