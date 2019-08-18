# Fast-Planner

Robust and Efficient Quadrotor Trajectory Generation for Fast Autonomous Flight
这篇文章是前面一篇文章　Gradient-based Bspline trajectory　generator的升级版


主要体现在：
- the front-end kinodynamic path searching
- the back-end gradient-based Bspline trajectory optimization
- the postprocessing named as _iterative time adjustment_.



## install 

-nlopt优化库　cmake -DCMAKE_INSTALL_PREFIX=../install ..　安装在lib下的install 注意cmake引用时的位置


## test　demo


roslaunch plan_manage rviz.launch
roslaunch plan_manage simulation.launch

