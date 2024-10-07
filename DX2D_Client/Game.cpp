#include "pch.h"
#include "Game.h"

Game::Game()
	: m_Hwnd(nullptr)
	, m_Width(0)
	, m_Height(0)
	, m_ClearColor{0.f, 0.f, 0.f, 0.f}
	, m_Device(nullptr)
	, m_DeviceContext(nullptr)
	, m_SwapChain(nullptr)
{
}

Game::~Game()
{
}

void Game::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = m_Width;
		desc.BufferDesc.Height = m_Height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = m_Hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		m_SwapChain.GetAddressOf(),
		m_Device.GetAddressOf(),
		nullptr,
		m_DeviceContext.GetAddressOf()
	);
	
	CHECK(hr);

}

void Game::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
	CHECK(hr);

}

void Game::SetViewport()
{
	m_Viewport.TopLeftX = 0.0f;
	m_Viewport.TopLeftY = 0.0f;
	m_Viewport.Width = static_cast<float>(m_Width);
	m_Viewport.Height = static_cast<float>(m_Height);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
}

void Game::RenderBegine()
{
	m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), m_ClearColor);
	m_DeviceContext->RSSetViewports(1, &m_Viewport);
}

void Game::RenderEnd()
{
	// 후면버퍼에 그린 그림을 전면버퍼로 보여달라는 의미.
	m_SwapChain->Present(1, 0);
}

void Game::Init(HWND _Hwnd)
{
	m_Hwnd = _Hwnd;
	m_Width = GWinSizeX;
	m_Height = GWinSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void Game::Update()
{
}

void Game::Render()
{
	RenderBegine();
	RenderEnd();
}

