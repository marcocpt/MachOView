/*
 *  Document.h
 *  MachOView
 *
 *  Created by psaghelyi on 15/06/2010.
 *
 */

@class MVDataController;

@interface MVOutlineView : NSOutlineView
{
}
@end

@interface MVTableView : NSTableView
{
}
@end

@interface MVRightFormatter : NSFormatter
{
  BOOL        compound;   ///< NO: plain hex;     YES: groups of bytes (11 22 33 44 55)
  NSUInteger  length;     ///< size of hex value; number of bytes
  BOOL        alignLeft;  ///< NO: 12 --> 0012    YES: 12 --> 1200
}
@end


@interface MVDocument : NSDocument
{
  IBOutlet MVOutlineView *        leftView;           ///< 1. 左边列表视图
  IBOutlet MVTableView *          rightView;          ///< 2. 主窗口表格视图
  IBOutlet NSSearchField *        searchField;        ///< 3. 搜索框字段, SEL: `updateSearchFilter`
  IBOutlet NSTextField *          statusText;         ///< 4. 底部状态栏字段
  IBOutlet NSProgressIndicator *  progressIndicator;  ///< 5. 底部状态栏中的进度指示器
  /// 6. 0: RAW 文件偏移; 1: RVA 虚拟地址偏移. SEL: `updateAddressingMode`
  IBOutlet NSSegmentedControl *   offsetModeSwitch;
  IBOutlet NSButton *             stopButton;         ///< 7. Bevel Button, SEL: `stopProcessing:`
  MVDataController *              dataController;     ///< 处理数据的主控制器
  int32_t                         threadCount;        ///< TODO:
}
@property (nonatomic,readonly) MVDataController * dataController; ///< 处理数据的主控制器

/// 对应 searchField
- (IBAction)updateSearchFilter:(id)sender;
/// 对应 offsetModeSwitch
- (IBAction)updateAddressingMode:(id)sender;
/// 对应 stopButton
- (IBAction)stopProcessing:(id)sender;
/// 是选择虚拟地址偏移
- (BOOL)isRVA;
/// 利用程序名,CFBundleShortVersionString 生成临时目录名称
+ (NSString *)temporaryDirectory;

@end
