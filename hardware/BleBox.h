#pragma once

// implememtation for devices : http://blebox.eu/
// by Fantom (szczukot@poczta.onet.pl)

#include "DomoticzHardware.h"
#include "../main/RFXtrx.h"
#include "../json/json.h"

typedef struct _STR_DEVICE {
	int			unit;
	std::string api_name;
	std::string name;
	int			deviceID;
	int			subType;
	int			switchType;
} STR_DEVICE;

class BleBox : public CDomoticzHardwareBase
{
public:
	BleBox(const int id, const int pollIntervalsec);
	virtual ~BleBox();

	bool WriteToHardware(const char *pdata, const unsigned char length);

	void AddNode(const std::string &name, const std::string &IPAddress);
	bool UpdateNode(const int id, const std::string &name, const std::string &IPAddress);
	void RemoveNode(const int id);
	void RemoveAllNodes();
	void SetSettings(const int pollIntervalsec);
	void Restart();

private:
	volatile bool m_stoprequested;
	int m_PollInterval;
	boost::shared_ptr<boost::thread> m_thread;
	std::map<const std::string, const int> m_devices;
	boost::mutex m_mutex;

	bool StartHardware();
	bool StopHardware();
	void Do_Work();

	std::string IdentifyDevice(const std::string &IPAddress);
	int GetDeviceTypeByApiName(const std::string &apiName);
	std::string GetDeviceIP(const tRBUF *id);
	std::string GetDeviceIP(const std::string &id);
	Json::Value SendCommand(const std::string &IPAddress, const std::string &command);
	void GetDevicesState();

	void ReloadNodes();
	void UnloadNodes();
	bool LoadNodes();
};