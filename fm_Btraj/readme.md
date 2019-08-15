
# Btraj 　front end + backend 的轨迹生成器

高飞2018ICRA文章
**Online Safe Trajectory Generation For Quadrotors　Using Fast Marching Method and Bernstein Basis Polynomial**


 前端的轨迹点生成：有两种方法：
    - Fast Marching*(FM*) on a velocity field
    - A* on a pure grid map

 A flight corridor consists of cubes are generated based on the path

- 后端的轨迹优化利用贝塞尔曲线　
     utilize properties of Bezier curve to confine the piecewise Bezier curves entirely within the corridor and dynamical limits



## test demo

<!-- 启动rviz 仿真环境，利用3D Nav Goal-->
roslaunch bezier_planer simulation.launch
