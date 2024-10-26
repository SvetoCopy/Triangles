#include "OctTree.h"
#include <iostream>

int main() {
    std::list<Triangle3D> list;
    int n = 0;
    std::cin >> n;

    float min_x = 1000000;
    float min_y = 1000000;
    float min_z = 1000000;

    float max_x = -1000000;
    float max_y = -1000000;
    float max_z = -1000000;

    for (int i = 0; i < n; i++) {
        Triangle3D tr {};
        std::cin >> tr.v0.x >> tr.v0.y >> tr.v0.z;
        std::cin >> tr.v1.x >> tr.v1.y >> tr.v1.z;
        std::cin >> tr.v2.x >> tr.v2.y >> tr.v2.z;

        tr.id = i;
        
        min_x = std::min(min_x, std::min(tr.v0.x, std::min(tr.v1.x, tr.v2.x)));
        min_y = std::min(min_y, std::min(tr.v0.y, std::min(tr.v1.y, tr.v2.y)));
        min_z = std::min(min_z, std::min(tr.v0.z, std::min(tr.v1.z, tr.v2.z)));

        max_x = std::max(max_x, std::max(tr.v0.x, std::max(tr.v1.x, tr.v2.x)));
        max_y = std::max(max_y, std::max(tr.v0.y, std::max(tr.v1.y, tr.v2.y)));
        max_z = std::max(max_z, std::max(tr.v0.z, std::max(tr.v1.z, tr.v2.z)));

        list.push_back(tr);
    }

    BoundingBox bb (Vector3D(min_x, min_y, min_z), Vector3D(max_x, max_y, max_z));
    
    OctTree tree{bb, list};
    tree.BuildTree();

    std::list<int> res = tree.getAllTreeIntersectNum();

    std::cout << res.size() << '\n';

    for (auto elem : res) {
        std::cout << elem << '\n';
    }
}