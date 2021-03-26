/*
 *  FatLayout.h
 *  MachOView
 *
 *  Created by psaghelyi on 02/12/2011.
 *
 */

#import "Layout.h"

/// 胖文件中的 Fat Header 的布局
@interface FatLayout : MVLayout;

/// 调用了父类 MVLayout 的初始化
+ (FatLayout *)     layoutWithDataController:(MVDataController *)dc rootNode:(MVNode *)node;

@end

