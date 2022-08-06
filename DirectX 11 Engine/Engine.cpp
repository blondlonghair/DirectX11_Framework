#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	timer.Start();

	if (!this->render_window.Initialize(this, hInstance, window_title, window_class, width, height))
		return false;

	if (!gfx.Initialize(this->render_window.GetHWND(), width, height))
		return false;

	return true;
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}

void Engine::Update()
{
	float dt = timer.GetMilisecondsElapsed();
	timer.Restart();

	while (!keyboard.charBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (mouse.IsRightDown())
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				this->gfx.camera3D.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	this->gfx.gameObject.AdjustRotation(0.0f, 0.001f * dt, 0.0f);

	float Camera3D3D3D3D3D3D3D3D3DSpeed = 0.005f;

	if (keyboard.KeyisPressed(VK_SHIFT))
	{
		Camera3D3D3D3D3D3D3D3D3DSpeed = 0.3f;
	}

	if (keyboard.KeyisPressed('W'))
	{
		this->gfx.camera3D.AdjustPosition(this->gfx.camera3D.GetForwardVector() * Camera3D3D3D3D3D3D3D3D3DSpeed * dt);
	}
	if (keyboard.KeyisPressed('S'))
	{
		this->gfx.camera3D.AdjustPosition(this->gfx.camera3D.GetBackwardVector() * Camera3D3D3D3D3D3D3D3D3DSpeed * dt);
	}
	if (keyboard.KeyisPressed('A'))
	{
		this->gfx.camera3D.AdjustPosition(this->gfx.camera3D.GetLeftVector() * Camera3D3D3D3D3D3D3D3D3DSpeed * dt);
	}
	if (keyboard.KeyisPressed('D'))
	{
		this->gfx.camera3D.AdjustPosition(this->gfx.camera3D.GetRightVector() * Camera3D3D3D3D3D3D3D3D3DSpeed * dt);
	}
	if (keyboard.KeyisPressed('E'))
	{
		this->gfx.camera3D.AdjustPosition(0.0f, Camera3D3D3D3D3D3D3D3D3DSpeed * dt, 0.0f);
	}
	if (keyboard.KeyisPressed('Q'))
	{
		this->gfx.camera3D.AdjustPosition(0.0f, -Camera3D3D3D3D3D3D3D3D3DSpeed * dt, 0.0f);
	}

	if (keyboard.KeyisPressed('C'))
	{
		XMVECTOR lightPosition = this->gfx.camera3D.GetPositionVector();
		lightPosition += this->gfx.camera3D.GetForwardVector();
		this->gfx.light.SetPosition(lightPosition);
		this->gfx.light.SetRotation(this->gfx.camera3D.GetRotationFloat3());
	}
}

void Engine::RenderFrame()
{
	this->gfx.RenderFrame();
}
