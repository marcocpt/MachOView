/*
 *  Layout.h
 *  MachOView
 *
 *  Created by psaghelyi on 18/03/2011.
 *
 */


#define MATCH_STRUCT(obj,location) \
  struct obj const * obj = (struct obj *)[self imageAt:(location)]; \
  if (!obj) [NSException raise:@"null exception" format:@#obj " is null"];

@class MVDataController;
@class MVArchiver;
@class MVNode;


@interface MVLayout : NSObject 
{
  MVNode *              __weak rootNode;        ///< 布局对象的根节点
  MVDataController *    __weak dataController;  ///<
  uint32_t              imageOffset;  ///< absolute physical offset of the image in binary
  uint32_t              imageSize;    ///< size of the image corresponds to this layout
  NSThread *            backgroundThread; ///< 后台线程用来处理 doBackgroundTasks
  MVArchiver *          archiver;
}

@property(nonatomic,weak,readonly)  MVDataController * dataController;
@property(nonatomic,readonly) NSThread * backgroundThread;
@property(nonatomic,readonly) MVArchiver * archiver;

- (id)                  initWithDataController:(MVDataController *)dc rootNode:(MVNode *)node;
///dataController.realData  中位于 location 的指针
- (void const *)        imageAt:(uint32_t)location;
- (void)                printException:(NSException *)exception caption:(NSString *)caption;
/// 是 64 位架构
- (BOOL)                is64bit;
/// 在主线程解析 `MVLayout` 生成节点对象用于 `leftView` 显示
- (void)                doMainTasks;
/// 后台处理 section 等. FatLayout 直接取消线程
- (void)                doBackgroundTasks;
- (NSString *)          convertToRVA: (NSString *)offsetStr;
- (MVNode *)            findNodeByUserInfo:(NSDictionary *)userInfo;

/// Create data node without details table (only hex content)
- (MVNode *)            createDataNode:(MVNode *)parent
                               caption:(NSString *)caption
                              location:(uint32_t)location
                                length:(uint32_t)length;

@end
