#include "targetver.h"
#include <windows.h>
#include <WinSpool.h>
#include <string>
#include <list>
#include <iostream>

struct PortInfo2 {
    std::wstring _portName;
    std::wstring _monitorName;
    std::wstring _description;
    DWORD _portType = 0;
    DWORD _reserved = 0;
};

using PortInfo2List = std::list <PortInfo2>;

std::wstring DecodePortType(const DWORD portType)
{
    std::wstring result;
    result += (portType & PORT_TYPE_WRITE) ? L"write " : L"";
    result += (portType & PORT_TYPE_READ) ? L"read " : L"";
    result += (portType & PORT_TYPE_REDIRECTED) ? L"redirected " : L"";
    result += (portType & PORT_TYPE_NET_ATTACHED) ? L"net_attached " : L"";
    result.pop_back();
    return result;
}

void PrintPortInfo2s(const PortInfo2List& portInfo2List)
{
    std::wcout << portInfo2List.size() << " ports on local machine." << std::endl;
    std::cout << "PORT_INFO_2:" << std::endl;

    for (auto portInfo2Iter = portInfo2List.begin(); portInfo2Iter != portInfo2List.end(); portInfo2Iter++) {
        std::wcout << "  " << portInfo2Iter->_portName << std::endl;
        std::wcout << "    " << portInfo2Iter->_description << std::endl;
        std::wcout << "    " << portInfo2Iter->_monitorName << std::endl;
        const auto portTypeString = DecodePortType(portInfo2Iter->_portType);
        std::wcout << "    portType: " << portInfo2Iter->_portType << " (" << portTypeString << ")" << std::endl;
        if (portInfo2Iter->_reserved) {
            std::wcout << "    reserved (normally zero): " << portInfo2Iter->_reserved << std::endl;
        }
    }
}

PortInfo2List GetPortInfo2List()
{
    DWORD needed {};
    DWORD returned {};
    int rc = ::EnumPortsW(nullptr, 2, nullptr, 0, &needed, &returned);
    if (0 != rc) {
        std::cerr << "EnumPorts() fail: " << ::GetLastError() << std::endl;
        std::exit(-1);
    }

    auto port_into_2s = (PORT_INFO_2*) new byte[needed];
    rc = ::EnumPortsW(nullptr, 2, (PBYTE) port_into_2s, needed, &needed, &returned);
    if (0 == rc) {
        std::cerr << "EnumPorts() fail: " << ::GetLastError() << std::endl;
        std::exit(-1);
    }

    PortInfo2List portInfo2List;

    for (DWORD portInfo2Index = 0; portInfo2Index < returned; portInfo2Index++) {
        PortInfo2 portInfo2 {};
        portInfo2._description = port_into_2s[portInfo2Index].pDescription;
        portInfo2._monitorName = port_into_2s[portInfo2Index].pMonitorName;
        portInfo2._portName = port_into_2s[portInfo2Index].pPortName;
        portInfo2._portType = port_into_2s[portInfo2Index].fPortType;
        portInfo2._reserved = port_into_2s[portInfo2Index].Reserved;
        portInfo2List.push_back(portInfo2);
    }

    return portInfo2List;
}

int main()
{
    auto portList = GetPortInfo2List();
    PrintPortInfo2s(portList);

    // note: PORT_INFO_3 looks good - but we just can't seem to retrieve it here.
    // seems to be only available *inside* a printer driver.
}