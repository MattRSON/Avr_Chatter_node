#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "ros.h"
#include "std_msgs/String.h"

// Include C headers (ie, non C++ headers) in this block
extern "C"
{
  #include <avr/io.h>
  #include <util/delay.h>
}

// Needed for AVR to use virtual functions
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

char flag = 0;
int main()
{
  uint32_t lasttime = 0UL;
  DDRC = 0xFF;
  // Initialize ROS
  nh.initNode();
  nh.advertise(chatter);

  while(1)
  {
    // Send the message every second
    if(avr_time_now() - lasttime > 1000)
    {
      str_msg.data = hello;
      chatter.publish(&str_msg);
      if(flag == 1)
      {
        PORTC = 0xFF;
        flag = 2;
      }
      else
      {
        PORTC = 0x00;
        flag = 1;
      }
      lasttime = avr_time_now();
    }
    nh.spinOnce();
  }

  return 0;
}