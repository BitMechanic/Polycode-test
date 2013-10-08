//
//  PolycodeTestAppDelegate.cpp
//  PolycodeTest
//
//  Created by Robbie on 05/10/2013.
//  Copyright (c) 2013 Tomatogon. All rights reserved.
//

#include "PolycodeTestAppDelegate.h"


@implementation PolycodeTestAppDelegate

@synthesize window;
@synthesize mainView;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	app = new Game(mainView);
	timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f)
                                    target:self
                                  selector:@selector(animationTimer:)
                                  userInfo:nil
                                   repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSEventTrackingRunLoopMode];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}

- (void)animationTimer:(NSTimer *)timer
{
	if(!app->Update()) {
		[[NSApplication sharedApplication] stop:self];
	}
}

@end
