#include <jderobot/comm/ardroneextraClient.hpp>
#include <jderobot/comm/ice/ardroneextraIceClient.hpp>
#ifdef JDERROS
//#include <jderobot/comm/ros/publisherArDroneExtra.hpp>
#endif

namespace Comm {

ArDroneExtraClient* 
getArDroneExtraClient(Comm::Communicator* jdrc, std::string prefix){
	ArDroneExtraClient* client = 0;


	int server = jdrc->getConfig().asIntWithDefault(prefix+".Server", 0);
	switch (server){
		case 0:
		{
			std::cout << "ArDroneExtra disabled" << std::endl;
			break;
		}
		case 1:
		{
			std::cout << "Sending ArDroneExtra by ICE interfaces" << std::endl;
			ArDroneExtraIceClient* cl;
			cl = new ArDroneExtraIceClient(jdrc, prefix);
		    client = (Comm::ArDroneExtraClient*) cl;
		    break;
		}
		case 2:
		{
			#ifdef JDERROS
				/*std::cout << "Sending Velocities by ROS messages" << std::endl;
				std::string nodeName;
				nodeName =  jdrc->getConfig().asStringWithDefault(prefix+".Name", "ArDroneExtraNode");
				std::string topic;
				topic = jdrc->getConfig().asStringWithDefault(prefix+".Topic", "");
				PublisherArDroneExtra* pm;
				pm = new PublisherArDroneExtra(0, nullptr, nodeName, topic);
				pm->start();
				client = (Comm::ArDroneExtraClient*) pm;
				*/
				throw "ERROR: ArDroneExtra is not supported with ROS yet";
            #else
				throw "ERROR: ROS is not available";
			#endif
		 	break;
		}
		default:
		{
			std::cerr << "Wrong " + prefix+".Server property" << std::endl;
			break;
		}

	}

	return client;


}

}//NS
