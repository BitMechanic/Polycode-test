//
// Polycode template. Write your code here.
//

#import "PolycodeView.h"
#include "Polycode.h"
#include "Polycode3DPhysics.h"

using namespace Polycode;

class PolycodeTemplateApp : public EventHandler {
public:
    PolycodeTemplateApp(PolycodeView *view);
    ~PolycodeTemplateApp();
    
    void handleEvent(Event *e);
    bool Update();
    Number walkSpeed, direction, pitch, rotateX, rotateY, strafeSpeed;
private:
    Core *core;
    PhysicsScene *scene;
	PhysicsVehicle *vehicleController;
	ScenePrimitive *testBox;
	ScenePrimitive *vehicle;
    ScenePrimitive *vehicleTracker;
	ScreenLabel *onGroundLabel;
	Number steeringValue;
	Number engineForce;
	bool breaking;
    bool cameraEvent;
    bool upKeys[6];
    Vector3 cameraMove;
    Number cameraTether;
    bool allKeysUp();
};