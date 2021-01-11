#include <argge/ARGGE.h>
#include <iostream>
#include "Player.h"
#include <time.h>
//wasdqe,.
struct CamController : public Component
{
	void onTick()
	{
		float dt = getCore()->DeltaTime();
		//up,down,left,right,forward,back
		if (getCore()->getInput()->getKey('w'))
		{
			getTransform()->Translate(rend::vec3(0, 0, -10.1f * dt));
		}
		else if (getCore()->getInput()->getKey('s'))
		{
			getTransform()->Translate(rend::vec3(0, 0, 10.1f * dt));
		}
		if (getCore()->getInput()->getKey('a'))
		{
			getTransform()->Translate(rend::vec3(-10.1f * dt, 0, 0));
		}
		else if (getCore()->getInput()->getKey('d'))
		{
			getTransform()->Translate(rend::vec3(10.1f * dt, 0, 0));
		}
		if (getCore()->getInput()->getKey('q'))
		{
			getTransform()->Translate(rend::vec3(0, 10.1f * dt, 0));
		}
		else if (getCore()->getInput()->getKey('e'))
		{
			getTransform()->Translate(rend::vec3(0, -10.1f * dt, 0));
		}

		if (getCore()->getInput()->getKey(','))
		{
			getTransform()->Rotate(rend::vec3(0, 10.5f * dt, 0));
		}
		else if (getCore()->getInput()->getKey('.'))
		{
			getTransform()->Rotate(rend::vec3(0, -10.5f * dt, 0));
		}
	}
};
//uhjkyi
struct LightController : public Component
{
	void onTick()
	{
		//up,down,left,right,forward,back
		if (getCore()->getInput()->getKey('u'))
		{
			getTransform()->Translate(rend::vec3(0, 0, -0.05f));
		}
		else if (getCore()->getInput()->getKey('j'))
		{
			getTransform()->Translate(rend::vec3(0, 0, 0.05f));
		}
		if (getCore()->getInput()->getKey('h'))
		{
			getTransform()->Translate(rend::vec3(-0.05f, 0, 0));
		}
		else if (getCore()->getInput()->getKey('k'))
		{
			getTransform()->Translate(rend::vec3(0.05f, 0, 0));
		}
		if (getCore()->getInput()->getKey('y'))
		{
			getTransform()->Translate(rend::vec3(0, 0.05f, 0));
		}
		else if (getCore()->getInput()->getKey('i'))
		{
			getTransform()->Translate(rend::vec3(0, -0.05f, 0));
		}
	}
};

struct Switcher : public Component
{
	float NUM_SECONDS = 0;
	int currentText = 0;
	void onTick()
	{
		NUM_SECONDS += getCore()->DeltaTime();
		getEntity()->getComponent<Transform>()->Rotate(glm::vec3(0,0.2,0));
		std::cout << NUM_SECONDS << std::endl;
		if (NUM_SECONDS > 10)
		{
			NUM_SECONDS = 0;
			switch (currentText)
			{
			case 0:
				getEntity()->getComponent<Renderer>()->setAlbedo("./Resources/FuturePanel/albedo.png");
				getEntity()->getComponent<Renderer>()->setAO("./Resources/FuturePanel/ao.png");
				getEntity()->getComponent<Renderer>()->setHeight("./Resources/FuturePanel/height.png");
				getEntity()->getComponent<Renderer>()->setNormal("./Resources/FuturePanel/normal.png");
				getEntity()->getComponent<Renderer>()->setMetalness("./Resources/FuturePanel/metallic.png");
				getEntity()->getComponent<Renderer>()->setRoughnesse("./Resources/FuturePanel/roughness.png");
				currentText++;
				break;
			case 1:
				getEntity()->getComponent<Renderer>()->setAlbedo("./Resources/Brick/albedo.png");
				getEntity()->getComponent<Renderer>()->setAO("./Resources/Brick/ao.png");
				getEntity()->getComponent<Renderer>()->setHeight("./Resources/Brick/height.png");
				getEntity()->getComponent<Renderer>()->setNormal("./Resources/Brick/normal.png");
				getEntity()->getComponent<Renderer>()->setMetalness("./Resources/Brick/metallic.png");
				getEntity()->getComponent<Renderer>()->setRoughnesse("./Resources/Brick/roughness.png");
				currentText++;
				break;
			case 2:
				getEntity()->getComponent<Renderer>()->setAlbedo("./Resources/narrowBrick/albedo.png");
				getEntity()->getComponent<Renderer>()->setAO("./Resources/narrowBrick/ao.png");
				getEntity()->getComponent<Renderer>()->setHeight("./Resources/narrowBrick/height.png");
				getEntity()->getComponent<Renderer>()->setNormal("./Resources/narrowBrick/normal.png");
				getEntity()->getComponent<Renderer>()->setMetalness("./Resources/narrowBrick/metallic.png");
				getEntity()->getComponent<Renderer>()->setRoughnesse("./Resources/narrowBrick/roughness.png");
				currentText++;
				break;
			case 3:
				getEntity()->getComponent<Renderer>()->setAlbedo("./Resources/ForestFloor/albedo.png");
				getEntity()->getComponent<Renderer>()->setAO("./Resources/ForestFloor/ao.png");
				getEntity()->getComponent<Renderer>()->setHeight("./Resources/ForestFloor/height.png");
				getEntity()->getComponent<Renderer>()->setNormal("./Resources/ForestFloor/normal.png");
				getEntity()->getComponent<Renderer>()->setMetalness("./Resources/ForestFloor/metallic.png");
				getEntity()->getComponent<Renderer>()->setRoughnesse("./Resources/ForestFloor/roughness.png");
				currentText++;
				break;
			case 4:
				getEntity()->getComponent<Renderer>()->setAlbedo("./Resources/LimeStone/albedo.png");
				getEntity()->getComponent<Renderer>()->setAO("./Resources/LimeStone/ao.png");
				getEntity()->getComponent<Renderer>()->setHeight("./Resources/LimeStone/height.png");
				getEntity()->getComponent<Renderer>()->setNormal("./Resources/LimeStone/normal.png");
				getEntity()->getComponent<Renderer>()->setMetalness("./Resources/LimeStone/metallic.png");
				getEntity()->getComponent<Renderer>()->setRoughnesse("./Resources/LimeStone/roughness.png");
				currentText = 0;
				break;
			}
		}
	}
};


int main()
{
	//std::shared_ptr<Player> pe = core->addEntity();
	/*Player p;
	p.addComponent<Renderer>();*/

	std::shared_ptr<Core> core = Core::initialize();

	//std::shared_ptr<Entity> narrow = core->addEntity();
	//narrow->addComponent<Renderer>();
	//narrow->getComponent<Renderer>()->setAlbedo    ("./Resources/narrowBrick/albedo.png");
	//narrow->getComponent<Renderer>()->setAO        ("./Resources/narrowBrick/ao.png");
	//narrow->getComponent<Renderer>()->setHeight    ("./Resources/narrowBrick/height.png");
	//narrow->getComponent<Renderer>()->setNormal    ("./Resources/narrowBrick/normal.png");
	//narrow->getComponent<Renderer>()->setMetalness ("./Resources/narrowBrick/metallic.png");
	//narrow->getComponent<Renderer>()->setRoughnesse("./Resources/narrowBrick/roughness.png");
	//narrow->getComponent<Renderer>()->setModel("./Resources/Ball/Ball.obj");
	//narrow->getComponent<Transform>()->setPos(rend::vec3(-10.0f, 0.0f, -5.0f));
	////narrow->getComponent<Transform>()->setScale(0.2f);

	//std::shared_ptr<Entity> brick = core->addEntity();
	//brick->addComponent<Renderer>();
	//brick->getComponent<Renderer>()->setAlbedo("./Resources/Brick/albedo.png");
	//brick->getComponent<Renderer>()->setAO("./Resources/Brick/ao.png");
	//brick->getComponent<Renderer>()->setHeight("./Resources/Brick/height.png");
	//brick->getComponent<Renderer>()->setNormal("./Resources/Brick/normal.png");
	//brick->getComponent<Renderer>()->setMetalness("./Resources/Brick/metallic.png");
	//brick->getComponent<Renderer>()->setRoughnesse("./Resources/Brick/roughness.png");
	//brick->getComponent<Renderer>()->setModel("./Resources/Ball/Ball.obj");
	//brick->getComponent<Transform>()->setPos(rend::vec3(-5.0f, 0.0f, -5.0f));
	//brick->getComponent<Transform>()->setScale(0.2f);

	//std::shared_ptr<Entity> panel = core->addEntity();
	//panel->addComponent<Renderer>();
	//panel->getComponent<Renderer>()->setAlbedo("./Resources/FuturePanel/albedo.png");
	//panel->getComponent<Renderer>()->setAO("./Resources/FuturePanel/ao.png");
	//panel->getComponent<Renderer>()->setHeight("./Resources/FuturePanel/height.png");
	//panel->getComponent<Renderer>()->setNormal("./Resources/FuturePanel/normal.png");
	//panel->getComponent<Renderer>()->setMetalness("./Resources/FuturePanel/metallic.png");
	//panel->getComponent<Renderer>()->setRoughnesse("./Resources/FuturePanel/roughness.png");
	//panel->getComponent<Renderer>()->setModel("./Resources/Ball/Ball.obj");
	//panel->getComponent<Transform>()->setPos(rend::vec3(0.0f, 0.0f, -5.0f));
	////panel->getComponent<Transform>()->setScale(0.2f);

	//std::shared_ptr<Entity> forest = core->addEntity();
	//forest->addComponent<Renderer>();
	//forest->getComponent<Renderer>()->setAlbedo("./Resources/ForestFloor/albedo.png");
	//forest->getComponent<Renderer>()->setAO("./Resources/ForestFloor/ao.png");
	//forest->getComponent<Renderer>()->setHeight("./Resources/ForestFloor/height.png");
	//forest->getComponent<Renderer>()->setNormal("./Resources/ForestFloor/normal.png");
	//forest->getComponent<Renderer>()->setMetalness("./Resources/ForestFloor/metallic.png");
	//forest->getComponent<Renderer>()->setRoughnesse("./Resources/ForestFloor/roughness.png");
	//forest->getComponent<Renderer>()->setModel("./Resources/Ball/Ball.obj");
	//forest->getComponent<Transform>()->setPos(rend::vec3(5.0f, 0.0f, -5.0f));
	////forest->getComponent<Transform>()->setScale(0.2f);

	//std::shared_ptr<Entity> stone = core->addEntity();
	//stone->addComponent<Renderer>();
	//stone->getComponent<Renderer>()->setAlbedo("./Resources/LimeStone/albedo.png");
	//stone->getComponent<Renderer>()->setAO("./Resources/LimeStone/ao.png");
	//stone->getComponent<Renderer>()->setHeight("./Resources/LimeStone/height.png");
	//stone->getComponent<Renderer>()->setNormal("./Resources/LimeStone/normal.png");
	//stone->getComponent<Renderer>()->setMetalness("./Resources/LimeStone/metallic.png");
	//stone->getComponent<Renderer>()->setRoughnesse("./Resources/LimeStone/roughness.png");
	//stone->getComponent<Renderer>()->setModel("./Resources/Ball/Ball.obj");
	//stone->getComponent<Transform>()->setPos(rend::vec3(10.0f, 0.0f, -5.0f));//3.5f, 0.0f, -10.0f
	////stone->getComponent<Transform>()->setScale(0.2f);


	std::shared_ptr<Entity> ball = core->addEntity();
	ball->addComponent<Renderer>();
	ball->getComponent<Renderer>()->setAlbedo("./Resources/FuturePanel/albedo.png");
	//ball->getComponent<Renderer>()->setAO("./Resources/FuturePanel/ao.png");
	//ball->getComponent<Renderer>()->setHeight("./Resources/FuturePanel/height.png");
	//ball->getComponent<Renderer>()->setNormal("./Resources/FuturePanel/normal.png");
	//ball->getComponent<Renderer>()->setMetalness("./Resources/FuturePanel/metallic.png");
	//ball->getComponent<Renderer>()->setRoughnesse("./Resources/FuturePanel/roughness.png");
	//std::shared_ptr<Model> cm = core->getCache()->load<Model>("./Resources/Ball/Ball.obj");
	//ball->getComponent<Renderer>()->setModel(cm);

	ball->getComponent<Renderer>()->setModel(core->getCache()->load<Model>("./Resources/Ball/Ball.obj"));
	ball->getComponent<Transform>()->setPos(rend::vec3(0.0f, 0.0f, -10.0f));
	//ball->addComponent<Switcher>();
	
	

	std::shared_ptr<Entity> cam = core->addEntity();
	cam->addComponent<Camera>();
	cam->addComponent<CamController>();
	cam->getComponent<Transform>()->setPos(rend::vec3(0.0f, 0.0f, 0.0f));

	std::shared_ptr<Entity> Light = core->addEntity();
	Light->addComponent<Renderer>();
	Light->getComponent<Renderer>()->setAlbedo("./Resources/LimeStone/albedo.png");
	Light->getComponent<Renderer>()->setAO("./Resources/LimeStone/ao.png");
	Light->getComponent<Renderer>()->setHeight("./Resources/LimeStone/height.png");
	Light->getComponent<Renderer>()->setNormal("./Resources/LimeStone/normal.png");
	Light->getComponent<Renderer>()->setMetalness("./Resources/LimeStone/metallic.png");
	Light->getComponent<Renderer>()->setRoughnesse("./Resources/LimeStone/roughness.png");
	Light->getComponent<Renderer>()->setModel(core->getCache()->load<Model>("./Resources/Light/Light.obj"));
	Light->getComponent<Transform>()->setScale(0.5f);
	Light->getComponent<Transform>()->setPos(rend::vec3(0.f, 0.0f, 0.0f));
	
	core->start();
	
	return 0;
}