#include "robot_ctrl/robot_ctrl.h"
#include "geometry_msgs/Quaternion.h" 
#include "geometry_msgs/Point.h" 
#include "tf/transform_datatypes.h"//转换函数头文件 
#include <cmath>

// max vel: 1.2m/s
// max ang:10.0rad/s

Robot::Robot()
{  
    index_ball = index_robot = -1;
    std::string topic_model_state = "/gazebo/model_states";

    nh.param("ball_name",ball_name,std::string("ball0"));
   
    ROS_INFO("ball_name: %s",ball_name.c_str());

    sub_model_pos = nh.subscribe(topic_model_state, 10, &Robot::ModelStateCallback, this);

    pub_robot_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
}

void Robot::ModelStateCallback(const gazebo_msgs::ModelStates::ConstPtr &cur_state)
{
    // int box_index = -1;
    std::vector<std::string> model_names = cur_state->name;
    if(index_ball<0||index_robot<0)
    {
        ROS_INFO("update_index");
        for(size_t i = 0; i < model_names.size(); i++)
        {
            if(model_names[i] == ball_name)
                index_ball = i;
            else if(model_names[i] == "home1")
                index_robot = i;
        }
    }

    geometry_msgs::Pose pose_ball;
    geometry_msgs::Pose pose_robot;
    geometry_msgs::Quaternion quat_robot;
    pose_ball = cur_state->pose[index_ball];
    pose_robot = cur_state->pose[index_robot];
    position_ball = pose_ball.position;
    position_robot = pose_robot.position;
    quat_robot = pose_robot.orientation;

    //ROS_INFO("bx: %.03f, by: %.03f",position_ball.x,position_ball.y);
    //ROS_INFO("rx: %.03f, ry: %.03f",position_robot.x,position_robot.y);

    // convert quat 2 yaw
    tf::Quaternion quat;
    tf::quaternionMsgToTF(quat_robot, quat);
 
    double roll, pitch, yaw;//定义存储r\p\y的容器
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
    orientation_robot = yaw;


    //ROS_INFO_STREAM("orientation:"  << yaw);
}

void Robot::RobotTwistPub(double velocity,double angular)
{
    if(velocity > MAX_LIN_VEL) velocity = MAX_LIN_VEL;
    if(angular > MAX_ANG_VEL) angular = MAX_ANG_VEL;
    //ROS_INFO("linear: %.03f, angular: %.03f",velocity,angular);
    geometry_msgs::Twist vel;
    vel.linear.x = velocity;
    vel.angular.z = angular;
    pub_robot_vel.publish(vel);
}

void Robot::Robot2Ball()
{
    double velocity = 1.;
    double angular = 2.;

    // ball pos and robot pos
    double ball_x = position_ball.x;
    double ball_y = position_ball.y;
    double robot_x = position_robot.x;
    double robot_y = position_robot.y;
    double robot_rot = orientation_robot;
    // Todo: write you code here
        



    RobotTwistPub(velocity,angular);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_ctrl");

    Robot t1;
    ros::Rate rate(30);

    while(ros::ok())
    {
        t1.Robot2Ball();
        ros::spinOnce();
        rate.sleep();
    }

    //ros::spin();
    return 0;
}
