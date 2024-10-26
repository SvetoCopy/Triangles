#include "OctTree.h"

const int MIN_SIZE = 1;

bool BoundingBox::contains(const Point3D& p) const {
    return (p.x >= min.vec_end.x) && (p.y >= min.vec_end.y) && (p.z >= min.vec_end.z) &&
           (p.x <= max.vec_end.x) && (p.y <= max.vec_end.y) && (p.z <= max.vec_end.z);
}

bool BoundingBox::contains(const Triangle3D& tri) const {
    return contains(tri.v0) && contains(tri.v1) && contains(tri.v2);
}

void OctTree::BuildTree() {
    if (region_elems.size() <= 1)
		return;

	Vector3D dimensions = region.max - region.min;

	if (dimensions.vec_end.x <= MIN_SIZE && dimensions.vec_end.y <= MIN_SIZE && dimensions.vec_end.z <= MIN_SIZE)
		return;

	Vector3D half = dimensions / 2.0f;
	Vector3D center = region.min + half;

	BoundingBox* octant = new BoundingBox[8];

	octant[0] = BoundingBox(region.min, center);
	octant[1] = BoundingBox(Vector3D(center.vec_end.x, region.min.vec_end.y, region.min.vec_end.z), 
                            Vector3D(region.max.vec_end.x, center.vec_end.y, center.vec_end.z));

	octant[2] = BoundingBox(Vector3D(center.vec_end.x, region.min.vec_end.y, center.vec_end.z), 
                            Vector3D(region.max.vec_end.x, center.vec_end.y, region.max.vec_end.z));

	octant[3] = BoundingBox(Vector3D(region.min.vec_end.x, region.min.vec_end.y, center.vec_end.z), 
                            Vector3D(center.vec_end.x, center.vec_end.y, region.max.vec_end.z));
	
    octant[4] = BoundingBox(Vector3D(region.min.vec_end.x, center.vec_end.y, region.min.vec_end.z), 
                            Vector3D(center.vec_end.x, region.max.vec_end.y, center.vec_end.z));

	octant[5] = BoundingBox(Vector3D(center.vec_end.x, center.vec_end.y, region.min.vec_end.z), 
                            Vector3D(region.max.vec_end.x, region.max.vec_end.y, center.vec_end.z));

	octant[6] = BoundingBox(center, region.max);

	octant[7] = BoundingBox(Vector3D(region.min.vec_end.x, center.vec_end.y, center.vec_end.z), 
                            Vector3D(center.vec_end.x, region.max.vec_end.y, region.max.vec_end.z));

	std::list<Triangle3D>* octList = new std::list<Triangle3D>[8];

	using list_iter = std::list<Triangle3D>::iterator;

    list_iter it = region_elems.begin();
	std::list<list_iter> to_delete;

    while(it != region_elems.end()) {
        Triangle3D obj = *it;
        if (!obj.isDegenerate()) {
			for (int a = 0; a < 8; a++) {
				if (octant[a].contains(obj)) {
					octList[a].push_back(obj);
					to_delete.push_back(it);
					break;
				}
			}
		}
		it++;
    }

	for (auto elem : to_delete)
		region_elems.erase(elem);

	childNodes = std::vector<OctTree>(8);

	//Создаём дочерние узлы, в которых находятся элементы, содержащиеся в ограничивающей области
	for (int a = 0; a < 8; a++)
	{
		if (octList[a].size() != 0)
		{
			childNodes[a] = OctTree(octant[a], octList[a]);
			childNodes[a].parent = this;
			childNodes[a].BuildTree();
		}
	}
}

std::list<int> OctTree::getTreeIntersectNum(std::list<Triangle3D> parentObjs) const {

	std::list<int> intersects;

	for (auto it1 = region_elems.begin(); it1 != region_elems.end(); ++it1) {
		bool is_added = false;
		for (auto it2 = parentObjs.begin(); it2 != parentObjs.end(); ++it2) {
			Triangle3D tr1 = *it1;
			Triangle3D tr2 = *it2;

			if(tr1.intersectWith(tr2)) {
				intersects.push_back(tr2.id);

				if (!is_added) {
					is_added = true;
					intersects.push_back(tr1.id);
				}
			}
		}
	}

	for (auto it1 = region_elems.begin(); it1 != region_elems.end(); ++it1) {
		bool is_added = false;
        for (auto it2 = std::next(it1); it2 != region_elems.end(); ++it2) {
			Triangle3D tr1 = *it1;
			Triangle3D tr2 = *it2;
            
			if(tr1.intersectWith(tr2)) {
				intersects.push_back(tr2.id);

				if (!is_added) {
					is_added = true;
					intersects.push_back(tr1.id);
				}
			}
        }
    }

	for (auto child : childNodes) {
		parentObjs.insert(parentObjs.end(), region_elems.begin(), region_elems.end());
		intersects.unique();
		intersects.sort();
		intersects.merge(child.getTreeIntersectNum(parentObjs));
	}

	return intersects;
}

std::list<int> OctTree::getAllTreeIntersectNum() const {
	std::list<Triangle3D> empty;
	std::list<int> ret = getTreeIntersectNum(std::list<Triangle3D>());
	ret.unique();
	
	return ret;
}