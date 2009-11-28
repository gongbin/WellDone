//
//  SyncManager.m
//  WellDone
//
//  Created by Alex Leutgöb on 28.11.09.
//  Copyright 2009 alexleutgoeb.com. All rights reserved.
//

#import "SyncManager.h"

@interface SyncManager()

@property (nonatomic, retain) NSDictionary *syncServices;

@end



@implementation SyncManager

@synthesize delegate;
@synthesize syncServices;


#pragma mark -
#pragma mark general methods

-(id)initWithDelegate:(id)aDelegate {
	if (self = [self init]) {
		self.delegate = aDelegate;
		self.syncServices = [[NSDictionary alloc] init];
	}
	return self;
}

- (void) dealloc {
	[syncServices release];
	self.delegate = nil;
	[super dealloc];
}



#pragma mark -
#pragma mark sync manager methods

- (void)registerSyncService:(id<GtdApi>)syncService {
	
	if ([(NSObject *)syncService conformsToProtocol:@protocol(GtdApi)] != NO) {
		// syncService is a valid GtdApi implementation
		[syncServices setValue:syncService forKey:[syncService identifier]];
	}
	else {
		// syncService does not conform to protocol, not added
	}
}

@end