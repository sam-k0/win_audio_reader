
#include <windows.h>
#include <iostream>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Functiondiscoverykeys_devpkey.h>
#include <stdio.h>

#define SCHEDULE_SLEEP_TIME 100

#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

/// Variable defs
HRESULT hr;
IMMDeviceEnumerator* pEnumerator = NULL;
IMMDevice* pDevice = NULL;
IAudioMeterInformation* pMeterInfo = NULL;
float peakVal = 0.0;

void show_error(const char* msg)
{
	std::cout << msg << std::endl;
}

void exit_on_error(HRESULT hr, const char* msg, int code)
{
	if (hr != S_OK)
	{
		std::cout << msg << std::endl;
		exit(code);

	}
}

/**
 * Will init the globally defined variables to the default audio device.
 * 
 */
void initDevice()
{
	CoInitialize(NULL); // idk
	// Get enumerator for audio endpoint devices.
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);

	// Check result
	exit_on_error(hr, "Could not initialize MMDeviceEnumerator", -1);

	// Get peak meter for default audio-rendering device.
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	exit_on_error(hr, "Get default audio endpoint failed. 2", -2);

	hr = pDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	// Check result
	exit_on_error(hr, "Activate failed", -3);
}


/**
 * Returns the in/output value 0 - 1 of the globally defined audio device.
 * 
 * \param d
 * \return 
 */
float getDevicePeak()
{
	// Get the val?
	float v;
	hr = pMeterInfo->GetPeakValue(&v);
	exit_on_error(hr, "Get Peak val failed", -4);
	return v;
}

/**
 * Iterates all audio devices.
 * 
 */
void iterateAllDevices() {
	/** Iterate all devices*/

	IMMDeviceCollection* enumeratedDevices;
	hr = pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &enumeratedDevices);
	exit_on_error(hr, "EnumAudioEndpoints failed", -11);

	UINT eCount; // Stores the count of devices
	enumeratedDevices->GetCount(&eCount); // Get the count of devices

	std::cout << "Count : " << eCount << std::endl;
	// Loop all devices in enum
	IMMDevice* dev;
	for (UINT i = 0; i < eCount; i++)
	{
		enumeratedDevices->Item(i, &dev);
		//dev->Activate
	}

	/** End iteration */
}

/** Prints out a readable name of the device */
void printDeviceName(IMMDevice* _pDevice)
{
	// Try to get description
	IPropertyStore* pStore;
	_pDevice->OpenPropertyStore(STGM_READ, &pStore);

	PROPVARIANT varName;
	PropVariantInit(&varName);

	pStore->GetValue(PKEY_Device_FriendlyName, &varName);
	// Print endpoint friendly name and endpoint ID.
	printf("Endpoint: \"%S\"\n",
		varName.pwszVal);

	PropVariantClear(&varName);
}

int main(int argc, char** argv)
{
	std::cout << "Hello world!" << std::endl;

	initDevice(); // Initializing


	bool continueLoop = true;
	while (continueLoop)
	{
		Sleep(SCHEDULE_SLEEP_TIME); // Prevent


	}

	// release
	pMeterInfo->Release();
	pDevice->Release();
	pEnumerator->Release();

	return 0;
}

