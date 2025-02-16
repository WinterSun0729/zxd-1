#include "lib/Mesh.hpp"

#include <cassert>
#include <array>

// 计算两个向量的点积
float dot(const Vector3f& a, const Vector3f& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 计算两个向量的叉积
Vector3f cross(const Vector3f& a, const Vector3f& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// 辅助函数，绕轴旋转向量
Vector3f rotate_vector_around_axis(const Vector3f& vector, const Vector3f& axis, float angle) {
    float cos_theta = std::cos(angle);
    float sin_theta = std::sin(angle);
    return cos_theta * vector + (1 - cos_theta) * dot(vector, axis) * axis + sin_theta * cross(axis, vector);
}

std::vector<std::shared_ptr<Triangle>> load_triangles_from_model_file(const std::string& file_name,
                                                                       const std::shared_ptr<Material>& mat_ptr,
                                                                       float scale_frac,
                                                                       const Vector3f& translation,
                                                                       const Vector3f& rotation_axis,
                                                                       float rotation_angle) {
    objl::Loader loader;
    loader.LoadFile(file_name);

    const objl::Mesh mesh = loader.LoadedMeshes[0];

    std::vector<std::shared_ptr<Triangle>> triangle_ptrs;

    const auto vertex_num = mesh.Vertices.size();
    for (size_t i = 0; i < vertex_num; i += 3) {
        std::array<Vector3f, 3> triangle_vertices;
        for (size_t j = 0; j < 3; ++j) {
            const auto idx = i + j;
            // 应用缩放、平移和旋转
            Vector3f scaled_vertex = {
                mesh.Vertices[idx].Position.X * scale_frac,
                mesh.Vertices[idx].Position.Y * scale_frac,
                mesh.Vertices[idx].Position.Z * scale_frac
            };
            Vector3f rotated_vertex = rotate_vector_around_axis(scaled_vertex, rotation_axis, rotation_angle);
            Vector3f translated_vertex = rotated_vertex + translation;

            triangle_vertices[j] = translated_vertex;
        }

        triangle_ptrs.push_back(std::make_shared<Triangle>(triangle_vertices[0],
                                triangle_vertices[1],
                                triangle_vertices[2],
                                mat_ptr));
    }

    return triangle_ptrs;
}

TriangleMesh::TriangleMesh(const std::vector<std::shared_ptr<Triangle>>& triangle_ptr_list,
                            BVH_tree::SplitMethod split_method)
     : _triangle_ptrs(triangle_ptr_list),
       _bvh_tree(transform_to_object_vector<Triangle>(triangle_ptr_list), split_method),
       _emitting(false) {
    for (const auto& tri_ptr : _triangle_ptrs) {
        if (tri_ptr->emitting()) {
            _emitting = true;
            break;
        }
    }
}