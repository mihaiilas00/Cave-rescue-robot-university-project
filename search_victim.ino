//#include "Arduino.h"

void search_victim()
{
	for (i = 0; i < 4; i++)															//find the closest victim
	{
		float minimum_grabber = 1e10;
		if (victim[i][0] > 0 && victim[i][1] > 0)				 //only look at victims not already collected
		{
		distance_robot = sqrt(sq((float)(closest_victim_y - robot_y)) + sq((float)(closest_victim_x - robot_x)));
		distance_grabber = sqrt(sq((float)(closest_victim_y - grabber_y)) + sq((float)(closest_victim_x - grabber_x)));

			if (distance_grabber < minimum_grabber)
			{
				minimum_grabber = distance_grabber;
			 // minimum_robot = distance_robot;
				closest_victim_x = victim[i][0];
				closest_victim_y = victim[i][1];
			}
		}
	}
	bool victim_reached = 0;
	while (victim_reached == 0)														//check if a victim has been reached
	{

		distance_robot = sqrt(sq((float)(closest_victim_y - robot_y)) + sq((float)(closest_victim_x - robot_x)));
		distance_grabber = sqrt(sq((float)(closest_victim_y - grabber_y)) + sq((float)(closest_victim_x - grabber_x)));
			
		tan_theta = (grabber_y - robot_y) / (grabber_x - robot_x);
		theta = atan(tan_theta);
		//minimum=0;
		
		if (distance_grabber > distance_robot && distance_grabber>length_robot)											//if the robot orientation si wrong, turn 180 degrees
		{
			rotation(3.14);
		}
		tan_phi = (closest_victim_y - grabber_y) / (closest_victim_x - grabber_x);
		phi = atan(tan_phi);
		target_distance = distance_grabber;
		target_angle = phi - theta;
		//rotation_speed = (K1 * 255 * target_angle);
		//moving_speed = (K2 * 255 * target_distance);
		
			forward_time = (int)((target_distance/forward_speed)*600+500);
		
		rotation(target_angle);
		move_forward(forward_time, forward_speed);	 //move to the victim
		
		if (closest_victim_x - 20 < grabber_x && grabber_x < closest_victim_x + 20 && closest_victim_y - 20 < grabber_y && grabber_y < closest_victim_y + 20)
		{
			fine_tuning();
			victim_reached = 1;													//mark that victim has been reached
			closest_victim_x = -1;							//mark victim taken so it is disregarded in the future
			closest_victim_y = -1;
		}
		requestUpdate("fine hello");
		wifi_loop();
		assign_coordinates();
	}
}
