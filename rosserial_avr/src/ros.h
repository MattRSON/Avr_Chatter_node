#ifndef _ROS_H_
#define _ROS_H_

#include "ros/node_handle.h"
#include "Atmega32Hardware.h"

namespace ros
{
    typedef ros::NodeHandle_<Atmega32AHardware> NodeHandle;
}

#endif