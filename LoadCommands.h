/*
 *  LoadCommands.h
 *  MachOView
 *
 *  Created by psaghelyi on 20/07/2010.
 *
 */

#import "MachOLayout.h"


@interface MachOLayout (LoadCommands)

/// 获取 load_command 子节点的类型名称
- (NSString *)getNameForCommand:(uint32_t)cmd;
/// 创建 load_command 的子节点
-(MVNode *)createLoadCommandNode:(MVNode *)parent
                         caption:(NSString *)caption
                        location:(uint32_t)location
                          length:(uint32_t)length
                         command:(uint32_t)command;

@end
