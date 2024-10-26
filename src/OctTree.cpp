#include "OctTree.h"

const int MIN_SIZE = 1;

bool BoundingBox::contains(const Point3D& p) const {
    return (p.x >= min.vec_end.x) && (p.y >= min.vec_end.y) && (p.z >= min.vec_end.z) &&
           (p.x <= max.vec_end.x) && (p.y <= max.vec_end.y) && (p.z <= max.vec_end.z);
}

bool BoundingBox::contains(const Triangle3D& tri) const {
    return contains(tri.v0) && contains(tri.v1) && contains(tri.v2);
}

OctTree OctTree::CreateNode(const BoundingBox& region, const std::list<Triangle3D>& objList) {
	OctTree ret = OctTree(region, objList);
	ret.parent = this;

	return ret;
}

void OctTree::BuildTree() {
    if (region_elems.size() <= 1)
		return;

	Vector3D dimensions = region.max - region.min;

	//Проверяем, больше ли размеры параллелепипеда минимальных размеров
	if (dimensions.vec_end.x <= MIN_SIZE && dimensions.vec_end.y <= MIN_SIZE && dimensions.vec_end.z <= MIN_SIZE)
		return;
	

	Vector3D half = dimensions / 2.0f;
	Vector3D center = region.min + half;

	//Создаём подразделённые области для каждого октанта
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

	//Здесь будут содержаться все наши объекты, которые входят в каждый из соответствующих октантов.
	std::list<Triangle3D>* octList = new std::list<Triangle3D>[8];

	//В этом списке содержатся все объекты, перемещённые вниз по дереву. Их можно удалить из списка этого объекта.
	std::list<Triangle3D> delist;

    std::list<Triangle3D>::iterator it = region_elems.begin();

    while(it != region_elems.end()) {
        Triangle3D obj = *it;
        if (!obj.isDegenerate()) {
			for (int a = 0; a < 8; a++) {
				if (octant[a].contains(obj)) {
					octList[a].push_back(obj);
                    region_elems.erase(it);
					break;
				}
			}
		}
    }

	//Создаём дочерние узлы, в которых находятся элементы, содержащиеся в ограничивающей области
	for (int a = 0; a < 8; a++)
	{
		if (octList[a].size() != 0)
		{
			childNodes[a] = CreateNode(octant[a], octList[a]);
			childNodes[a].BuildTree();
		}
	}
}

size_t OctTree::getTreeIntersectNum() const {
    size_t count = 0;
    for (auto it1 = region_elems.begin(); it1 != region_elems.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != region_elems.end(); ++it2) {
            //count += (*it1).intersectWith(*it2);
        }
    }

    return count;
}

size_t OctTree::getAllTreeIntersectNum() const {

}