//
// Polycode template. Write your code here.
// 

#include <iostream>
#include <math.h>
#include "PolycodeTemplateApp.h"
#define moveSpeed 01.00


PolycodeTemplateApp::PolycodeTemplateApp(PolycodeView *view) : EventHandler() {
    
    for (int i = 0; i < 6; i++) {
        upKeys[i] = true;
    }
    
    core = new CocoaCore(view, 1280,768,false,false, 0,0,60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default");

	Screen *hud = new Screen();
	
	onGroundLabel = new ScreenLabel("Arrow keys to control, spacebar to brake, press R to reset car", 16);
	hud->addChild(onGroundLabel);
	
	scene = new PhysicsScene();
    
	ScenePrimitive *ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(-50, 0.0, 0.0);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(50, 0.0, 0.0);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(0.0, 0.0, -50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(-50, 0.0, -50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(50, 0.0, 50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(-50, 0.0, 50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(0.0, 0.0, 50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);
    
    ground = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 50, 50);
	ground->loadTexture("Resources/green_texture.png");
    ground->setPosition(50, 0.0, -50);
	scene->addPhysicsChild(ground, PhysicsSceneEntity::SHAPE_PLANE, 0.0);


    
    
	// Some obstacles
	ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4,4,6);
	box->setPitch(25.0);
	box->setPosition(7,-1.05, 0.0);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);
    
	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4,4,6);
	box->setPitch(25.0);
	box->setPosition(-7,-1.05, 0.0);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);
    
	box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 20,2,5);
	box->setPosition(0.0,1.0, -4.3);
	box->setColor(0.5,0.5,1.0,1.0);
	box->loadTexture("Resources/green_texture.png");
	scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 0.0);
    
	for(int i=0; i < 10; i++) {
		ScenePrimitive *box = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.7,0.7,0.7);
		box->loadTexture("Resources/pink_texture.png");
		box->Roll(-45 + (rand() % 90));
		box->Pitch(-45 + (rand() % 90));
		box->setPosition(-3 + (rand() % 6), 2 + i*0.5, -5 + (rand() % 3));
		scene->addPhysicsChild(box, PhysicsSceneEntity::SHAPE_BOX, 1.0);
	}
    
	// The vehicle
	vehicle = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 1.0,0.5,2.0);
	vehicle->loadTexture("Resources/pink_texture.png");
	vehicle->setColor(1.0, 1.0, 0.0, 1.0);
	vehicle->setPosition(6,1,5);
	vehicleController = scene->addVehicleChild(vehicle, 5.0, 1.0);
    
    
    // A vehicle tracker who's position is updated in the update function, without inheriting physics from vehicle, so that the scene camera can inherit from it without inheriting physics, steering etc.
    vehicleTracker = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.25, 1.0);
    vehicleTracker->setPosition(6,1,5);
    vehicleTracker->addChild(scene->getDefaultCamera());
    
   
    
    
	
	ScenePrimitive *wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(0.6,0,-0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, true);
	scene->addEntity(wheel);
    
	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(-0.6,0,-0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, true);
	scene->addEntity(wheel);
    
	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, false);
	scene->addEntity(wheel);
    
	wheel = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 0.3, 10, 10);
	wheel->loadTexture("Resources/pink_texture.png");
	wheel->setColor(0.0, 1.0, 0.0, 1.0);
	vehicleController->addWheel(wheel, Vector3(-0.6,0,0.5), Vector3(0,-1,0), Vector3(-1,0,0), 0.2,  0.3, false);
	scene->addEntity(wheel);
	
	steeringValue = 0;
	engineForce = 0;
	breaking = false;
	
	testBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4, 4, 4);
	testBox->loadTexture("Resources/pink_texture.png");
	testBox->setColor(0.3,0.5, 1.0,0.4);
	testBox->setPosition(-5,2,7);
	scene->addCollisionChild(testBox, PhysicsSceneEntity::SHAPE_BOX);
	
	scene->getDefaultCamera()->setPosition(15,15,15);
	scene->getDefaultCamera()->lookAtEntity(vehicle);
    
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);
}

void PolycodeTemplateApp::handleEvent(Event *e) {
	if(e->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
                    case KEY_a:// On every camera movement key press, change cameraEvent bool to true and change the cameraMove vector to point in the direction of the movement
                        cameraEvent = true;
                        cameraMove = Vector3(-1.0, 0.0, 0.0);
                        break;
                        
                    case KEY_d:
                        cameraEvent = true;
                        cameraMove = Vector3(1.0, 0.0, 0.0);
                        break;
                        
                    case KEY_s:
                        cameraEvent = true;
                        cameraMove = Vector3(0.0, 0.0, 1.0);
                        break;
                        
                    case KEY_w:
                        cameraEvent = true;
                        cameraMove = Vector3(0.0, 0.0, -1.0);
                        break;
                        
                    case KEY_q:
                        cameraEvent = true;
                        cameraMove = Vector3(0.0, 1.0, 0.0);
                        break;
                        
                    case KEY_e:
                        cameraEvent = true;
                        cameraMove = Vector3(0.0, -1.0, 0.0);
                        break;
                        
					case KEY_r:
						vehicleController->warpVehicle(Vector3(6,1,5));
                        break;
                        
					case KEY_UP:
						engineForce = -15;
                        break;
                        
					case KEY_DOWN:
						engineForce = 15;
                        break;
                        
					case KEY_LEFT:
						steeringValue = 0.5;
                        break;
                        
					case KEY_RIGHT:
						steeringValue = -0.5;
                        break;
                        
					case KEY_SPACE:
						breaking = true;
                        break;
				}
                break;
                
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
                        
					case KEY_UP:
					case KEY_DOWN:
						engineForce = 0;
                        break;
					case KEY_LEFT:
					case KEY_RIGHT:
						steeringValue = 0.0;
                        break;
					case KEY_SPACE:
						breaking = false;
                        break;
                    case KEY_a:
                        upKeys[0] = true;
                        if (allKeysUp()) {// on every key up for the camera movements, use allKeysUp function to check if they are all up
                            cameraEvent = false;// if they are set cameraEvent bool to false
                        }
                        break;
                    case KEY_d:
                        upKeys[1] = true;
                        if (allKeysUp()) {
                            cameraEvent = false;
                        }
                        break;
                    case KEY_s:
                        upKeys[2] = true;
                        if (allKeysUp()) {
                            cameraEvent = false;
                        }
                        break;
                    case KEY_w:
                        upKeys[3] = true;
                        if (allKeysUp()) {
                            cameraEvent = false;
                        }
                        break;
                    case KEY_q:
                        upKeys[4] = true;
                        if (allKeysUp()) {
                            cameraEvent = false;
                        }
                        break;
                    case KEY_e:
                        upKeys[5] = true;
                        if (allKeysUp()) {
                            cameraEvent = false;
                        }
                        break;
				}
                break;
		}
		
	}
}

bool PolycodeTemplateApp::allKeysUp() {// Function to check if all the camera movement keys are currently up
    for (int i = 0; i < 6; i++) {
        if (!upKeys[i]) {
            return false;
        }
    }
    return true;
}

PolycodeTemplateApp::~PolycodeTemplateApp() {
}

bool PolycodeTemplateApp::Update() {
    
    bool update = core->Update();
    
    Vector3 pCam = scene->getDefaultCamera()->getPosition();
    Camera *cam = scene->getDefaultCamera();
	
	if(breaking) {
		vehicleController->setBrake(20, 2);
		vehicleController->setBrake(20, 3);
		vehicleController->applyEngineForce(0, 2);
		vehicleController->applyEngineForce(0, 3);
	} else {
		vehicleController->setBrake(0, 2);
		vehicleController->setBrake(0, 3);
		vehicleController->applyEngineForce(engineForce, 2);
		vehicleController->applyEngineForce(engineForce, 3);
	}
	
	vehicleController->setSteeringValue(steeringValue, 0);
	vehicleController->setSteeringValue(steeringValue, 1);
	
	CollisionResult res = scene->testCollision(vehicle, testBox);
	if(res.collided) {
		testBox->setColor(1.0,1.0,0.0,0.5);
	} else {
		testBox->setColor(0.0,1.0,1.0,0.5);
	}
    
    if (!steeringValue == 0.0) {// Move the camera to compensate for yaw of the vehicle when turning, not supposed to keep the camera precisely behind the vehicle, player can use wasd keys to make further compensations
        Vector3 camPos = cam->getPosition();
        Vector3 carPos = vehicle->getPosition();
        Number xs = (camPos.x - carPos.x) * (camPos.x - carPos.x);
        Number ys = (camPos.y - carPos.y) * (camPos.y - carPos.y);
        Number zs = (camPos.z - carPos.z) * (camPos.z - carPos.z);
        Number dist = xs + ys + zs; // Find the distance between the car and the camera
        
        if (engineForce < 0.0) {
            if (steeringValue < 0.0) {// camera adjustment for forward direction
                Vector3 turnL = Vector3(-0.001, 0.0, 0.0);
                turnL = cam->getConcatenatedMatrix().rotateVector(turnL);
                pCam = pCam + (turnL * dist);
                cam->setPosition(pCam);// adjust the camera so that it stays roughly behind the vehicle.
            } else {
                Vector3 turnR = Vector3(0.001, 0.0, 0.0);
                turnR = cam->getConcatenatedMatrix().rotateVector(turnR);
                pCam = pCam + (turnR * dist);
                cam->setPosition(pCam);
            }
        }
        if (engineForce > 0.0) {
            if (steeringValue < 0.0) {// reverse camera adjustment for reverse direction
                Vector3 turnL = Vector3(0.001, 0.0, 0.0);
                turnL = cam->getConcatenatedMatrix().rotateVector(turnL);
                pCam = pCam + (turnL * dist);
                cam->setPosition(pCam);
            } else {
                Vector3 turnR = Vector3(-0.001, 0.0, 0.0);
                turnR = cam->getConcatenatedMatrix().rotateVector(turnR);
                pCam = pCam + (turnR * dist);
                cam->setPosition(pCam);
            }
        }
    }
    
    
    
    if(cameraEvent) {// If true then change camera position relative to the vehicle, in the direction of the key press
        Vector3 dirVector = cameraMove;
        dirVector = cam->getConcatenatedMatrix().rotateVector(dirVector);
        pCam = pCam + (dirVector * moveSpeed);
        cam->setPosition(pCam);
    }
    
    vehicleTracker->setPosition(vehicle->getPosition());// set position of vehicle tracker, which the camera is a child of. Keeps the camera at the right distance to the vehicle. 
    
    
    // use a quat etc to keep the camera centered on the vehicle
    Vector3 vpos = vehicle->getPosition();
    Matrix4 rotatecam = cam->getLookAtMatrix(vpos);
    Quaternion rotateQ;
    rotateQ.createFromMatrix(rotatecam);
    cam->setRotationQuat(rotateQ.w, rotateQ.x, rotateQ.y, rotateQ.z);
    
    core->Render();
    
    return update;
}