#!/usr/bin/env python
# -*- coding: utf-8 -*-
import rospy
import sys
import math
from std_msgs.msg import String
from geometry_msgs.msg import Point, Quaternion,Twist,Pose
from gazebo_msgs.msg import ModelStates
from tf.transformations import quaternion_from_euler,euler_from_quaternion

# max vel: 1.0 m/s
# max ang:2.8 rad/s

# rate = rospy.Rate(200)
rate = 30. # twist pub rate

index_robot = -1
index_ball = -1

pub_model_twist = rospy.Publisher("/cmd_vel",Twist, queue_size=10)

MAX_LIN_VEL = 1.0
MAX_ANG_VEL = 2.8  
PI = 3.14159265
position_ball = Point()
position_robot = Point()
yaw_robot = -5.0

def cb_model_pose(model_state):
    global index_ball, index_robot,position_ball,position_robot,yaw_robot
    model_names = model_state.name
    if(index_ball<0 or index_robot<0):
        rospy.loginfo("update index")
        for i in range(len(model_names)):
            if(model_names[i] == para_ball_name):
                index_ball = i
            elif (model_names[i] == "home1"):
                index_robot = i

    position_ball = model_state.pose[index_ball].position
    position_robot = model_state.pose[index_robot].position
    quat_robot = model_state.pose[index_robot].orientation
    (_,_,yaw_robot) = euler_from_quaternion([quat_robot.x, quat_robot.y, quat_robot.z, quat_robot.w])
    
    #rospy.loginfo("orientation: {0:.3f}".format(yaw_robot))


def cmd_vel_pub(lin_x,ang_z):
    global pub_model_twist
    if(lin_x > MAX_LIN_VEL):
         lin_x =  MAX_LIN_VEL
    if(ang_z>MAX_ANG_VEL):
         ang_z = MAX_ANG_VEL
    vel = Twist()
    vel.linear.x = lin_x
    vel.angular.z = ang_z
    pub_model_twist.publish(vel)

def robot2ball(event):
    velocity = 1.0
    angular = 1.0
    ball_x = position_ball.x
    ball_y = position_ball.y
    robot_x = position_robot.x
    robot_y = position_robot.y
    robot_rot = yaw_robot
    # TODO: write your code here
    
    
    #rospy.loginfo("ball_x: {0:.3f}".format(ball_x))
    # set the control linear velocity in x axis and yaw angular velocity
    cmd_vel_pub(velocity,angular)

if __name__ == "__main__":
    rospy.init_node("ctrl_py",anonymous=True)
    sub_model_state = rospy.Subscriber("/gazebo/model_states",ModelStates,cb_model_pose)
    para_ball_name = rospy.get_param("ball_name",default="ball")
    rospy.loginfo("ball_name"+str(para_ball_name))

    cmdTimer = rospy.Timer(rospy.Duration(1/rate),robot2ball)

    rospy.spin()

