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

/**
 The key in an NSError object that has the status code / error code from Windows Azure.
 
 @see http://msdn.microsoft.com/en-us/library/windowsazure/dd179382.aspx
 */
extern NSString * const WAErrorReasonCodeKey;

@class WAAuthenticationCredential;
@class WABlob;
@class WABlobContainer;
@class WATableEntity;
@class WATable;
@class WAQueueMessage;
@class WATableFetchRequest;
@class WABlobFetchRequest;
@class WABlobContainerFetchRequest;
@class WAQueueFetchRequest;
@class WAQueueMessageFetchRequest;
@class WAResultContinuation;

@protocol WACloudStorageClientDelegate;

/**
 The cloud storage client is used to invoke operations on, and return data from, Windows Azure storage. 
 */
@interface WACloudStorageClient : NSObject
{
@private
	WAAuthenticationCredential* _credential;
	id<WACloudStorageClientDelegate> _delegate;
}

///---------------------------------------------------------------------------------------
/// @name Setting the Delegate
///---------------------------------------------------------------------------------------

/**
 The delegate is sent messages when content is loaded or errors occur from Windows Azure storage.
 */
@property (assign) id<WACloudStorageClientDelegate> delegate;

///---------------------------------------------------------------------------------------
/// @name Managing Certificates
///---------------------------------------------------------------------------------------

/**
 Ignores any ssl errors from the given host. This is useful when using a self signed certificate.
 
 @param host The host to ignore errors.
 */
+ (void)ignoreSSLErrorFor:(NSString *)host;

#pragma mark - Blob Operations
///---------------------------------------------------------------------------------------
/// @name Blob Operations
///---------------------------------------------------------------------------------------

/**
 Fetch a list of blob containers asynchronously. 
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:]. There could be a limit to the number of containers that are returned. If you have many containers you may want to use the continuation version of fetching the containers.
 
 @warning *Deprecated*: now use fetchBlobContainersWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:]
 */
// TODO: Remove this before release
- (void)fetchBlobContainers DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of blob containers asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will contain the array of WABlobContainer objects or an error if one occurs. There could be a limit to the number of containers that are returned. If you have many containers you may want to use the continuation version of fetching the containers.
 
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchBlobContainersWithRequest:usingCompletionHandler:.
 
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)fetchBlobContainersWithCompletionHandler:(void (^)(NSArray *containers, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of blob containers asynchronously using continuation.
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:withResultContinuation:].
 
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of containers to reuturn for this fetch.
 
 @warning *Deprecated*: now use fetchBlobContainersWithRequest:
 
 @see WAResultContinuation
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:withResultContinuation:]
 */
// TODO: Remove this before release
- (void)fetchBlobContainersWithContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of blob containers asynchronously using continuation with a block.
 
 The method will run asynchronously and will call back through the block. The block will contain the array of WABlobContainer objects or an error if one occurs. The WAResultContinuation returned in the block can be used to call this method again to get the next set of containers.
 
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of containers to reuturn for this fetch.
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchBlobContainersWithRequest:usingCompletionHandler:
 
 @see WAResultContinuation
 */
// TODO: Remove this before release
- (void)fetchBlobContainersWithContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult usingCompletionHandler:(void (^)(NSArray *containers, WAResultContinuation *resultContinuation, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of blob containers asynchronously using a fetch request.
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:withResultContinuation:].
 
 @param fetchRequest The fetch request for the containers.
 
 @see WABlobContainerFetchRequest
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobContainers:withResultContinuation:]
 */
- (void)fetchBlobContainersWithRequest:(WABlobContainerFetchRequest *)fetchRequest;

/**
 Fetch a list of blob containers asynchronously using fetch request with a block.
 
 The method will run asynchronously and will call back through the block. The block will contain the array of WABlobContainer objects or an error if one occurs. The WAResultContinuation returned in the block can be used to call this method again to get the next set of containers.
 
 @param fetchRequest The fetch request for the containers.
 @param block A block object called with the results of the fetch.
 
 @see WABlobContainerFetchRequest
 @see WAResultContinuation
 */
- (void)fetchBlobContainersWithRequest:(WABlobContainerFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *containers, WAResultContinuation *resultContinuation, NSError *error))block;

/**
 Fetch a blob container by name asynchronously.
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobContainer:].
 
 @param containerName The name of the container to fetch.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobContainer:]
 */
- (void)fetchBlobContainerNamed:(NSString *)containerName;

/**
 Fetch a blob container by name asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will contain the WABlobContainer object or an error if one occurs. 
 
 @param containerName The name of the container to fetch.
 @param block A block object called with the results of the fetch.

 @see WABlobContainer
 */
- (void)fetchBlobContainerNamed:(NSString *)containerName withCompletionHandler:(void (^)(WABlobContainer *container, NSError *error))block;

/**
 Adds a named blob container asynchronously.
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didAddBlobContainerNamed:].

 @param containerName The container name to add.

 @returns Returns if the request was sent or not.
 
 @warning *Deprecated*: now use addBlobContainer:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didAddBlobContainerNamed:]
 */
// TODO: Remove this before release
- (BOOL)addBlobContainerNamed:(NSString *)containerName  DEPRECATED_ATTRIBUTE;

/**
 Adds a named blob container asynchronously using a block.
	
 The method will run asynchronously and will call back through the block. The block wil contain an error if one occurred or nil.
 
 @param containerName The container name to add.
 @param block A block object called with the results of the add.
	
 @returns Returns if the request was sent or not.
 
 @warning *Deprecated*: now use addBlobContainer:withCompletionHandler:
 */
// TODO: Remove this before release
- (BOOL)addBlobContainerNamed:(NSString *)containerName withCompletionHandler:(void (^)(NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Adds a named blob container asynchronously.
 
 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didAddBlobContainer:]. 
 
 @param container The container to add.
 
 @returns Returns if the request was sent or not.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didAddBlobContainer:]
 */
- (BOOL)addBlobContainer:(WABlobContainer *)container;

/**
 Adds a named blob container asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block wil contain an error if one occurred or nil.
 
 @param container The container  to add.
 @param block A block object called with the results of the add.
 
 @returns Returns if the request was sent or not.
 */
- (BOOL)addBlobContainer:(WABlobContainer *)container withCompletionHandler:(void (^)(NSError*))block;

/**
 Deletes a specified blob container asynchronously.

 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didDeleteBlobContainerNamed:].
 
 @param container The container to delete.
	
 @returns Returns if the request was sent or not.
 
 @see WABlobContainer
 @see [WACloudStorageClientDelegate storageClient:didDeleteBlobContainerNamed:]
 */
- (BOOL)deleteBlobContainer:(WABlobContainer *)container;

/**
 Deletes a specified blob container asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will return an error if there was an error or nil if not.
 
 @param container The container to delete.
 @param block A block object called with the results of the delete.
	
 @returns Returns if the request was sent or not.
 
 @see WABlobContainer
 */
- (BOOL)deleteBlobContainer:(WABlobContainer *)container withCompletionHandler:(void (^)(NSError *error))block;

/**
 Deletes a specified named blob container asynchronously.

 The method will run asynchronously and will call back through the delegate set for the client using [WACloudStorageClientDelegate storageClient:didDeleteBlobContainerNamed:].
 
 @param containerName The name of the container to delete.
	
 @returns Returns if the request was sent or not.
 
 @warning *Deprecated*: now use deleteBlobContainer:.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteBlobContainerNamed:]
 */
// TODO: Remove this before release
- (BOOL)deleteBlobContainerNamed:(NSString *)containerName DEPRECATED_ATTRIBUTE;

/**
 Deletes a specified named blob container asynchronously with a block.
	
 The method will run asynchronously and will call back through the block. The block will return an error if there was an error or nil if not.
 
 @param containerName The name of the container to delete.
 @param block A block object called with the results of the delete.
 
 @returns Returns if the request was sent or not.
 
 @warning *Deprecated*: now use deleteBlobContainer:withCompletionHandler:
 */
// TODO: Remove this before release
- (BOOL)deleteBlobContainerNamed:(NSString *)containerName withCompletionHandler:(void (^)(NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch the blobs for the specified blob container asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:]. There could be a limit to the number of blobs that are returned. If you have many blobs, you may want to use the continuation version of fetching the blobs.
 
 @param container The container for the blobs to fetch.
 
 @warning *Deprecated*: now use fetchBlobsWithRequest:.
 
 @see delegate
 @see fetchBlobsWithContinuation:resultContinuation:maxResult:
 @see WABlobContainer
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:]
 */
// TODO: Remove this before release
- (void)fetchBlobs:(WABlobContainer *)container DEPRECATED_ATTRIBUTE;

/**
 Fetch the blobs for the specified blob container asynchronously with a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an array of WABlob objects or an error if the request failed. There could be a limit to the number of blobs that are returned. If you have many blobs, you may want to use the continuation version of fetching the blobs.
 
 @param container The container for the blobs to fetch.
 @param block A block object called with the results of the delete.
 
 @warning *Deprecated*: now use fetchBlobsWithRequest:usingCompletionHandler:.
 
 @see fetchBlobsWithContinuation:resultContinuation:maxResult:usingCompletionHandler:
 @see WABlobContainer
 @see WABlob
 */
// TODO: Remove this before release
- (void)fetchBlobs:(WABlobContainer *)container withCompletionHandler:(void (^)(NSArray *blobs, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch the blobs for the specified blob container asynchronously using continuation.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:withResultContinuation:]. The continuation token contains the next marker to use or nil if this is the first request.
 
 @param container The container for the blobs to fetch.
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of blobs to reuturn for this fetch.

 @warning *Deprecated*: now use fetchBlobsWithRequest:.
 
 @see WAResultContinuation
 @see WABlobContainer
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:withResultContinuation:]
 */
// TODO: Remove this before release
- (void)fetchBlobsWithContinuation:(WABlobContainer *)container resultContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult DEPRECATED_ATTRIBUTE;

/**
 Fetch the blobs for the specified blob container asynchronously using continuation with a block.
 
 The method will run asynchronously and will call back through the block. The block will return an arry of WABlob objects if the request succeeds or an error if it fails. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param container The container for the blobs to fetch.
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of blobs to reuturn for this fetch.
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchBlobsWithRequest:usingCompletionHandler:
 
 @see WABlobContainer
 @see WAResultContinuation
 */
// TODO: Remove this before release
- (void)fetchBlobsWithContinuation:(WABlobContainer *)container resultContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult usingCompletionHandler:(void (^)(NSArray *blobs, WAResultContinuation *resultContinuation, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch the blobs for the specified blob container asynchronously using continuation.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:withResultContinuation:]. The continuation token contains the next marker to use or nil if this is the first request.
 
 @param fetchRequest A fetch request that specifies the search criteria for the fetch.
 
 @see WABlobFetchRequest
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobs:inContainer:withResultContinuation:]
 */
- (void)fetchBlobsWithRequest:(WABlobFetchRequest *)fetchRequest;

/**
 Fetch the blobs for the specified blob container asynchronously using continuation with a block.
 
 The method will run asynchronously and will call back through the block. The block will return an arry of WABlob objects if the request succeeds or an error if it fails. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param fetchRequest A fetch request that specifies the search criteria for the fetch.
 @param block A block object called with the results of the fetch.
 
 @see WABlobFetchRequest
 @see WAResultContinuation
 */
- (void)fetchBlobsWithRequest:(WABlobFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *blobs, WAResultContinuation *resultContinuation, NSError *error))block;

/**
 Fetch the blob data for the specified blob asynchronously.

 The method will run asynchronously and will call back through the delegate for the client.
 
 @param blob The blob to fetch the data.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobData:blob:]
 @see WABlob
 */
- (void)fetchBlobData:(WABlob *)blob;

/**
 Fetch the blob data for the specified blob asynchronously.
	
 The method will run asynchronously and will call back through the block. The block will be called with the data for the blob if the request succeeds or an error if the request fails.
 
 @param blob The blob to fetch the data.
 @param block A block object called with the results of the fetch. 
 
 @see WABlob
 */
- (void)fetchBlobData:(WABlob *)blob withCompletionHandler:(void (^)(NSData *data, NSError *error))block;

/**
 Fetch the blob data for the specified url asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client. This method will only run when you are using the proxy service. 
 
 @param URL The URL of the blob to fetch the data.
 
 @returns Returns if the request was sent or not.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchBlobData:URL:]
 */
- (BOOL)fetchBlobDataFromURL:(NSURL *)URL;

/**
 Fetch the blob data for the specified blob asynchronously.
 
 The method will run asynchronously and will call back through the block. The block will be called with the data for the blob if the request succeeds or an error if the request fails. This method will only run when you are using the proxy service.
 
 @param URL The URL of the blob to fetch the data.
 @param block A block object called with the results of the fetch. 
 */
- (BOOL)fetchBlobDataFromURL:(NSURL *)URL withCompletionHandler:(void (^)(NSData *data, NSError *error))block;

/**
 Adds a new blob to a container asynchronously, given the name of the blob, binary data for the blob, and content type.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClient storageClient:didAddBlobToContainer:blobName:].
 
 @param container The container to use to add the blob.
 @param blobName The name of the blob.
 @param contentData The data for the blob.
 @param contentType The content type for the blob.
 
 @warning *Deprecated*: now use addBlob:toContainer:withCompletionHandler:
 
 @see delegate
 @see [WACloudStorageClient storageClient:didAddBlobToContainer:blobName:]
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)addBlobToContainer:(WABlobContainer *)container blobName:(NSString *)blobName contentData:(NSData *)contentData contentType:(NSString*)contentType DEPRECATED_ATTRIBUTE;

/**
 Adds a new blob to a container asynchronously, given the name of the blob, binary data for the blob, and content type with a block.
	
 The method will run asynchronously and will call back through the block. The block will be called an error if the request fails, otherwise the error object will be nil.
 
 @param container The container to use to add the blob.
 @param blobName The name of the blob to add.
 @param contentData The content of the blob to add.
 @param contentType The type of content to add.
 @param block A block object called with the results of the add. 
 
 @warning *Deprecated*: now use addBlob:toContainer:withCompletionHandler:
 
 @see WABlobContainer
 */
// TODO: Remove this before release
- (void)addBlobToContainer:(WABlobContainer *)container blobName:(NSString *)blobName contentData:(NSData *)contentData contentType:(NSString *)contentType withCompletionHandler:(void (^)(NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Adds a new blob to a container asynchronously, given the name of the blob, binary data for the blob, and content type.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClient storageClient:didAddBlob:toContainer:].
 
 @param container The container to use to add the blob.
 @param blob The blob to add.
 @param contentData The data for the blob.
 @param contentType The content type for the blob.
 
 @see delegate
 @see [WACloudStorageClient storageClient:didAddBlob:toContainer:]
 @see WABlobContainer
 */
- (void)addBlob:(WABlob *)blob toContainer:(WABlobContainer *)container;

/**
 Adds a new blob to a container asynchronously, given the blob and container with a block.
 
 The method will run asynchronously and will call back through the block. The block will be called an error if the request fails, otherwise the error object will be nil.
 
 @param blob The blob to add.
 @param container The container to use to add the blob.
 @param block A block object called with the results of the add.
 
 @see WABlobContainer
 */
- (void)addBlob:(WABlob *)blob toContainer:(WABlobContainer *)container withCompletionHandler:(void (^)(NSError *error))block;

/**
 Deletes a given blob asynchronously.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didDeleteBlob:].
 
 @param blob The blob to delete
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteBlob:]
 @see WABlob
 */
- (void)deleteBlob:(WABlob *)blob;

/**
 Deletes a blob asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param blob The blob to delete.
 @param block A block object called with the results of the delete.
 
 @see WABlob
 */
- (void)deleteBlob:(WABlob *)blob withCompletionHandler:(void (^)(NSError *error))block;

#pragma mark - Queue Operations
///---------------------------------------------------------------------------------------
/// @name Queue Operations
///---------------------------------------------------------------------------------------

/**
 Fetch a list of queues asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client.
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueues:]
 */
// TODO: Remove this before release
- (void)fetchQueues DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of queues asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with a list of WAQueue objects or an error if the request fails, otherwise the error object will be nil.
 
 @param block A block object called with the results of the fetch. 
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:usingCompletionHandler:
 
 @see WAQueue
 */
// TODO: Remove this before release
- (void)fetchQueuesWithCompletionHandler:(void (^)(NSArray *queues, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of queues asynchronously with a result continuation.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueues:withResultContinuation:]. The result continuation can be nil or conatin the marker to fetch the next set of queues from a previous request.
 
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of queues to reuturn for this fetch.
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueues:withResultContinuation:]
 @see WAResultContinuation
 */
// TODO: Remove this before release
- (void)fetchQueuesWithContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of queues asynchronously with a result continuation using a block.

 The method will run asynchronously and will call back through the block. The block will return an arry of WAQueue objects if the request succeeds or an error if it fails. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param resultContinuation The result continuation to use for this fetch request.
 @param maxResult The max number of queues to reuturn for this fetch.
 @param block A block object called with the results of the fetch. 
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:usingCompletionHandler:
 
 @see WAResultContinuation
 */
// TODO: Remove this before release
- (void)fetchQueuesWithContinuation:(WAResultContinuation *)resultContinuation maxResult:(NSInteger)maxResult usingCompletionHandler:(void (^)(NSArray *queues, WAResultContinuation *resultContinuation, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a list of queues asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueues:].
 
 @param fetchRequest The fetch request for the queues.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueues:]
 */
- (void)fetchQueuesWithRequest:(WAQueueFetchRequest *)fetchRequest;

/**
 Fetch a list of queues asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with a list of WAQueue objects or an error if the request fails, otherwise the error object will be nil.
 
 @param fetchRequest The fetch request for the queues.
 @param block A block object called with the results of the fetch. 
 
 @see WAQueue
 */
- (void)fetchQueuesWithRequest:(WAQueueFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *queues, WAResultContinuation *resultContinuation, NSError *error))block;

/**
 Adds a queue asynchronously, given a specified queue name.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didAddQueueNamed:].
 
 @param queueName The name of the queue to add.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didAddQueueNamed:]
 */
- (void)addQueueNamed:(NSString *)queueName;

/**
 Adds a queue asynchronously, given a specified queue name using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param queueName The name of the queue to add.
 @param block A block object called with the results of the add.
 */
- (void)addQueueNamed:(NSString *)queueName withCompletionHandler:(void (^)(NSError *error))block;

/**
 Deletes a queue asynchronously, given a specified queue name.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didDeleteQueueNamed:].
 
 @param queueName The name of the queue to delete.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteQueueNamed:]
 */
- (void)deleteQueueNamed:(NSString *)queueName;

/**
 Deletes a queue asynchronously, given a specified queue name using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param queueName The name of the queue to delete.
 @param block A block object called with the results of the delete. 
 */
- (void)deleteQueueNamed:(NSString *)queueName withCompletionHandler:(void (^)(NSError *error))block;

/**
 Fetch a single message asynchronously from the specified queue.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueueMessage:].
 
 @param queueName The name of the queue.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueueMessage:]
 */
- (void)fetchQueueMessage:(NSString *)queueName;

/**
 Fetch a single message asynchronously from the specified queue using a block.

 The method will run asynchronously and will call back through the block. The block will be called with a WAQueueMessage object or an error if the request fails, otherwise the error object will be nil.
 
 @param queueName The name of the queue.
 @param block A block object called with the results of the fetch.
 
 @see WAQueueMessage
 */
- (void)fetchQueueMessage:(NSString *)queueName withCompletionHandler:(void (^)(WAQueueMessage *message, NSError *error))block;

/**
 Fetch messages asynchronously for a given queue name.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:].
 
 @param queueName The name of the queue to get messages.
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:]
 */
// TODO: Remove this before release
- (void)fetchQueueMessages:(NSString *)queueName DEPRECATED_ATTRIBUTE;

/**
 Fetch messages asynchronously for a given queue name using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with a list of WAQueueMessage objects or an error if the request fails, otherwise the error object will be nil.
 
 @param queueName The name of the queue to get messages.
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:usingCompletionHandler:
 
 @see WAQueueMessage
 */
// TODO: Remove this before release
- (void)fetchQueueMessages:(NSString *)queueName withCompletionHandler:(void (^)(NSArray *messages, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a batch of messages asynchronously from the specified queue.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:]. The max number of messages that will be returned is 32.
 
 @param queueName The name of the queue.
 @param fetchCount The number of messages to fetch.
 
 @warning *Deprecated*: now use fetchQueueMessagesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:]
 */
// TODO: Remove this before release
- (void)fetchQueueMessages:(NSString *)queueName fetchCount:(NSInteger)fetchCount DEPRECATED_ATTRIBUTE;

/**
 Fetch a batch of messages asynchronously from the specified queue using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an array of WAQueueMessage object or an error if the request fails, otherwise the error object will be nil.
 
 @param queueName The name of the queue.
 @param fetchCount The number of messages to fetch.
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchQueuesWithRequest:usingCompletionHandler:
 
 @see WAQueueMessage
 */
// TODO: Remove this before release
- (void)fetchQueueMessages:(NSString *)queueName fetchCount:(NSInteger)fetchCount withCompletionHandler:(void (^)(NSArray *messages, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetch a batch of messages asynchronously from the specified queue.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:]. The max number of messages that will be returned is 32.
 
 @param fetchRequest The fetch request to fetch the messages.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchQueueMessages:]
 @see WAQueueMessageFetchRequest
 */
- (void)fetchQueueMessagesWithRequest:(WAQueueMessageFetchRequest *)fetchRequest;

/**
 Fetch a batch of messages asynchronously from the specified queue using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an array of WAQueueMessage object or an error if the request fails, otherwise the error object will be nil.
 
 @param fetchRequest The fetch request to fetch the messages.
 @param block A block object called with the results of the fetch.
 
 @see WAQueueMessage
 @see WAQueueMessageFetchRequest
 */
- (void)fetchQueueMessagesWithRequest:(WAQueueMessageFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *messages, NSError *error))block;

/**
 Peeks a single message from the specified queue asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didPeekQueueMessage:]. Peek is like fetch, but the message is not marked for removal.
 
 @param queueName The name of the queue.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didPeekQueueMessage:]
 */
- (void)peekQueueMessage:(NSString *)queueName;

/**
 Peeks a single message from the specified queue asynchronously using a block.

 The method will run asynchronously and will call back through the block. The block will be called with a WAQueueMessage object or an error if the request fails, otherwise the error object will be nil. Peek is like fetch, but the message is not marked for removal.
 
 @param queueName The name of the queue.
 @param block A block object called with the results of the peek.
 
 @see WAQueueMessage
 */
- (void)peekQueueMessage:(NSString *)queueName withCompletionHandler:(void (^)(WAQueueMessage *message, NSError *error))block;

/**
 Peeks a batch of messages from the specified queue asynchronously.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didPeekQueueMessages:]. Peek is like fetch, but the message is not marked for removal.
 
 @param queueName The name of the queue.
 @param fetchCount The number of messages to return.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didPeekQueueMessages:]
 */
- (void)peekQueueMessages:(NSString *)queueName fetchCount:(NSInteger)fetchCount;

/**
 Peeks a batch of messages from the specified queue asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an array of WAQueueMessage object or an error if the request fails, otherwise the error object will be nil. Peek is like fetch, but the message is not marked for removal.
 
 @param queueName The name of the queue.
 @param fetchCount The number of messages to return.
 @param block A block object called with the results of the peek.
 
 @see WAQueueMessage
 */
- (void)peekQueueMessages:(NSString *)queueName fetchCount:(NSInteger)fetchCount withCompletionHandler:(void (^)(NSArray *messages, NSError *error))block;

/**
 Deletes a message asynchronously, given a specified queue name and queueMessage.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didDeleteQueueMessage:queueName:].
 
 @param queueMessage The message to delete.
 @param queueName The name of the queue that owns the message.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteQueueMessage:queueName:]
 @see WAQueueMessage
 */
- (void)deleteQueueMessage:(WAQueueMessage *)queueMessage queueName:(NSString *)queueName;

/**
 Deletes a message asynchronously, given a specified queue name and queueMessage using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param queueMessage The message to delete.
 @param queueName The name of the queue that owns the message.
 @param block A block object called with the results of the peek.
 
 @see WAQueueMessage
 */
- (void)deleteQueueMessage:(WAQueueMessage *)queueMessage queueName:(NSString *)queueName withCompletionHandler:(void (^)(NSError *error))block;

/**
 Adds a message into a queue asynchronously, given a specified queue name and message.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didAddMessageToQueue:queueName:].
 
 @param message The message to add.
 @param queueName The name of the queue to add the message.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didAddMessageToQueue:queueName:]
 */
- (void)addMessageToQueue:(NSString *)message queueName:(NSString *)queueName;

/**
 Adds a message into a queue asynchronously, given a specified queue name and message.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param message The message to add.
 @param queueName The name of the queue to add the message.
 @param block A block object called with the results of the add.
 */
- (void)addMessageToQueue:(NSString *)message queueName:(NSString *)queueName withCompletionHandler:(void (^)(NSError *error))block;

#pragma mark - Table Operations
///---------------------------------------------------------------------------------------
/// @name Table Operations
///---------------------------------------------------------------------------------------

/**
 Fetch a list of tables asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchTables:].
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchTables:]
 */
- (void)fetchTables;

/**
 Fetch a list of tables asynchronously using a block.
 
 @param block A block object called with the results of the fetch.
 
 @discussion The method will run asynchronously and will call back through the block. The block will be called with an arrary of NSString objects that are the table names or an error if the request fails, otherwise the error object will be nil.
 */
- (void)fetchTablesWithCompletionHandler:(void (^)(NSArray *tables, NSError *error))block;

/**
 Fetch a list of tables asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchTables:withResultContinuation:].
 
 @param resultContinuation The result continuation to use for this fetch request.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchTables:withResultContinuation:]
 @see WAResultContinuation
 */
- (void)fetchTablesWithContinuation:(WAResultContinuation *)resultContinuation;

/**
 Fetch a list of tables asynchronously.
 
 The method will run asynchronously and will call back through the block. The block will be called with an arrary of NSString objects that are the table names or an error if the request fails, otherwise the error object will be nil. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param resultContinuation The result continuation to use for this fetch request.
 @param block A block object called with the results of the fetch.
 
 @see WAResultContinuation
 */
- (void)fetchTablesWithContinuation:(WAResultContinuation *)resultContinuation usingCompletionHandler:(void (^)(NSArray *tables, WAResultContinuation *resultContinuation, NSError *error))block;

/**
 Creates a new table asynchronously with a specified name.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didCreateTableNamed:].
 
 @param newTableName The new table name.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didCreateTableNamed:]
 */
- (void)createTableNamed:(NSString *)newTableName;

/**
 Creates a new table asynchronously with a specified name.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param newTableName The new table name.
 @param block A block object called with the results of the create.
 */
- (void)createTableNamed:(NSString *)newTableName withCompletionHandler:(void (^)(NSError *error))block;

/**
 Deletes a specifed table asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didDeleteTableNamed:].
 
 @param tableName The name of the table to delete.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteTableNamed:]
 */
- (void)deleteTableNamed:(NSString *)tableName;

/**
 Deletes a specifed table asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param tableName The name of the table to delete.
 @param block A block object called with the results of the delete.
 */
- (void)deleteTableNamed:(NSString *)tableName withCompletionHandler:(void (^)(NSError *error))block;

/**
 Fetches the entities for a given table asynchronously.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:].
 
 @param fetchRequest The request to use to fetch the entities.
 
 @warning *Deprecated*: now use fetchEntitiesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:]
 @see WATableFetchRequest
 */
// TODO: Remove this before release
- (void)fetchEntities:(WATableFetchRequest *)fetchRequest DEPRECATED_ATTRIBUTE;

/**
 Fetches the entities for a given table asynchronously using a block.

 The method will run asynchronously and will call back through the block. The block will be called with an arrary of WATableEntity objects that are the table names or an error if the request fails, otherwise the error object will be nil.
 
 @param fetchRequest The request to use to fetch the entities.
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use fetchEntitiesWithRequest:usingCompletionHandler:
 
 @see WATableEntity
 @see WATableFetchRequest
 */
// TODO: Remove this before release
- (void)fetchEntities:(WATableFetchRequest *)fetchRequest withCompletionHandler:(void (^)(NSArray *entities, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetches the entities for a given table asynchronously using a result continuation.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:withResultContinuation:]. The fetch request contains the result continuation to use for this fetch request.
 
 @param fetchRequest The request to use to fetch the entities. 
 
 @warning *Deprecated*: now use fetchEntitiesWithRequest:
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:withResultContinuation:]
 @see WATableFetchRequest
 */
// TODO: Remove this before release
- (void)fetchEntitiesWithContinuation:(WATableFetchRequest *)fetchRequest DEPRECATED_ATTRIBUTE;

/**
 Fetches the entities for a given table asynchronously using a result continuation and block.

 The method will run asynchronously and will call back through the block. The block will be called with an arrary of WATableEntity objects that are the table names or an error if the request fails, otherwise the error object will be nil. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param fetchRequest The request to use to fetch the entities. 
 @param block A block object called with the results of the fetch.
 
 @warning *Deprecated*: now use WACloudStorageClient#fetchEntitiesWithRequest:usingCompletionHandler:
 
 @see WAFetchRequest
 @see WATableEntity
 */
// TODO: Remove this before release
- (void)fetchEntitiesWithContinuation:(WATableFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *entities, WAResultContinuation *resultContinuation, NSError *error))block DEPRECATED_ATTRIBUTE;

/**
 Fetches the entities for a given table asynchronously using a result continuation.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:withResultContinuation:]. The fetch request contains the result continuation to use for this fetch request.
 
 @param fetchRequest The request to use to fetch the entities. 
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didFetchEntities:fromTableNamed:withResultContinuation:]
 @see WATableFetchRequest
 */
- (void)fetchEntitiesWithRequest:(WATableFetchRequest *)fetchRequest;

/**
 Fetches the entities for a given table asynchronously using a result continuation and block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an arrary of WATableEntity objects that are the table names or an error if the request fails, otherwise the error object will be nil. The result continuation can be used to make requests for the next set of blobs in the contianer.
 
 @param fetchRequest The request to use to fetch the entities. 
 @param block A block object called with the results of the fetch.
 
 @see WAFetchRequest
 @see WATableEntity
 */
- (void)fetchEntitiesWithRequest:(WATableFetchRequest *)fetchRequest usingCompletionHandler:(void (^)(NSArray *entities, WAResultContinuation *resultContinuation, NSError *error))block;

/**
 Inserts a new entity into an existing table asynchronously.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didInsertEntity:].
 
 @param newEntity The new entity to insert.
	
 @returns Returns if the request was sent successfully.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didInsertEntity:]
 @see WATableEntity
 */
- (BOOL)insertEntity:(WATableEntity *)newEntity;

/**
 Inserts a new entity into an existing table asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param newEntity The new entity to insert.
 @param block A block object called with the results of the insert.
 
 @returns Returns if the request was sent successfully.
 
 @see WATableEntity
 */
- (BOOL)insertEntity:(WATableEntity *)newEntity withCompletionHandler:(void (^)(NSError *error))block;

/**
 Updates an existing entity within a table asynchronously.

 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didUpdateEntity:].
 
 @param existingEntity The entity to update.
	
 @returns Returns if the request was sent successfully.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didUpdateEntity:]
 @see WATableEntity
 */
- (BOOL)updateEntity:(WATableEntity *)existingEntity;


/**
 Updates an existing entity within a table asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param existingEntity The entity to update.
 @param block A block object called with the results of the insert.
 
 @returns Returns if the request was sent successfully.
 
 @see WATableEntity
 */
- (BOOL)updateEntity:(WATableEntity *)existingEntity withCompletionHandler:(void (^)(NSError *error))block;

/**
 Merges an existing entity within a table asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didMergeEntity:].
 
 @param existingEntity The entity to merge.
 
 @returns Returns if the request was sent successfully.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didMergeEntity:]
 @see WATableEntity
 */
- (BOOL)mergeEntity:(WATableEntity *)existingEntity;

/**
 Merges an existing entity within a table asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param existingEntity The entity to merge.
 @param block A block object called with the results of the merge.
 
 @returns Returns if the request was sent successfully.
 
 @see WATableEntity
 */
- (BOOL)mergeEntity:(WATableEntity *)existingEntity withCompletionHandler:(void (^)(NSError *error))block;

/**
 Deletes an existing entity within a table asynchronously.
 
 The method will run asynchronously and will call back through the delegate for the client using [WACloudStorageClientDelegate storageClient:didDeleteEntity:].
 
 @param existingEntity The entity to delete.
 
 @returns Returns if the request was sent successfully.
 
 @see delegate
 @see [WACloudStorageClientDelegate storageClient:didDeleteEntity:]
 @see WATableEntity
 */
- (BOOL)deleteEntity:(WATableEntity *)existingEntity;

/**
 Deletes an existing entity within a table asynchronously using a block.
 
 The method will run asynchronously and will call back through the block. The block will be called with an error if the request fails, otherwise the error object will be nil.
 
 @param existingEntity The entity to delete.
 @param block A block object called with the results of the delete.
 
 @returns Returns if the request was sent successfully.
 
 @see WATableEntity
 */
- (BOOL)deleteEntity:(WATableEntity *)existingEntity withCompletionHandler:(void (^)(NSError *error))block;

///---------------------------------------------------------------------------------------
/// @name Creating and Initializing Clients
///---------------------------------------------------------------------------------------

/**
 Create a storage client initialized with the given credential.
	
 @param credential The credentials for Windows Azure storage. 
	
 @returns The newly initialized WACloudStorageClient object.
 */
+ (WACloudStorageClient *)storageClientWithCredential:(WAAuthenticationCredential *)credential;


@end