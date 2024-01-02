# Install script for directory: /home/benjamin/ros2_ws/src/visualization

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/benjamin/ros2_ws/src/visualization/install/visualization")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visualization" TYPE EXECUTABLE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/prueba")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba"
         OLD_RPATH "/home/benjamin/ws_moveit/install/moveit_core/lib:/home/benjamin/ros2_humble/install/rclcpp_lifecycle/lib:/home/benjamin/ros2_humble/install/rcl_lifecycle/lib:/home/benjamin/ros2_humble/install/lifecycle_msgs/lib:/home/benjamin/ros2_humble/install/rviz_default_plugins/lib:/home/benjamin/ros2_humble/install/rviz_common/lib:/home/benjamin/ros2_humble/install/rviz_rendering/lib:/home/benjamin/ros2_humble/install/resource_retriever/lib:/home/benjamin/ros2_humble/install/tf2_ros/lib:/home/benjamin/ros2_humble/install/urdf/lib:/home/benjamin/ros2_humble/install/image_transport/lib:/home/benjamin/ros2_humble/install/laser_geometry/lib:/home/benjamin/ros2_humble/install/map_msgs/lib:/home/benjamin/ros2_humble/install/nav_msgs/lib:/home/benjamin/ros2_humble/install/message_filters/lib:/home/benjamin/ros2_humble/install/rclcpp_action/lib:/home/benjamin/ros2_humble/install/rcl_action/lib:/home/benjamin/ros2_humble/install/tf2_msgs/lib:/home/benjamin/ros2_humble/install/action_msgs/lib:/home/benjamin/ros2_humble/install/unique_identifier_msgs/lib:/home/benjamin/ros2_humble/install/rclcpp_components/lib:/home/benjamin/ros2_humble/install/class_loader/lib:/home/benjamin/ros2_humble/install/composition_interfaces/lib:/home/benjamin/ros2_humble/install/shape_msgs/lib:/home/benjamin/ros2_humble/install/trajectory_msgs/lib:/home/benjamin/ros2_humble/install/interactive_markers/lib:/home/benjamin/ros2_humble/install/rclcpp/lib:/home/benjamin/ros2_humble/install/libstatistics_collector/lib:/home/benjamin/ros2_humble/install/rcl/lib:/home/benjamin/ros2_humble/install/rmw_implementation/lib:/home/benjamin/ros2_humble/install/ament_index_cpp/lib:/home/benjamin/ros2_humble/install/rcl_logging_spdlog/lib:/home/benjamin/ros2_humble/install/rcl_logging_interface/lib:/home/benjamin/ros2_humble/install/rcl_interfaces/lib:/home/benjamin/ros2_humble/install/rcl_yaml_param_parser/lib:/home/benjamin/ros2_humble/install/libyaml_vendor/lib:/home/benjamin/ros2_humble/install/rosgraph_msgs/lib:/home/benjamin/ros2_humble/install/statistics_msgs/lib:/home/benjamin/ros2_humble/install/tracetools/lib:/home/benjamin/ros2_humble/install/tf2/lib:/home/benjamin/ros2_humble/install/visualization_msgs/lib:/home/benjamin/ros2_humble/install/sensor_msgs/lib:/home/benjamin/ros2_humble/install/geometry_msgs/lib:/home/benjamin/ros2_humble/install/std_msgs/lib:/home/benjamin/ros2_humble/install/builtin_interfaces/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_fastrtps_c/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_fastrtps_cpp/lib:/home/benjamin/ros2_humble/install/fastcdr/lib:/home/benjamin/ros2_humble/install/rmw/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_introspection_cpp/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_introspection_c/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_cpp/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_c/lib:/home/benjamin/ros2_humble/install/rcpputils/lib:/home/benjamin/ros2_humble/install/rosidl_runtime_c/lib:/home/benjamin/ros2_humble/install/rcutils/lib:/opt/ros/humble/lib:/home/benjamin/ros2_humble/install/kdl_parser/lib:/home/benjamin/ros2_humble/install/urdfdom/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/home/benjamin/ws_moveit/install/moveit_msgs/lib:/home/benjamin/ros2_humble/install/rviz_ogre_vendor/opt/rviz_ogre_vendor/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/prueba")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/visualization" TYPE EXECUTABLE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/sphere_publish_service")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service"
         OLD_RPATH "/home/benjamin/ws_moveit/install/moveit_core/lib:/home/benjamin/ros2_humble/install/rclcpp_lifecycle/lib:/home/benjamin/ros2_humble/install/rcl_lifecycle/lib:/home/benjamin/ros2_humble/install/lifecycle_msgs/lib:/home/benjamin/ros2_humble/install/rviz_default_plugins/lib:/home/benjamin/ros2_humble/install/rviz_common/lib:/home/benjamin/ros2_humble/install/rviz_rendering/lib:/home/benjamin/ros2_humble/install/resource_retriever/lib:/home/benjamin/ros2_humble/install/tf2_ros/lib:/home/benjamin/ros2_humble/install/urdf/lib:/home/benjamin/ros2_humble/install/image_transport/lib:/home/benjamin/ros2_humble/install/laser_geometry/lib:/home/benjamin/ros2_humble/install/map_msgs/lib:/home/benjamin/ros2_humble/install/nav_msgs/lib:/home/benjamin/ros2_humble/install/message_filters/lib:/home/benjamin/ros2_humble/install/rclcpp_action/lib:/home/benjamin/ros2_humble/install/rcl_action/lib:/home/benjamin/ros2_humble/install/tf2_msgs/lib:/home/benjamin/ros2_humble/install/action_msgs/lib:/home/benjamin/ros2_humble/install/unique_identifier_msgs/lib:/home/benjamin/ros2_humble/install/rclcpp_components/lib:/home/benjamin/ros2_humble/install/class_loader/lib:/home/benjamin/ros2_humble/install/composition_interfaces/lib:/home/benjamin/ros2_humble/install/shape_msgs/lib:/home/benjamin/ros2_humble/install/trajectory_msgs/lib:/home/benjamin/ros2_humble/install/interactive_markers/lib:/home/benjamin/ros2_humble/install/rclcpp/lib:/home/benjamin/ros2_humble/install/libstatistics_collector/lib:/home/benjamin/ros2_humble/install/rcl/lib:/home/benjamin/ros2_humble/install/rmw_implementation/lib:/home/benjamin/ros2_humble/install/ament_index_cpp/lib:/home/benjamin/ros2_humble/install/rcl_logging_spdlog/lib:/home/benjamin/ros2_humble/install/rcl_logging_interface/lib:/home/benjamin/ros2_humble/install/rcl_interfaces/lib:/home/benjamin/ros2_humble/install/rcl_yaml_param_parser/lib:/home/benjamin/ros2_humble/install/libyaml_vendor/lib:/home/benjamin/ros2_humble/install/rosgraph_msgs/lib:/home/benjamin/ros2_humble/install/statistics_msgs/lib:/home/benjamin/ros2_humble/install/tracetools/lib:/home/benjamin/ros2_humble/install/tf2/lib:/home/benjamin/ros2_humble/install/visualization_msgs/lib:/home/benjamin/ros2_humble/install/sensor_msgs/lib:/home/benjamin/ros2_humble/install/geometry_msgs/lib:/home/benjamin/ros2_humble/install/std_msgs/lib:/home/benjamin/ros2_humble/install/builtin_interfaces/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_fastrtps_c/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_fastrtps_cpp/lib:/home/benjamin/ros2_humble/install/fastcdr/lib:/home/benjamin/ros2_humble/install/rmw/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_introspection_cpp/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_introspection_c/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_cpp/lib:/home/benjamin/ros2_humble/install/rosidl_typesupport_c/lib:/home/benjamin/ros2_humble/install/rcpputils/lib:/home/benjamin/ros2_humble/install/rosidl_runtime_c/lib:/home/benjamin/ros2_humble/install/rcutils/lib:/opt/ros/humble/lib:/home/benjamin/ros2_humble/install/kdl_parser/lib:/home/benjamin/ros2_humble/install/urdfdom/lib:/opt/ros/humble/lib/x86_64-linux-gnu:/home/benjamin/ws_moveit/install/moveit_msgs/lib:/home/benjamin/ros2_humble/install/rviz_ogre_vendor/opt/rviz_ogre_vendor/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/visualization/sphere_publish_service")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/visualization")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/visualization")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization/environment" TYPE FILE FILES "/home/benjamin/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization/environment" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization/environment" TYPE FILE FILES "/home/benjamin/ros2_humble/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization/environment" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_index/share/ament_index/resource_index/packages/visualization")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization/cmake" TYPE FILE FILES
    "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_core/visualizationConfig.cmake"
    "/home/benjamin/ros2_ws/src/visualization/build/visualization/ament_cmake_core/visualizationConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/visualization" TYPE FILE FILES "/home/benjamin/ros2_ws/src/visualization/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/benjamin/ros2_ws/src/visualization/build/visualization/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
