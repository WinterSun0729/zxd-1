cmake_minimum_required (VERSION 3.10)

project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp lib/Vector.hpp Vector.cpp lib/Object.hpp Object.cpp  lib/Mesh.hpp Mesh.cpp lib/Scene.hpp Scene.cpp lib/BVH.hpp BVH.cpp lib/BoundingBox.hpp BoundingBox.cpp lib/Ray.hpp Ray.cpp lib/Material.hpp Material.cpp lib/Intersection.hpp lib/stb_image_write.h lib/Renderer.hpp Renderer.cpp lib/OBJ_Loader.h)