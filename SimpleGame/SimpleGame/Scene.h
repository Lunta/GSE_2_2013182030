#pragma once
#include "Renderer.h"

class Scene
{
public:
	enum class Type {
		Title = 0,
		Main,
		Count
	};

protected:
	Type		m_tag;
	Renderer*	m_pRenderer;

	Vec4f		m_vec4fBackgroundColor;

public:
	Scene() = delete;
	Scene(const Type& tag);
	virtual ~Scene();

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Update(const double TimeElapsed) = 0;
	virtual void PrepareUpdate(const double TimeElapsed) = 0;
	virtual void PhysicsProcess(const double TimeElapsed) = 0;
	virtual void Render() = 0;

	virtual void Input_Key(unsigned char key, int x, int y) = 0;
	virtual void Input_SpecialKey(int key, int x, int y) = 0;
	virtual void Input_MouseButton(int button, int state, int x, int y) = 0;

	const Type& GetTag() { return m_tag; }
};

#define SceneTypeToIdx(Enum) GetEnumValueByType(Scene::Type::Enum)
