#include <ros/ros.h>
#include <sound_play/sound_play.h>
#include <unistd.h>
#include <geometry_msgs/Point.h>

//important parameters
//describe the area in the middle
float x_side_half_postive = 0.8;
float x_side_half_negative = -0.8;
float y_side_half_postive = 0.8; //1.18;
float y_side_half_negative = -0.8; //-1.18;

//pointer to room_sound
sound_play::SoundClient *room_sound_pointer;

int previous_sound = 0;

void soundCallback(const geometry_msgs::Point::ConstPtr& msg)
{
  ROS_INFO("callback called");

  //reading msgs values
  float x_body = msg->x;
  float y_body = msg->y;
  float z_body = msg->z;
  ROS_INFO("X, Y, Z frame %f %f %f", x_body, y_body, z_body);

  //door sound 3
  //wall sound 2
  //innner sound 1

  if (x_body > x_side_half_postive || x_body < x_side_half_negative) {ROS_INFO("outside x");}
  if (y_body > y_side_half_postive || y_body < y_side_half_negative) {ROS_INFO("outside y");}

  if (    (x_body > x_side_half_postive || x_body < x_side_half_negative)
       || (y_body > y_side_half_postive || y_body < y_side_half_negative) ) {
    //check door steps first
    if ( x_body > 0.6 && y_body < -0.6){
      //if within play door sound (but where is the door) & stop others
      ROS_INFO("stop - playing door");
      room_sound_pointer->stopAll();
      room_sound_pointer->startWave("/home/tosh-sat/light_room_sounds/3_heart_beat.ogg");
      sleep(1);
      //previous_sound = 3;
    }
    else {
      ROS_INFO("should play wall sound & stop all other sounds");
          ROS_INFO("stop - playing wall");
          room_sound_pointer->stopAll();
          //room_sound_pointer->repeat("wall");
          room_sound_pointer->startWave("/home/tosh-sat/light_room_sounds/2_breathing.wav");
          sleep(4);
    }
  }
  else {
    //checking if in room center
//    if (    (x_body < 0.25 && x_body > -0.25)
//         || (y_body < 0.25 && y_body > -0.25) ) {
//      ROS_INFO("should play center sound & stop all other sounds");
//        ROS_INFO("stop -playing center");
//        room_sound_pointer->stopAll();
//        //room_sound_pointer->repeat("center");
//        room_sound_pointer->startWave("/home/tosh-sat/light_room_sounds/5_seconds_middle_no_fade.wav");
//        sleep(5);
//        //previous_sound = 1;
//    }
//    else {
      ROS_INFO("should play inner sound & stop all other sounds");
        ROS_INFO("stop -playing inner");
        room_sound_pointer->stopAll();
        //room_sound_pointer->repeat("inner");
        room_sound_pointer->startWave("/home/tosh-sat/light_room_sounds/5_seconds_middle.wav");
        sleep(5);
        //previous_sound = 1;
//    }
  }
}

int main(int argc, char **argv)
{
  // Set up ROS
  ros::init(argc, argv, "sound_node");
  ros::NodeHandle node;

  sound_play::SoundClient room_sound;
  sleep(1);
  room_sound_pointer = &room_sound;

  ROS_INFO("sound node started");

  int i;
  ros::Subscriber sound_sub = node.subscribe("light_room_person_point", 1,  soundCallback);

  ros::spin();
}
