#pragma once

class Game
{
private:
	HWND		m_Hwnd;
	int32		m_Width;
	int32		m_Height;

public:
	void Init(HWND _Hwnd);
	void Update();
	void Render();

public:
	Game();
	~Game();
};

