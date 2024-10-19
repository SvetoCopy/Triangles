#include "Intervals.h"
#include "Plane.h"

// TODO: write comment about formule
Interval::Interval(const Line3D& line, const Triangle3D& triang0, const Triangle3D& triang1) {
    float v_pr_0_0 = line.dist & Vector3D(triang0.v0 - line.p);
    float v_pr_0_1 = line.dist & Vector3D(triang0.v1 - line.p);
    float v_pr_0_2 = line.dist & Vector3D(triang0.v2 - line.p);

    float v_pr_1_0 = line.dist & Vector3D(triang1.v0 - line.p);
    float v_pr_1_1 = line.dist & Vector3D(triang1.v1 - line.p);
    float v_pr_1_2 = line.dist & Vector3D(triang1.v2 - line.p);

    Plane triang0_plane {triang0};
    Plane triang1_plane {triang1};

    float dist_v_0_0 = triang1_plane.distanceFromPoint(triang0.v0);
    float dist_v_0_1 = triang1_plane.distanceFromPoint(triang0.v1);
    float dist_v_0_2 = triang1_plane.distanceFromPoint(triang0.v2);

    float dist_v_1_0 = triang0_plane.distanceFromPoint(triang1.v0);
    float dist_v_1_1 = triang0_plane.distanceFromPoint(triang1.v1);
    float dist_v_1_2 = triang0_plane.distanceFromPoint(triang1.v2);

    t0_0 = v_pr_0_0 + ((v_pr_0_2 - v_pr_0_0) * dist_v_0_0) / (dist_v_0_0 - dist_v_0_2);
    t0_1 = v_pr_0_1 + ((v_pr_0_2 - v_pr_0_1) * dist_v_0_1) / (dist_v_0_1 - dist_v_0_2);

    t1_0 = v_pr_1_0 + ((v_pr_1_2 - v_pr_1_0) * dist_v_1_0) / (dist_v_1_0 - dist_v_1_2);
    t1_1 = v_pr_0_1 + ((v_pr_1_2 - v_pr_1_1) * dist_v_1_1) / (dist_v_1_1 - dist_v_1_2);
    //t1_0 = v_pr_1_0 + (v_pr_1_2 - v_pr_1_0) * (dist_v_1_0 / (dist_v_1_0 - dist_v_1_2));
    //t1_1 = v_pr_0_1 + (v_pr_1_2 - v_pr_1_1) * (dist_v_1_1 / (dist_v_1_1 - dist_v_1_2));
}