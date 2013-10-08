//
//  PolycodeTestAppDelegate.h
//  PolycodeTest
//
//  Created by Robbie on 05/10/2013.
//  Copyright (c) 2013 Tomatogon. All rights reserved.
//

#ifndef PolycodeTest_PolycodeTestAppDelegate_h
#define PolycodeTest_PolycodeTestAppDelegate_h

#import <Cocoa/Cocoa.h>
#import "PolycodeView.h"
#include "game.h"

@interface PolycodeTestAppDelegate : NSObject <NSApplicationDelegate> {
@private
	NSWindow *window;
	PolycodeView *mainView;
    Game *app;
    NSTimer *timer;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet PolycodeView *mainView;

@end


#endif
