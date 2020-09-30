#配置环境
## 安装Ubuntu
建议使用 18.04，虚拟机或双系统
## 安装ros
安装与ubuntu对应版本ros melodic，安装教程请前往[ros wiki官网](http://wiki.ros.org/melodic/Installation/Ubuntu) 按教程安装

# 代码内容
/src: 机器人模型与示例程序，拷贝到ros工作空间文件夹下与原src文件夹合并  
Football_field.pdf 球场坐标文件
## 仿真环境文件夹
/src/gazebo_simulator: 仿真环境
## 示例代码目录结构
```
|-- robot_ctrl
            |-- CMakeLists.txt  		编译Cmake文件
            |-- package.xml		 	ros配置文件
            |-- config		
            |   |-- config.yaml	 	 参数文件
            |-- include
            |   |-- robot_ctrl
            |       |-- robot_ctrl.h	 cpp头文件
            |-- launch
            |   |-- sim_game.launch	  cpp程序launch文件
            |   |-- sim_game_py.launch   python程序launch文件
            |-- scripts			
            |   |-- ctrl_py.py			python程序
            |-- src
                |-- robot_ctrl.cpp		cpp源文件
```


# 代码编译

## Install ROS
http://wiki.ros.org/melodic/Installation/Ubuntu
## Source develop env
```
$ echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```

## 创建代码工作空间
```
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_make
```

## Install Gazebo
http://gazebosim.org/tutorials?tut=install_ubuntu
```
$ sudo apt-get install gazebo9
```

## Install dependênce to Gazebo
```
$ sudo apt-get install libgazebo9-dev
```

## install build-essential & git
```
$ sudo apt-get install build-essential git 
$ sudo apt-get install ros-melodic-mavros
```

## clone code
```
$ git clone https://github.com/BUAA503Control/Training2020_new
```
## clone code to ros workspace
```
$ cp -r Training2020_new/src/. ~/catkin_ws/src/
```
## enable operation authority
```
$ chmod a+x ~/catkin_ws/src/gazebo_simulator/scripts/robot_up.sh 
$ chmod a+x ~/catkin_ws/src/robot_ctrl/scripts/ctrl_py.py 

```

## compile 
```
$ cd ~/cakin_ws/   
$ catkin_make (or  catkin build)
```
# 代码运行
## launch simulation
```
$ roslaunch gazebo_simulator gazebo_simulator.launch 
```

## launch strategy code
1. for c/c++ users
```
$ roslaunch robot_ctrl sim_game.launch 
```
2. for python users
```
$ roslaunch robot_ctrl sim_game_py.launch
```

运行成功效果：机器人在场内转圈圈

