

# Gradient-Based Trajectory Optimizer

高飞　IROS2017年的论文

Gradient-Based Online Safe Trajectory Generation　for Quadrotor Flight in Complex Environments

- Gradient-Based Trajectory Optimizer只是motionPlanning的后端，对生成的轨迹点做出优化
- 系统所对应　mapping module, https://github.com/HKUST-Aerial-Robotics/VI-MEAN
- mapping module维护的是一个a global hashed voxel map
- planning的时候维护的是一个a constant local map, just by filtering the voxels and keeping only voxels in a local range

>  receive the voxels published by VI-MEAN and insert them into a local/global map.

>  grad_traj_optimization just provides a planning core, you have to write a map maintainer/interface for engineering usage

## install

依赖的库都放在　third_party or lib中
直接catkin_make 安装


## test_demo

**rviz 可视化界面**
roslaunch grad_traj_optimization traj_rviz.launch


<!-- 随机设定了一组waypoints  和障碍物地图，　利用轨迹优化产生优化后轨迹 -->
roslaunch grad_traj_optimization random.launch

<!-- 利用 2D Navi goal, click 一组点，　然后利用轨迹优化产生优化后的轨迹-->
roslaunch grad_traj_optimization click.launch

<!--  -->
roslaunch grad_traj_optimization text_input.launch