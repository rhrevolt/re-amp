#include "Application.h"
#include "config.h"
#include "StateManager.h"

//-------------------------------------------------------------------------------------
Application::Application(void)
{
	stateMgr = StateManager::instance();
}
//-------------------------------------------------------------------------------------
Application::~Application(void)
{
	free(stateMgr);
}

//-------------------------------------------------------------------------------------
void Application::createScene(void)
{
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);

	//Start our sample game
	stateMgr->newGame();
}

void Application::mainLoopPreRender(void)
{
	stateMgr->tick();
}

void Application::mainLoopPostRender(void)
{
    
}
