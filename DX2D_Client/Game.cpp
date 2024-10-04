#include "pch.h"
#include "Game.h"

Game::Game()
	: m_Hwnd(nullptr)
	, m_Width(0)
	, m_Height(0)
{
}

Game::~Game()
{
}

void Game::Init(HWND _Hwnd)
{
	m_Hwnd = _Hwnd;
	m_Width = GWinSizeX;
	m_Height = GWinSizeY;
}

void Game::Update()
{
}

void Game::Render()
{
}

