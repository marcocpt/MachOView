/*
 *  ArchiveLayout.h
 *  MachOView
 *
 *  Created by psaghelyi on 18/03/2011.
 *
 */

#import "Layout.h"

@interface MVObjectInfo : NSObject
{
  NSString *    name;           ///< 存储 symtab_header->longname
  uint32_t      length;         ///< symtab_header->size 减去 symtab_header->name 中的数字
  MVLayout *    __weak layout;
}

@property (nonatomic)                   NSString *  name;
@property (nonatomic)                   uint32_t    length;
@property (nonatomic,weak)  MVLayout *  layout;

@end

/// 档案文件布局。静态库文件
@interface ArchiveLayout : MVLayout 
{
  NSMutableDictionary * objectInfoMap; // <(NSNumber)object offset,MVObjectInfo>
}

+ (ArchiveLayout *)     layoutWithDataController:(MVDataController *)dc rootNode:(MVNode *)node;

@end
