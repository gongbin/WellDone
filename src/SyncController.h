//
//  SyncController.h
//  WellDone
//
//  Created by Alex Leutgöb on 12.12.09.
//  Copyright 2009 alexleutgoeb.com. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class SyncController, SyncManager;


/**
 SyncControllerDelegate protocol provides callback methods for communicating with 
 a delegate while syncing.
 */
@protocol SyncControllerDelegate <NSObject>

@optional

/**
 Callback method for notifying the delegate about a successful sync.
 @param sc the sync controller instance
 */
- (void)syncControllerDidSyncWithSuccess:(SyncController *)sc;

/**
 Callback method for notifying the delegate about conflicts in sync.
 @param sc the sync controller instance
 @param conflicts An array with TaskContainer objects representing sync conflicts.
 */
- (void)syncControllerDidSyncWithConflicts:(SyncController *)sc conflicts:(NSArray *)conflicts;

/**
 Callback method for notifying the delegate about an error while syncing.
 @param sc the sync controller instance
 @param error the emerged error during syncing
 */
- (void)syncController:(SyncController *)sc didSyncWithError:(NSError *)error;

@end


/**
 Enum for sync controller states
 */
typedef enum {
	SyncControllerReady = 0,
	SyncControllerBusy,
	SyncControllerOffline,
	SyncControllerFailed,
	SyncControllerInit
} SyncControllerState;


/**
 SyncController class
 The class is the main class for enabling services and trigger a sync.
 */
@interface SyncController : NSObject {
@private
	// Delegate for sync controller instance
	id<SyncControllerDelegate> delegate;
	
	// List of available sync services
	NSMutableDictionary *syncServices;
	// Instance of the syncmanager
	SyncManager *syncManager;
	
	// queue for sync operations
	NSOperationQueue *syncQueue;
	
	// counter for active services
	NSInteger activeServicesCount;
	
	// SyncControllerState
	SyncControllerState status;
}


/**
 Getter and setter for delegate object
 */
@property (nonatomic, assign) id<SyncControllerDelegate> delegate;

/**
 Getter for a list of all available sync services.
 */
@property (nonatomic, readonly) NSMutableDictionary *syncServices;

/**
 Returns the number of available sync services.
 */
@property (nonatomic, readonly) NSInteger servicesCount;

/**
 Returns the number of active sync services.
 */
@property (nonatomic, readonly) NSInteger activeServicesCount;

/**
 Getter and setter for last sync date string
 */
@property (nonatomic, readonly) NSString *lastSyncText;

/**
 Getter and setter fot synccontroller state property
 */
@property (nonatomic, assign) SyncControllerState status;


/**
 Custom initializer for setting the delegate.
 Initializes a new SyncController object with the given delegate. The delegate 
 must implement the SyncControllerDelegate protocol and is used to inform about 
 the  sync process.
 @param aDelegate		the delegate to be set
 @return				the initialized object, or nil if an error occured
 */
- (id)initWithDelegate:(id<SyncControllerDelegate>)aDelegate;

/**
 Enables a syncService in the sync controller.
 @param anIdentifier specific syncService identifer to enable
 @param aUser username for login
 @param aPwd password for login
 @param anError error object if enabling the service failed
 */
- (BOOL)enableSyncService:(NSString *)anIdentifier withUser:(NSString *)aUser pwd:(NSString *)aPwd error:(NSError **)anError;

/**
 Disables a specific syncService in the sync controller.
 @param anIdentifier the specific syncService identifiert to disable
 */
- (BOOL)disableSyncService:(NSString *)anIdentifier;

/**
 Starts the sync in background. Notifications about success and failures will be 
 sent through the sync controller delegate.
 */
- (void)sync;

@end
