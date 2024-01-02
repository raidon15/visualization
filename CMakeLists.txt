cmake_minimum_required(VERSION 3.8)
project(visualization)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rviz_common REQUIRED)
find_package(moveit_core REQUIRED)

find_package(eigen3_cmake_module REQUIRED)
find_package(eigen_stl_containers REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(rviz_visual_tools REQUIRED)
find_package(std_srvs REQUIRED)


add_executable(sphere_publish_service src/sphere_publish_service.cpp)
add_executable(prueba src/test.cpp)

ament_target_dependencies(sphere_publish_service 
  std_srvs
  rclcpp 
  geometry_msgs
  rviz_common
  moveit_core
  eigen3_cmake_module
  eigen_stl_containers
  Eigen3
  rviz_visual_tools)

ament_target_dependencies(prueba 
  rclcpp 
  geometry_msgs
  rviz_common
  moveit_core
  eigen3_cmake_module
  eigen_stl_containers
  Eigen3
  rviz_visual_tools
  )

install(TARGETS
  prueba
  sphere_publish_service
  DESTINATION lib/${PROJECT_NAME})
ament_package()
