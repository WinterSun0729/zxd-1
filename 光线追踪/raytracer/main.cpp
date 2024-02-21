#include <chrono>

#include "lib/Renderer.hpp"
#include "lib/Scene.hpp"
#include "lib/Mesh.hpp"

int main(int argc, char** argv) {
    Scene scene(1024, 1024, {278.0f, 273.0f, -800.0f}, 40.0f);
    constexpr unsigned int spp = 2;
    constexpr unsigned int total_thread_count = 8;

    const auto light_emission = Vector3f(12.0f * Vector3f(0.747f + 0.058f, 0.747f + 0.258f, 0.747f)
                                     + 23.4f * Vector3f(0.740f + 0.287f, 0.740f + 0.160f, 0.740f)
                                     + 27.6f * Vector3f(0.737f + 0.642f, 0.737f + 0.159f, 0.737f));
    const auto light_mat_ptr = std::make_shared<Diffuse>(Vector3f(0.65f), light_emission);

    const auto red_diffuse_mat_ptr = std::make_shared<Diffuse>(Vector3f(0.63f, 0.065f, 0.05f));
    const auto green_diffuse_mat_ptr = std::make_shared<Diffuse>(Vector3f(0.14f, 0.45f, 0.091f));
    const auto white_diffuse_mat_ptr = std::make_shared<Diffuse>(Vector3f(0.725f, 0.71f, 0.68f));

    const auto marble_mat_ptr = std::make_shared<MetalRough>(Vector3f(0.875f, 0.83f, 0.82f), 0.001f, 0.3f);
    const auto silver_mat_ptr = std::make_shared<MetalRough>(Vector3f(0.95f, 0.93f, 0.88f), 0.01f, 1.0f);

    const auto glass_mat_ptr = std::make_shared<FrostedGlass>(0.1f, 1.5f);
    Vector3f rotation_axis(1.0f, 0.0f, 0.0f);
    Vector3f oringinal_transition(0.0f, 0.0f, 0.0f);

    const auto ceil_floor_back_wall_triangles = load_triangles_from_model_file("../models/cornellbox/floor.obj", marble_mat_ptr,1,oringinal_transition,rotation_axis,0);
    const auto left_wall_triangles = load_triangles_from_model_file("../models/cornellbox/left.obj", red_diffuse_mat_ptr,1,oringinal_transition,rotation_axis,0);
    const auto right_wall_triangles = load_triangles_from_model_file("../models/cornellbox/right.obj", green_diffuse_mat_ptr,1,oringinal_transition,rotation_axis,0);
    const auto tall_box_triangles = load_triangles_from_model_file("../models/cornellbox/tallbox.obj", marble_mat_ptr,1,oringinal_transition,Vector3f(0.0f, 1.0f, 0.0f) , 0);
    const auto ceiling_lamp_triangles = load_triangles_from_model_file("../models/cornellbox/light.obj", light_mat_ptr, 1,Vector3f(0.0f, 0.0f, -60.0f),rotation_axis,0);
    const auto logo = load_triangles_from_model_file("../models/logo.obj", silver_mat_ptr, 1.0, Vector3f(50.0f, 0.0f, -150.0f), rotation_axis, 0.0);
    const auto lib = load_triangles_from_model_file("../models/lib.obj", white_diffuse_mat_ptr, 1.3, Vector3f(-170.0f, 0.0f, 50.0f), rotation_axis, 0.0);

    const auto ceil_floor_back_wall_ptr = std::make_shared<TriangleMesh>(ceil_floor_back_wall_triangles, BVH_tree::SplitMethod::NAIVE);
    const auto left_wall_ptr = std::make_shared<TriangleMesh>(left_wall_triangles, BVH_tree::SplitMethod::NAIVE);
    const auto right_wall_ptr = std::make_shared<TriangleMesh>(right_wall_triangles, BVH_tree::SplitMethod::NAIVE);
    const auto tall_box_ptr = std::make_shared<TriangleMesh>(tall_box_triangles, BVH_tree::SplitMethod::NAIVE);
    const auto ceiling_lamp_ptr = std::make_shared<TriangleMesh>(ceiling_lamp_triangles, BVH_tree::SplitMethod::NAIVE);
    const auto logo_ptr = std::make_shared<TriangleMesh>(logo, BVH_tree::SplitMethod::NAIVE);
    const auto lib_ptr = std::make_shared<TriangleMesh>(lib, BVH_tree::SplitMethod::NAIVE);

    const auto glass_ball_ptr = std::make_shared<Sphere>(Vector3f(380.0f, 380.0f, 150.0f), 70.0f, glass_mat_ptr);
    const auto glass_ball_ptr2 = std::make_shared<Sphere>(Vector3f(300.0f, 100.0f, 200.0f), 20.0f, glass_mat_ptr);

    scene.add_object(ceil_floor_back_wall_ptr);
    scene.add_object(left_wall_ptr);
    scene.add_object(right_wall_ptr);
    scene.add_object(ceiling_lamp_ptr);
    scene.add_object(glass_ball_ptr);
    scene.add_object(glass_ball_ptr2);
    scene.add_object(logo_ptr);
    scene.add_object(lib_ptr);
    scene.add_light(std::make_shared<Light>(Vector3f{-20.0f, 70.0f, 20.0f}, Vector3f{1.0f, 1.0f, 1.0f}));
    scene.add_light(std::make_shared<Light>(Vector3f{20.0f, 70.0f, 20.0f}, Vector3f{1.0f, 1.0f, 1.0f}));

    scene.build_BVH();

    Renderer r;
    const auto start = std::chrono::system_clock::now();
    r.render(scene, spp, total_thread_count);
    const auto stop = std::chrono::system_clock::now();

    std::cout << "Complete!\n";
    return 0;
}