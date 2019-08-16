
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

启动rviz 仿真环境，利用3D Nav Goal
! 按住左键选择XY位置，　按住右键，拖动鼠标确定Ｚ轴高度
roslaunch bezier_planer simulation.launch


## 先梳理　输入/输出 　入口函数

1. init_pose 指定无人机启动时的位置
2. rviz中指定　/goal目标点
      - 发布一个３d pose /goal
3. odom_generator  仿真模型　收到什么pose命令，就发布为下一时刻的odom
      - 订阅轨迹服务器发布的 /position_cmd
      - 发布　/fake_odom
      
4. [waypoint_generator]节点，订阅/goal & /odom  输出一个waypoints
   不同的mode输出不同，比如circle eight 等等，　如果是manual，那么就是只有gola一个的位姿，圆和八字会多一些
      - 订阅 /goal  /odom
      - 根据不同的模型，发布 /waypoints
   
5. [random_forest_sensing]节点　在三维空间中随机产生障碍物树
      - 订阅 /odom
      - 发布　障碍物点云 /random_forest_sensing/random_forest


**现在系统有了对自己位姿的状态估计，也有了周围环境的障碍物地图，可以进行核心工作轨迹生成和轨迹优化了**

1. [b_traj_node]节点
   ａ. 订阅
      - 自身位姿/odom 
      - /waypoints目标点　
      - 以及障碍物map　//random_forest_sensing/random_forest
   b. 发布　
      - check_trajectory
      - trajectory_vis
      - trajectory
      - grid_path_vis
      - path_vis
      - expanded_node_vis
      - corridor_vis
      - vis_map_local


      a.1 订阅障碍物点云地图：
        - 维护两个　pointCloud　主要是为了可视化，cloud_local//cloud_inflation
            vis_map_inflate　vis_map_local两个点云图
        - 维护两个　CollisionMapGrid,为了运算，collision_map，　collision_map_local

        然后执行 checkExecTraj()  trajPlanning()

      a.2 订阅无人机的odom 　注意　frame_id=uav
        - 更新　start_pt vel acc
        - 发布tf_tree  "quadrotor" --> "world"

      a.3 订阅　目标点
        - 更新　_end_pt
        - trajPlanning();

      b.1 checkExecTraj()
            - traj_pt = getPosFromBezier( _bezier_coeff, t/_seg_time(i), i );
            - checkCoordObs(traj_pt)
            - 然后发布check_trajectory，stop_trajectory两个轨迹