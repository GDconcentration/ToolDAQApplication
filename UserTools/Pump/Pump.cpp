#include "Pump.h"
Pump::Pump() : Tool()
{
}

bool Pump::Initialise(std::string configfile, DataModel &data)
{
	if(configfile!="")  m_variables.Initialise(configfile);
	//m_variables.Print();

	m_data= &data;

	m_variables.Get("pump_pin",pumppin);

	std::stringstream command;
	command<<"echo \""<<pumppin<<"\" > /sys/class/gpio/export";
	system(command.str().c_str());

	command.str("");
	command<<"echo \"out\" > /sys/class/gpio/gpio"<<pumppin<<"/direction";
	system(command.str().c_str());
	
	m_data->changeWater = false;

	return true;
}

bool Pump::Execute()
{
	switch (m_data->mode)
	{
		case state::change_water:
		case state::finalise:
			m_data->changeWater = false;
			TurnOn();
			break;
		case state::power_down:
		default:
			TurnOff();
			break;
	}
	return true;
}


bool Pump::Finalise()
{
	return true;
}

void Pump::TurnOn()
{
	//write to GPIO
  std::stringstream command;
  command<<"echo \"1\" > /sys/class/gpio/gpio"<<pumppin<<"/value";
  system(command.str().c_str());

}

void Pump::TurnOff()
{
	//write to GPIO
  std::stringstream command;
  command<<"echo \"0\" > /sys/class/gpio/gpio"<<pumppin<<"/value";
  system(command.str().c_str());
  
  
}
