//
//  ViewController.h
//  Azureintegrationsample
//
//  Created by user on 13/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "WACloudStorageClientDelegate.h"

#import "WACloudStorageClient.h"
#import "WATableEntity.h"
#import "WAResultContinuation.h"

#import "WACloudStorageClient.h"
#import "WACloudStorageClientDelegate.h"
#import "WATableFetchRequest.h"

#import "WAAuthenticationCredential.h"
#import "WACloudAccessControlClient.h"
#import "WACloudAccessToken.h"




@interface ViewController : UIViewController<WACloudStorageClientDelegate,UITabBarDelegate>{
    
    IBOutlet UITabBar *myTabBar;
    IBOutlet UITextView *vieww;
    
    NSString *contents;
@private
	WACloudStorageClient *storageClient;
    
     WAResultContinuation *_resultContinuation;
    
  
    
    
}
@property (nonatomic, retain) WAResultContinuation *resultContinuation;
@property (nonatomic, retain) NSMutableArray *localEntityList;


-(IBAction)azure:(id)sender;
@end
