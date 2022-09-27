#include "Device.h"

HRESULT Device::CreateDevice()
{
	// 1) 디바이스 생성
	// Direct3D를 사용하기 위해서는 반드시 디바이스 및 디바이스컨텍스트를 생성(획득)해야 작업이 가능해짐
	// ID3D11Device(리소스의 생성을 담당)
	// ID3D11DeviceContext(랜더링 담당)
	// 디바이스의 기능이 분리됨으로 인해 멀티 스레딩 랜더링이 가능해짐
	// 멀티 스레드를 이용한 랜더링을 하기 위해서는 DeferredContext를 사용해야 함
	//
	// ID3D11Device // 주로 리소스의 생성과 관련된 작업
	// ID3D11DeviceContext // 생성된 리소스들을 사용하여 랜더링 처리 및 제어
	// IDXGISwapChain // 전면 버퍼 및 후면 버퍼들을 생성 및 제어
	// ID3D11RenderTargetView // 생성된 후면버퍼들 중에서 랜더링(출력) 될 대상버퍼를 지정
	// DXGI_SWAP_CHAIN_DESC // 생성할 스왑체인 객체의 속성값 지정
	// D3D11_VIEWPORT //윈도우 안에서 랜더링 될 영역을 지정
	// 
	// D3D_FEATURE_LEVEL Direct3D버전을 열거한 것 특성 레벨이라 함
	// 선택된 변수에 따라 지원하는 쉐이더버전이 다르게 된다. 우리는 쉐이더 5.0을 앞으로 사용할 것이기 때문에 D3D_FEATURE_LEVEL_11_0으로 설정
	// 
	// D3D_DRIVER_TYPE은 디바이스의 생성 타입을 지정하며 D3D_DRIVER_TYPE열거형 변수 중 하나가 사용 된다.
	// Direct11을 하드웨어적으로 지원한다면 D3D_DRIVER_TYPE_HARDWARE으로 지정하고 그렇지 않을 경우 
	// D3D_DRIVER_TYPE_WARP 또는 D3D_DRIVER_TYPE_REFFERENCE(GPU의 연산을 CPU에서 저속처리 한다는 뜻)을 사용
	// 
	// 더블 버퍼링과 페이지 플릿핑
	// 전면버퍼에 직접 랜더링하면 랜더링 과정이 눈에 보여서 화면 깜빡임이 발생
	// 스왑체인을 생성하는 이유가 이 더블 버퍼링 방식을 사용하기 위함
	// 복사방식과 교체 방식이 사용
	// 
	// 
	// 
	// **CreateDeviceAndSwapChain**
	// IDXGIAdapter* pAdapter // 디스플레이 시스템이며 이값이 NULL이면 주 디스플레이 어댑터 장치가 선택
	// D3D_DRIVER_TYPE DriverType // 디바이스 디바이스 드라이버의 타입 중에 하나가 되어야 함
	// HMODULE Software // 일반적으로 NULL
	// UINT Flags // 디바이스 생성 플래그로써 D3D11_CREATE_DEVICE_FLAG중 하나가 사용된다., 비트 논리합이 가능
	// D3D_FEATURE_LEVEL* pFeatureLevels //enum D3D_FEATURE_LEVEL의 주소 및 배열의 주소
	// UINT FeatureLevels // pFeatureLevels 배열의 개수
	// UINT SDKVersion // SDK버전을 나타내는 플래그로 D3D11_SDK_VERSION을 사용하면 됨
	// DXGI_SWAP_CHAIN_DESC* pSwapChainDesc // 스왑체인 속성 지정
	// IDXGISwapChain** ppSwapChain 
	// ID3D11Device** ppDevice, // 
	// D3D_FEATURE_LEVEL* pFeatureLevel,
	// ID3D11DeviceContext** ppImmediateContext
	//
	// 
	//


	HRESULT hr;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL pFeatureLevel;
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT FeatureLevels = 1;
	hr = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &_pd3dDevice, &pFeatureLevel, &_pImmediateContext);
	//pd3dDevice 다른 인터페이스 생성시 사용
	//pImmediateContext 생성된 인터페이스를 사용(관리, 제어)할 때
	return hr;
}

HRESULT Device::CreateDXGIDevice()
{
	// 2) 팩토리 생성
	// 스왑체인 객체를 생성하기 위해 만듬
	// 
	// DXGI DirectX10에 새롭게 등장
	// 유저모드와 커널모드를 연결해 주는 단계
	// 커널 모드 드라이브 및 시스템 하드웨어와 통신하는 것이 목적
	//
	/*HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pGIFactory);*/
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)_pGIFactory.GetAddressOf());
	return hr;
}

HRESULT Device::CreateSwapChain()
{
	// 3) 스왑체인 생성
	// 후면(백)버퍼 생성 -> 전면버퍼
	//
	// DXGI_SWAP_CHAIN_DESC
	//DXGI_MODE_DESC BufferDesc; 백버퍼 모드를 나타내는 DXGI_MODE_DESC 구조
	//DXGI_SAMPLE_DESC SampleDesc; 멀티 샘플링 매개 변수를 나타내는 구조
	//DXGI_USAGE BufferUsage; 백버퍼 표면 사용법 및 CPU 액세스 옵션을 나타내는 DXGI_USAGE 열거 형 멤버, 쉐이더를 입력하거나 렌더 타겟 출력으로 사용 할 수 있다.
	//UINT BufferCount; 스왑 체인의 버퍼 개수
	//HWND OutputWindow; 출력 창에 HWND 핸들, NULL이 될 수 없다
	//BOOL Windowed; 윈도우 모드 = TRUE, 풀스크린 모드 = FALSE
	//DXGI_SWAP_EFFECT SwapEffect; 플립핑 이후 렌더 타겟 버퍼의 내용을 처리하기 위한 DXGI_SWAP_EFFECT 열거 형 멤버중 하나가 지정된다
	//UINT Flags; 스왑체인동작 옵션을 나타내는 DXGI_SWAP_CHAIN_FLAG 열거 형 멤버이다.
	// 
	// DXGI_MODE_DESC
	//UINT Width; 해상도의 너비를 나타내는 값
	//UINT Height; 해상도 높이를 나타내는 값
	//DXGI_RATIONAL RefreshRate; 재생빈도를 나타내는 DXGI_RATIONAL 구조
	//DXGI_FORMAT Format; 백버퍼 출력픽셀 포멧을 나타내는 DXGI_FORMAT 구조
	//DXGI_MODE_SCANLINE_ORDER ScanlineOrdering; 주사선 렌더링 모드의 형식을 타나낸다
	//DXGI_MODE_SCALING Scaling; 크기 조정 모드를 나타낸다
	// 
	// DXGI_RATIONAL
	// UINT Numerator 재생빈도의 분자값(보통 60 값을 사용한다)
	// UINT Denominator 재생빈도의 분모값
	// 
	// DXGI_FORMAT
	// 백 버퍼의 픽셀 포맷을 지정
	// 일반적으로 32비트 픽셀 포맷(DXGI_FORMAT_R8G8B8A8_UNORM)을 많이 사용(색상표현 방식으로 많이들 사용)
	// 
	// DXGI_SAMPLE_DESC
	// UINT Count; //픽셀 단위의 멀티 샘플링의 수
	// UINT Quality; // 이미지의 품질 수준이 반환된다. 품질이 높을수록 성능의 저하 => 1로 지정되면 멀티 샘플링을 하지 않겠다는 것과 같음
	// 
	// DXGI_USAGE
	// 스왑체인의 버퍼를 생성하려면 반드시 DXGI_USAGE_RENDER_TARGET_OUTPUT 이어야 함
	// 
	// DXGI_SWAP_EFFECT
	// DXGI_SWAP_EFFECT_DISCARD Present를 호출하게 되면 백 버퍼의 내용이 삭제
	// DXGI_SWAP_EFFECT_SEQUENTIAL Present를 호출하게 되면 백 버퍼의 내용이 보존된다. 단 플래그는 멀티 샘플링과 함께 사용할 수 없다.
	// 
	// DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH 해상도에 맞게 전체화면시 재 조절
	//
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _rtClient.right;
	sd.BufferDesc.Height = _rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 한번 확인해보기
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.Windowed = true;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	return _pGIFactory->CreateSwapChain(_pd3dDevice.Get(), &sd, _pSwapChain.GetAddressOf());
}

HRESULT Device::CreateRenderTargetView()
{
	// 4) 랜더타겟뷰 생성
	// 
	// ID3D11RenderTargetView 함수는 렌더링 될 백 버퍼의 메로리로써 스왑체인의 백 버퍼를 나타내는 인터페이스이며 생성된 스왑체인 버퍼와 연결하게 된다.
	// 어디다 그릴 것인지
	// 
	// GetBuffer
	// UINT Buffer //스왑체인 백 버퍼의 인덱스
	// REFIID riid //스왑체인 백 버퍼의 반환되는 인터페이스 타입을 지정
	// void** ppSurface // 지정된 타입으로 생성된 객체의 주소가 반환
	// 
	// 이렇게 반환된 백 버퍼는 랜더링 결과가 저장될 대상으로 지정하기 위해서 CreateRenderTargetView 함수로 지정
	// 
	// OMSetRenderTarget 생성된 랜더타겟뷰를 디바이스가 사용할 수 있도록 셋팅(출력 병합기)
	// 
	// 스왑체인의 각 백 버퍼들은 각각 D3D11Texture2D객체로 표현
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, _pRTV.GetAddressOf());
	pBackBuffer->Release();
	if (FAILED(hr)) return hr;
	//_pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
	return S_OK;
}

void Device::CreateViewport()
{
	// 5)뷰포트 설정
	// 
	// 스크린의 어떤 위치에 작업한 내용을 표현할 것인지 구역 설정하는 것
	//
	_vp.Width = _rtClient.right;
	_vp.Height = _rtClient.bottom;
	_vp.TopLeftX = 0;
	_vp.TopLeftY = 0;
	_vp.MinDepth = 0.0f;
	_vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &_vp);
}

bool Device::Init()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIDevice()))
	{
		return false;
	}
	if (FAILED(hr = CreateDevice()))
	{
		return false;
	}
	if (FAILED(hr = CreateSwapChain()))
	{
		return false;
	}
	if (FAILED(hr = CreateRenderTargetView()))
	{
		return false;
	}
	CreateViewport();
	return true;
}

bool Device::Frame()
{
	return true;
}

bool Device::Render()
{
	return true;
}

bool Device::Release()
{
	/*if (_pd3dDevice) _pd3dDevice->Release();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pGIFactory) _pGIFactory->Release();
	if (_pSwapChain) _pSwapChain->Release();
	if (_pRTV) _pRTV->Release();*/
	return true;
}
