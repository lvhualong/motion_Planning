#ifndef _DATA_TYPE_
#define _DATA_TYPE_

#include <stdio.h>
#include <ros/ros.h>
#include <ros/console.h>
#include <iostream>
#include <fstream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <vector>

#define inf 1>>30

struct Cube;
struct GridNode;
typedef GridNode* GridNodePtr;

struct Cube
{     
      //Eigen::Vector3d p1, p2, p3, p4, p5, p6, p7, p8;   // the 8 vertex of a cube 
      Eigen::MatrixXd vertex;
      Eigen::Vector3d center; // the center of the cube
      bool valid;    // indicates whether this cube should be deleted

      double t; // time allocated to this cube
      std::vector< std::pair<double, double> > box;
/*
           P3------------P2 
           /|           /|              ^
          / |          / |              | z
        P0--|---------P1 |              |
         |  P7--------|--p6             |
         | /          | /               /--------> y
         |/           |/               /  
        P4------------P5              / x
*/                                                                                 

      // create a cube using 8 vertex and the center point
      Cube( Eigen::MatrixXd vertex_, Eigen::Vector3d center_)
      {
            vertex = vertex_;
            center = center_;
            valid = true;
            t = 0.0;
            box.resize(3);
      }

      // create a inscribe cube of a ball using the center point and the radius of the ball
      // 根据分辨率每个顶点要往外扩半个分辨率
      // M 8*3 每行一个顶点
      void setVertex( Eigen::MatrixXd vertex_, double resolution_)
      {     
            vertex = vertex_;
            //ｙ方向
            vertex(0,1) -= resolution_ / 2.0;
            vertex(3,1) -= resolution_ / 2.0;
            vertex(4,1) -= resolution_ / 2.0;
            vertex(7,1) -= resolution_ / 2.0;

            vertex(1,1) += resolution_ / 2.0;
            vertex(2,1) += resolution_ / 2.0;
            vertex(5,1) += resolution_ / 2.0;
            vertex(6,1) += resolution_ / 2.0;

            //x 方向
            vertex(0,0) += resolution_ / 2.0;
            vertex(1,0) += resolution_ / 2.0;
            vertex(4,0) += resolution_ / 2.0;
            vertex(5,0) += resolution_ / 2.0;

            vertex(2,0) -= resolution_ / 2.0;
            vertex(3,0) -= resolution_ / 2.0;
            vertex(6,0) -= resolution_ / 2.0;
            vertex(7,0) -= resolution_ / 2.0;
            //z方向
            vertex(0,2) += resolution_ / 2.0;
            vertex(1,2) += resolution_ / 2.0;
            vertex(2,2) += resolution_ / 2.0;
            vertex(3,2) += resolution_ / 2.0;

            vertex(4,2) -= resolution_ / 2.0;
            vertex(5,2) -= resolution_ / 2.0;
            vertex(6,2) -= resolution_ / 2.0;
            vertex(7,2) -= resolution_ / 2.0;
            
            setBox();
      }
      
      //　cube的三条边的长度差
      void setBox()
      {
            box.clear();
            box.resize(3);
            box[0] = std::make_pair( vertex(3, 0), vertex(0, 0) );//x
            box[1] = std::make_pair( vertex(0, 1), vertex(1, 1) );//y
            box[2] = std::make_pair( vertex(4, 2), vertex(1, 2) );//z
      }

      void printBox()
      {
            std::cout<<"center of the cube: \n"<<center<<std::endl;
            std::cout<<"vertex of the cube: \n"<<vertex<<std::endl;
      }

      Cube()
      {  
         center = Eigen::VectorXd::Zero(3);
         vertex = Eigen::MatrixXd::Zero(8, 3);

         valid = true;
         t = 0.0;
         box.resize(3);
      }

      ~Cube(){}
};


struct GridNode
{     
   int id;        // 1--> open set, -1 --> closed set
   Eigen::Vector3d coord;
   Eigen::Vector3i index;
   
   double gScore, fScore;
   GridNodePtr cameFrom;
   std::multimap<double, GridNodePtr>::iterator nodeMapIt;
   double occupancy; 

   std::vector<GridNodePtr> hisNodeList; // use a list to record nodes in its history

   GridNode(Eigen::Vector3i _index)
   {  
      id = 0;
      index = _index;
      
      gScore = inf;
      fScore = inf;
      cameFrom = NULL;
   }

   GridNode(Eigen::Vector3i _index, Eigen::Vector3d _coord)
   {  
      id = 0;
      index = _index;
      coord = _coord;

      gScore = inf;
      fScore = inf;
      cameFrom = NULL;
   }

   GridNode(){};
   
   ~GridNode(){};
};

#endif