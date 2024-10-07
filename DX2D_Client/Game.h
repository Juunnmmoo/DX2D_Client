#pragma once

class Game
{
private:
	HWND		m_Hwnd;
	uint32		m_Width;
	uint32		m_Height;

	float			m_ClearColor[4];

private:
	
	// Device & SwapChain
	ComPtr<ID3D11Device>				m_Device;
	ComPtr<ID3D11DeviceContext>	m_DeviceContext;
	ComPtr<IDXGISwapChain>			m_SwapChain;

	// RTV
	ComPtr<ID3D11RenderTargetView>		m_RenderTargetView;

	// ViewPort
	D3D11_VIEWPORT m_Viewport = { 0 };
	


private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:

	// 도화지 초기화
	void RenderBegine();
	
	// 도화지 제출
	void RenderEnd();

public:
	void Init(HWND _Hwnd);
	void Update();
	void Render();

public:
	Game();
	~Game();
};

