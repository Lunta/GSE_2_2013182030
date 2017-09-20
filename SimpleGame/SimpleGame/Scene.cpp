#include "stdafx.h"
#include "Scene.h"
#include "Framework.h"

Scene::Scene(const Type& tag) :
	m_pRenderer(nullptr), 
	m_vec4fBackgroundColor({ 0.0f, 0.0f, 0.0f, 1.0f })
{
	m_tag = tag;
}

Scene::~Scene()
{
	ReleaseObjects();
}

void Scene::BuildObjects()
{
	// Initialize Renderer
	m_pRenderer = new Renderer(GameFramework.GetClientWidth(), GameFramework.GetClientHeight());
	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

void Scene::ReleaseObjects()
{
	delete m_pRenderer;
}
