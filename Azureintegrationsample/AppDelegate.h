//
//  AppDelegate.h
//  Azureintegrationsample
//
//  Created by user on 13/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "WAAuthenticationCredential.h"
#import "WACloudAccessControlClient.h"

//@class WACloudAccessControlClient;

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>{
    
    WAAuthenticationCredential *authenticationCredential;
	BOOL use_proxy;
}

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) ViewController *viewController;

@property (nonatomic, retain) WAAuthenticationCredential *authenticationCredential;
@property (assign) BOOL use_proxy;



@end
