#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <math.h>
#include <ros_arduino_msgs/ServoWrite.h>
#include <geometry_msgs/Point.h>

//important parameters
int square_side_half = 1; //describer the area

const double halfC = M_PI / 180;

int main(int argc, char** argv){
	ros::init(argc, argv, "light_controller_node");

	ros::NodeHandle node;
 
	tf::TransformListener listener;

  ros::ServiceClient servo_write_client = node.serviceClient<ros_arduino_msgs::ServoWrite>("arduino/servo_write");

  ros::Publisher sound_pub = node.advertise<geometry_msgs::Point>("light_room_person_point", 20);

  ros::Rate loop_rate(10);

  //int previous_sound = 0;

	while (node.ok()){
        tf::StampedTransform transform;
    try {
          ROS_INFO("node started");

          //listening to the transfom message
          //listener.lookupTransform("/openni_depth_frame", "/right_foot", ros::Time(0), transform);
          listener.lookupTransform("/room_link", "/head", ros::Time(0), transform);

          //room axis
          //mapping from kinect frames to flashlight frame
          //to subtract [0.526, -0.895, 2.229] [y, z, x]to make the flashlight as the origin
          //double x_body_BS = transform.getOrigin().z();
          //double y_body_BS = transform.getOrigin().x();
          //double z_body_BS = transform.getOrigin().y();
          double x_body = transform.getOrigin().x();
          double y_body = transform.getOrigin().y();
          double z_body = transform.getOrigin().z ();

          double zMax = 2.65; //TODO: make it a ROS parameter

          //calculating serbo angle
          //change type to int
          // the plus 10 is servo bracket error correction
          double servoXangleDegree = atan( x_body / zMax) * 180 / M_PI + 90 + 7 + 5;
          double servoYangleDegree = atan( y_body / zMax) * 180 / M_PI + 90 - 3 + 9;
          double servoXangleRad = servoXangleDegree * M_PI / 180;
          double servoYangleRad = servoYangleDegree * M_PI / 180;


          //printing values
          //ROS_INFO("X Y Z beforeS :%f %f %f", x_body_BS, y_body_BS, z_body_BS);
          ROS_INFO("X, Y, Z frame %f %f %f", x_body, y_body, z_body);
          ROS_INFO("X, Y angles :%f %f", servoXangleDegree, servoYangleDegree);
          ROS_INFO("X, Y angles :%f %f", servoXangleRad, servoYangleRad);

          //servo_write services
            //x_servox
            //declaring the srv for y_servo
            ros_arduino_msgs::ServoWrite x_servo_srv;
            x_servo_srv.request.id = 0;
            x_servo_srv.request.value = servoXangleRad;
            //calling the service
            servo_write_client.call(x_servo_srv);

            //y_servo
            //declaring the srv for y_servo
            ros_arduino_msgs::ServoWrite y_servo_srv;
            y_servo_srv.request.id = 1;
            y_servo_srv.request.value = servoYangleRad;
            //calling the service
            servo_write_client.call(y_servo_srv);

          //publishing the point for the sounde_node
          geometry_msgs::Point light_room_person_point;
          light_room_person_point.x = x_body;
          light_room_person_point.y = y_body;
          light_room_person_point.z = z_body;

          sound_pub.publish(light_room_person_point);

//          //printing which area i'n in (inner - wall - door)
//          if (x_body > square_side_half || x_body < -square_side_half || y_body > square_side_half || y_body < -square_side_half) {
//            //check door steps first {
//              //if within play door sound (but where is the door) & stop others
//                //if ( previous_sound != 3) { room_sound.stopAll();
//                //                            room_sound.builtinSound(3).play();
//                //                            sleep(1);
//                //                            previous_sound = 3;
//                //}
//            //}
//            //else {
//                ROS_INFO("play wall sound & stop all other sounds");
//            //}
//          }
//          else {
//            ROS_INFO("play inner sound & stop all other sounds");
//          }
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep(); //why!!!

      //Directing servo at door
      ROS_INFO("Directing flashlight at door");
        //x_servox
        //declaring the srv for y_servo
        //TODO edit door angles with thier correct values
        ros_arduino_msgs::ServoWrite x_servo_srv;
        x_servo_srv.request.id = 0;
        x_servo_srv.request.value = 2.05;
        //calling the service
        servo_write_client.call(x_servo_srv);

        //y_servo
        //declaring the srv for y_servo
        ros_arduino_msgs::ServoWrite y_servo_srv;
        y_servo_srv.request.id = 1;
        y_servo_srv.request.value = 1.28;
        //calling the service
        servo_write_client.call(y_servo_srv);

			continue;
		}
		loop_rate.sleep();
	}
	return 0;
}
