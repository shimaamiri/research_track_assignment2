#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "second_assignment/Service.h"
#include "std_srvs/Empty.h"
#include "stdio.h"

const char * buttons = R"(
   
   Press w to increase the velocity
   Press s to decrease the velocity
   Press r to reset the position
   Press q to quit
)";


int main ( int argc, char ** argv ) {

   float tmp;
   
   float velocity = 0.0;
   
   // Initializing ros node
   ros::init(argc, argv, "command_interface");
   ros::NodeHandle nh;

   // clients
   ros::ServiceClient client_srv = nh.serviceClient<second_assignment::Service>("/service");
   ros::ServiceClient client_res = nh.serviceClient<std_srvs::Empty>("/reset_positions");

   // Initializing servers
   second_assignment::Service server_srv;
   std_srvs::Empty server_res;

   // Printing on screen 
   printf( "%s", buttons );
   printf( "speed: %f\n", velocity);

   char input = 'r'; // Initialize the variable input

   
   while (ros::ok()) {

      scanf(" %c", &input); // Read command
      
      if(input == 'q')
      {
      	ros::shutdown();
      }
      else if ( input == 'w' || input == 's' || input == 'r') 
      {
         // Send a request to the service
         server_srv.request.command = input;
	 client_srv.waitForExistence();

         if ( client_srv.call(server_srv) ) 
         {

            if ( input == 'r' ) 
            {
            	// reset
               client_res.waitForExistence();
               client_res.call(server_res);
               printf("reset\n");
            }
            
            // Receive the final velociity from the server
	    tmp = server_srv.response.vel_final;
            
            if(tmp == 0 && velocity == 0 && input != 'r')
            	printf("Error: The velocity can't be decreased anymore!\n");
            else if(tmp == velocity && tmp == 5)
            	printf("Error: The velocity can't be increased anymore!\n");
            else
            	velocity = tmp;
            // Print new velocity
            printf( "the speed is: %f\n", velocity);
         }
      } else {
         // print if wrong button is entered
         printf( "Error: wrong button: %c\n", input );
      }
   }

   return 0;
}
