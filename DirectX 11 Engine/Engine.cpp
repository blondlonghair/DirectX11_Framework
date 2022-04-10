#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
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
				this->gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	const float cameraSpeed = 0.02f;

	if (keyboard.KeyisPressed('W'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetForwardVector() * cameraSpeed);
	}
	if (keyboard.KeyisPressed('S'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetBackwardVector() * cameraSpeed);
	}
	if (keyboard.KeyisPressed('A'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetLeftVector() * cameraSpeed);
	}
	if (keyboard.KeyisPressed('D'))
	{
		this->gfx.camera.AdjustPosition(this->gfx.camera.GetRightVector() * cameraSpeed);
	}
	if (keyboard.KeyisPressed(VK_SPACE))
	{
		this->gfx.camera.AdjustPosition(0.0f, cameraSpeed, 0.0f);
	}
	if (keyboard.KeyisPressed('Z'))
	{
		this->gfx.camera.AdjustPosition(0.0f, -cameraSpeed, 0.0f);
	}
}

void Engine::RenderFrame()
{
	this->gfx.RenderFrame();
}
