//
//  ViewController.m
//  Azureintegrationsample
//
//  Created by user on 13/06/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

#import "WATableFetchRequest.h"
#import "WAConfiguration.h"

#import "AppDelegate.h"
@interface ViewController ()

@end

@implementation ViewController
@synthesize resultContinuation=_resultContinuation;
@synthesize localEntityList = _localEntityList;
- (void)viewDidLoad
{
    
    [super viewDidLoad];
   	WAConfiguration *config = [WAConfiguration sharedConfiguration];	
	// Do any additional setup after loading the view, typically from a nib.
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.authenticationCredential = [WAAuthenticationCredential credentialWithAzureServiceAccount:config.accountName 
                                                                                               accessKey:config.accessKey];    
    
    storageClient = [[WACloudStorageClient storageClientWithCredential:appDelegate.authenticationCredential] retain];
	storageClient.delegate = self;
    
      _localEntityList = [[NSMutableArray alloc] initWithCapacity:20];
       
    
}


-(IBAction)azure:(id)sender{
    
    WATableFetchRequest *fetchRequest = [WATableFetchRequest fetchRequestForTable:@"Your Table Name here"];
    fetchRequest.resultContinuation = self.resultContinuation;
    fetchRequest.topRows = 20;
    [storageClient fetchEntitiesWithRequest:fetchRequest];
    
}

- (void)storageClient:(WACloudStorageClient *)client didFetchEntities:(NSArray *)entities fromTableNamed:(NSString *)tableName withResultContinuation:(WAResultContinuation *)resultContinuation
{
  
    NSMutableArray *array = [[NSMutableArray alloc]init];
    for (int i = 0;  i < [entities count]; i++)
    {
        WATableEntity *aaa = [entities objectAtIndex:i];
        NSArray *keys = [aaa keys];
        
        NSMutableDictionary *data = [[NSMutableDictionary alloc]init];
        
        for (int j = 0 ; j < [keys count]; j++) 
        {
            NSString *value;
            NSString *key = [keys objectAtIndex:j];
            value = [aaa objectForKey:key];
            [data setValue:value forKey:key];
        }
        [array addObject:data];
    }
    NSLog(@"datas  %@",array);
    
    
   // self.resultContinuation = resultContinuation;
    [self.localEntityList addObjectsFromArray:entities];
//    
   contents=[[self.localEntityList objectAtIndex:0] description];
//   
//    
   NSLog(@"   kkkk %@",contents);
//    
//    
//    
//    
 vieww.text=contents;
    
    
//    NSLog(@"haii%@",[self.localEntityList objectAtIndex:0]);
}




- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
