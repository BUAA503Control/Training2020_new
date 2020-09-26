#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>    
#include <geometry_msgs/TwistStamped.h>    
#include "geometry_msgs/Pose.h"

#include <gazebo_msgs/ModelStates.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

    
#include <nav_msgs/Odometry.h>    
#include "tf/LinearMath/Matrix3x3.h"    
#include "geometry_msgs/Quaternion.h" 
#include "geometry_msgs/Point.h"

#define MAX_LIN_VEL 1.2
#define MAX_ANG_VEL 10.0 
#define PI 3.14159265
   
class Robot
{
private:

    int num;
    int index_ball;
    int index_robot;

    std::string ball_name;

    ros::NodeHandle nh;
    ros::Subscriber sub_model_pos;
    ros::Publisher pub_robot_vel;

    // model state
    
    geometry_msgs::Point position_ball;
    geometry_msgs::Point position_robot;
    double orientation_robot;
    
    
public:
    Robot();
    bool DONE;
    void ModelStateCallback(const gazebo_msgs::ModelStates::ConstPtr &cur_state);
    void RobotTwistPub(double velocity,double angular);
    void Robot2Ball();
};
