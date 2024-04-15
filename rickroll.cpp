#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <chrono>

int main(void) {
    CoInitialize(NULL);
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    IAudioEndpointVolume *endpointVolume = NULL;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    float currentVolume = 0;
    endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);

    PlaySound(TEXT("rickroll"), NULL, SND_RESOURCE | SND_ASYNC);
    std::chrono::time_point start = std::chrono::steady_clock::now();
    while(true) {
        endpointVolume->SetMasterVolumeLevelScalar(1.0, NULL);
        endpointVolume->SetMute(false, NULL);
        if(std::chrono::steady_clock::now() - start > std::chrono::seconds(213))
            break;
    }

    endpointVolume->Release();

    CoUninitialize();

    return 0;
}