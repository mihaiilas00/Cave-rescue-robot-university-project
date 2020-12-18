//#include <Adafruit_MotorShield.h>

void fine_tuning()    //rotate for 1 second with a given speed and move forwards for 2 seconds with a gives speed
{
  int tuned=0;
  while(tuned==0)
  {
    tan_theta = (grabber_y - robot_y) / (grabber_x - robot_x);
    theta = atan(tan_theta);

    tan_phi = (closest_victim_y - grabber_y) / (closest_victim_x - grabber_x);
    phi = atan(tan_phi);

    target_angle = phi - theta;
    if (target_angle>-0.1 && target_angle<0.1)
    {
      tuned = 1;
      break;
    }
    rotation(target_angle);
    requestUpdate("Rotating:", target_angle, "Moving:", 0, " fine hello");
    wifi_loop();
    assign_coordinates();
  }
  move_forward(3000,50);  //to be calibrated experientally----------------------------------------------
  
}
