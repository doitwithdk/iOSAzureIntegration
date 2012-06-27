/*
 Copyright 2010 Microsoft Corp
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>

@class WACloudStorageClient;
@class WAResultContinuation;
@class WABlobContainer;
@class WABlob;
@class WAQueueMessage;
@class WATableEntity;

/**
 The WACloudStorageClientDelegate protocol defines methods that a delegate of WACloudStorageClient object can optionally implement when a request is made.
 */
@protocol WACloudStorageClientDelegate <NSObject>

@optional

///---------------------------------------------------------------------------------------
/// @name Request Completion
///---------------------------------------------------------------------------------------

/**
 Sent if a URL request failed.
 
 @param client The client that sent the request.
 @param request The request that failed.
 @param error The error that occurred.
 */
- (void)storageClient:(WACloudStorageClient *)client didFailRequest:(NSURLRequest*)request withError:(NSError *)error;

///---------------------------------------------------------------------------------------
/// @name Blob Request Completion
///---------------------------------------------------------------------------------------

/**
 Sent when the client successfully returns a list of blob containers.
 
 @param client The client that sent the request.
 @param containers The array of WABlobContainer objects returned from the request.
 
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobContainers:(NSArray *)containers DEPRECATED_ATTRIBUTE;

/**
 Sent when the client successfully returns a list of blob containers and the result continuation that you can use when making future requests to get the next set of containers. 
 
 @param client The client that sent the request.
 @param containers The array of WABlobContainer objects returned from the request.
 @param resultContinuation The result continuation that contains the marker to use for the next request.
 
 @see WABlobContainer
 @see WAResultContinuation
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobContainers:(NSArray *)containers withResultContinuation:(WAResultContinuation *)resultContinuation;

/**
 Sent when the client successfully returns a blob container.
 
 @param client The client that sent the request.
 @param container The container the client requested.
 
 @see WABlobContainer
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobContainer:(WABlobContainer *)container;

/**
 Sent when the client successsfully adds a new blob container.
 
 @param client The client that sent the request.
 @param name The name that was added.
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didAddBlobContainerNamed:(NSString *)name DEPRECATED_ATTRIBUTE;

/**
 Sent when the client successsfully adds a new blob container.
 
 @param client The client that sent the request.
 @param container The container that was added.
 */
- (void)storageClient:(WACloudStorageClient *)client didAddBlobContainer:(WABlobContainer *)container;

/**
 Sent when the client successfully removes an existing blob container.
 
 @param client The client that sent the request.
 @param container The container that was deleted.
 
 @see WABlobContainer
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteBlobContainer:(WABlobContainer *)container;

/**
 Sent when the client successfully removes an existing blob container.
 
 @param client The client that sent the request.
 @param name The name of the container that was deleted.
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteBlobContainerNamed:(NSString *)name;

/**
 Sent when the client successfully returns blobs from an existing container.
 
 @param client The client that sent the request.
 @param blobs The array of WABlob objects returned from the request.
 @param container The WABlobContainer object for the blobs.
 
 @deprecated Now use WACloudStorageClientDelegate#storageClient:didFetchBlobs:inContainer:withResultContinuation:
 
 @see WABlob
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobs:(NSArray *)blobs inContainer:(WABlobContainer *)container DEPRECATED_ATTRIBUTE;

/**
 Sent when the client successfully returns blobs from an existing container.
 
 @param client The client that sent the request.
 @param blobs The array of WABlob objects returned from the request.
 @param container The WABlobContainer object for the blobs.
 @param resultContinuation The result continuation that contains the marker to use for the next request.
 
 @see WABlob
 @see WABlobContainer
 @see WAResultContinuation
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobs:(NSArray *)blobs inContainer:(WABlobContainer *)container withResultContinuation:(WAResultContinuation *)resultContinuation;

/**
 Sent when the client successfully returns blob data for a given blob.
 
 @param client The client that sent the request.
 @param data The data for the blob.
 @param blob The blob for the the data.
 
 @see WABlob
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobData:(NSData *)data blob:(WABlob *)blob;

/**
 Sent when the client successfully returns blob data for a given URL.
 
 @param client The client that sent the request.
 @param data The data for the blob.
 @param URL The URL for the the data.
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchBlobData:(NSData *)data URL:(NSURL *)URL;

/**
 Sent when the client successfully adds a blob to a specified container.
 
 @param client The client that sent the request.
 @param container The container to add the blob.
 @param blobName The name of the blob
 
 @warning *Deprecated*: now use WACloudStorageClientDelegate#storageClient:didAddBlob:toContainer:
 
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didAddBlobToContainer:(WABlobContainer *)container blobName:(NSString *)blobName DEPRECATED_ATTRIBUTE;


/**
 Sent when the client successfully adds a blob to a specified container.
 
 @param client The client that sent the request.
 @param blob The blob added.
 @param container The container the blob was added.
 
 @see WABlobContainer
 */
- (void)storageClient:(WACloudStorageClient *)client didAddBlob:(WABlob *)blob toContainer:(WABlobContainer *)container;

/**
 Sent when the client successfully deletes a blob.
 
 @param client The client that sent the request.
 @param blob The blob that was deleted.
 
 @see WABlob
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteBlob:(WABlob *)blob;

///---------------------------------------------------------------------------------------
/// @name Queue Request Completion
///---------------------------------------------------------------------------------------

/**
 Sent when the client successfully returns a list of queues.
 
 @param client The client that sent the request
 @param queues An array of WAQueue objects.
 
 @deprecated Now use WACloudStorageClientDelegate#storageClient:didFetchQueues:withResultContinuation:
 
 @see WAQueue
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didFetchQueues:(NSArray *)queues DEPRECATED_ATTRIBUTE;

/**
 Sent when the client successfully returns a list of queues with a result continuation.
 
 @param client The client that sent the request
 @param queues An array of WAQueue objects.
 @param resultContinuation The result continuation that contains the marker to use for the next request.
 
 @see WAQueue
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchQueues:(NSArray *)queues withResultContinuation:(WAResultContinuation *)resultContinuation;

/**
 Sent when the client successfully adds a queue.
 
 @param client The client that sent the request
 @param queueName The name of the queue that was added.
 */
- (void)storageClient:(WACloudStorageClient *)client didAddQueueNamed:(NSString *)queueName;

/**
 Sent when the client successfully removes an existing queue.
 
 @param client The client that sent the request.
 @param queueName The name of the queue that was deleted.
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteQueueNamed:(NSString *)queueName;

/**
 Sent when the client successfully get messages from the specified queue.
 
 @param client The client that sent the request.
 @param queueMessages An array of WAQueue objects.
 
 @see WAQueueMessage
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchQueueMessages:(NSArray *)queueMessages;

/**
 Sent when the client successfully got a single message from the specified queue
 
 @param client The client that sent the request.
 @param queueMessage The message that was fetched.
 
 @see WAQueueMessage
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchQueueMessage:(WAQueueMessage *)queueMessage;

/**
 Sent when the client successfully peeked a single message from the specified queue.
 
 @param client The client that sent the request. 
 @param queueMessage The message that was fetched.
 
 @see WAQueueMessage
 */
- (void)storageClient:(WACloudStorageClient *)client didPeekQueueMessage:(WAQueueMessage *)queueMessage;

/*!  */
/**
 Sent when the client successfully peeked messages from the specified queue.
 
 @param client The client that sent the request.
 @param queueMessages An array of WAQueueMessage objects.
 
 @see WAQueueMessage
 */
- (void)storageClient:(WACloudStorageClient *)client didPeekQueueMessages:(NSArray *)queueMessages;

/**
 Sent when the client successfully delete a message from the specified queue
 
 @param client The client that sent the request.
 @param queueMessage The message that was deleted.
 @param queueName The name of the queue where the message was deleted.
 
 @see WAQueueMessage
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteQueueMessage:(WAQueueMessage *)queueMessage queueName:(NSString *)queueName;

/**
 Sent when the client successfully put a message into the specified queue.
 
 @param client The client that sent the request.
 @param message The message that was added.
 @param queueName The name of the queue that the message was added.
 */
- (void)storageClient:(WACloudStorageClient *)client didAddMessageToQueue:(NSString *)message queueName:(NSString *)queueName;

///---------------------------------------------------------------------------------------
/// @name Table Request Completion
///---------------------------------------------------------------------------------------

/**
 Sent when the client successfully returns a list of tables.
 
 @param client The client that sent the request.
 @param tables An array of NSString objects that are the names of the tables.
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchTables:(NSArray *)tables;

/**
 Sent when the client successfully returns a list of tables with a continuation.
 
 @param client The client that sent the request.
 @param tables An array of NSString objects that are the names of the tables.
 @param resultContinuation The result continuation that contains the marker to use for the next request.
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchTables:(NSArray *)tables withResultContinuation:(WAResultContinuation *)resultContinuation;

/**
 Sent when the client successfully creates a table.
 
 @param client The client that sent the request.
 @param tableName The table name that was created.
 */
- (void)storageClient:(WACloudStorageClient *)client didCreateTableNamed:(NSString *)tableName;

/**
 Sent when the client successfully deletes a specified table.
 
 @param client The client that sent the request.
 @param tableName The table name that was deleted.
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteTableNamed:(NSString *)tableName;

/**
 Sent when the client successfully returns a list of entities from a table.
 
 @param client The client that sent the request.
 @param entities An array of WATableEntity objects.
 @param tableName The name of the table that contains the enties.
 
 @deprecated Now use WACloudStorageClientDelegate#storageClient:didFetchEntities:fromTableNamed:withResultContinuation:
 
 @see WATableEntity
 */
// TODO: Remove this before release
- (void)storageClient:(WACloudStorageClient *)client didFetchEntities:(NSArray *)entities fromTableNamed:(NSString *)tableName DEPRECATED_ATTRIBUTE;

/**
 Sent when the client successfully returns a list of entities from a table.
 
 @param client The client that sent the request.
 @param entities An array of WATableEntity objects.
 @param tableName The table name that contains the entities.
 @param resultContinuation The result continuation that contains the marker to use for the next request.
 
 @see WAResultContinuation
 @see WATableEntity
 */
- (void)storageClient:(WACloudStorageClient *)client didFetchEntities:(NSArray *)entities fromTableNamed:(NSString *)tableName withResultContinuation:(WAResultContinuation *)resultContinuation;

/**
 Sent when the client successfully inserts an entity into a table.
 
 @param client The client that sent the request.
 @param entity The entity that was inserted.
 
 @see WATableEntity
 */
- (void)storageClient:(WACloudStorageClient *)client didInsertEntity:(WATableEntity *)entity;

/**
 Sent when the client successfully updates an entity within a table.
 
 @param client The client that sent the request.
 @param entity The entity that was updated.
 
 @see WATableEntity
 */
- (void)storageClient:(WACloudStorageClient *)client didUpdateEntity:(WATableEntity *)entity;

/**
 Sent when the client successfully merges an entity within a table.
 
 @param client The client that sent the request.
 @param entity The entity that was merged.
 
 @see WATableEntity
 */
- (void)storageClient:(WACloudStorageClient *)client didMergeEntity:(WATableEntity *)entity;

/**
 Sent when the client successfully deletes an entity from a table.
 
 @param client The client that sent the request.
 @param entity The entity that was deleted.
 
 @see WATableEntity
 */
- (void)storageClient:(WACloudStorageClient *)client didDeleteEntity:(WATableEntity *)entity;

@end
