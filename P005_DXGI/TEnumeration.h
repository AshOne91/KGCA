#pragma once
#include "TDefine.h"
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class TEnumOutput
{
public:
    ~TEnumOutput();
	void						Set(UINT iIndex, IDXGIOutput* pAdapter);
    UINT						m_Output;
    IDXGIOutput*				m_pOutput;
    DXGI_OUTPUT_DESC			m_Desc;
	vector<DXGI_MODE_DESC>		m_DisplayModeList;    
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class TEnumDevice
{
public:

public:
    ~TEnumDevice();
    UINT						m_AdapterOrdinal;
	vector<TEnumOutput*>		m_OutputInfoList;
    D3D_DRIVER_TYPE				DeviceType;
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class TEnumAdapter
{  
public:
    ~TEnumAdapter();
	void					Set(UINT iIndex, IDXGIAdapter* pAdapter);
    UINT					m_AdapterOrdinal;
    DXGI_ADAPTER_DESC		m_AdapterDesc;
    IDXGIAdapter*			m_pAdapter;
    vector<TEnumOutput*>	m_OutputInfoList;
	vector<TEnumDevice*>	m_DeviceInfoList;
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class TEnumeration
{
public:
	vector<TEnumAdapter*>	m_AdapterInfoList;	
public:
	HRESULT Enumerate(IDXGIFactory* pFactory);
	HRESULT EnumerateDevices( TEnumAdapter* pAdapterInfo );
	HRESULT EnumerateDisplayModes( TEnumOutput* pOutputInfo );
	HRESULT EnumerateOutputs( TEnumAdapter* pAdapterInfo );
	void	ClearAdapterInfoList();
public:
	TEnumeration(void);
	virtual ~TEnumeration(void);
};
